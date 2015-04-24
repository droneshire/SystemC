/*

Part 1

Run the simulation and see how the simulation time is continually incremented
Take a copy of the original code before making any modifications

You have to modify the initiator to use a quantum keeper to implement temporal decoupling
such that the initiator thread runs ahead for a quantum of 1 US before yielding control
back to the SystemC scheduler

See if you can measure the simulation speed increase due to temporal decoupling by
comparing the speed of your new version with the original. In order to notice the speed
increase, you will need to

1. Increase the value of RUN_LENGTH (e.g. add 4 zeros)
2. Comment out the statement that writes messages to cout

Now investigate the effect of making the quantum larger and smaller:
Make a plot of CPU time against quantum for the values 250 NS, 1 US, 4US and 16 US


*/

#define SC_INCLUDE_DYNAMIC_PROCESSES

#include "systemc"
using namespace sc_core;
using namespace std;

#include "tlm.h"

struct Initiator: sc_module, tlm::tlm_bw_transport_if<>
{
  // TLM-2 socket, defaults to 32-bits wide, base protocol
  tlm::tlm_initiator_socket<> socket;

  SC_CTOR(Initiator) : socket("socket")
  {
    socket.bind(*this);

    SC_THREAD(thread_process);
  }

  enum { RUN_LENGTH = 128 };

  void set_base_address(int addr) { base_address = addr; }

  void thread_process()
  {
    tlm::tlm_generic_payload trans;
    sc_time delay;

    for (int i = 0; i < RUN_LENGTH; i += 4)
    {
      int address = base_address + (i % 128);
      tlm::tlm_command cmd = static_cast<tlm::tlm_command>(rand() % 2);
      if (cmd == tlm::TLM_WRITE_COMMAND) data = address;

      trans.set_command( cmd );
      trans.set_address( address );
      trans.set_data_ptr( reinterpret_cast<unsigned char*>(&data) );
      trans.set_data_length( 4 );
      trans.set_streaming_width( 4 );
      trans.set_byte_enable_ptr( 0 );
      trans.set_dmi_allowed( false );
      trans.set_response_status( tlm::TLM_INCOMPLETE_RESPONSE );

      delay = SC_ZERO_TIME;

      socket->b_transport( trans, delay );

      if (trans.is_response_error())
        SC_REPORT_ERROR("TLM-2", trans.get_response_string().c_str());

      cout << name() << " completed " << (cmd ? "write" : "read") << ", addr = " << hex << i
           << ", data = " << hex << data << ", time " << sc_time_stamp()
           << " delay = " << delay << endl;

      wait(delay);
    }
  }


  // TLM-2 backward non-blocking transport method
  virtual tlm::tlm_sync_enum nb_transport_bw( tlm::tlm_generic_payload& trans,
                                              tlm::tlm_phase& phase, sc_time& delay )
  {
    // Dummy method
    return tlm::TLM_ACCEPTED;
  }

  // TLM-2 backward DMI method
  virtual void invalidate_direct_mem_ptr(sc_dt::uint64 start_range,
                                         sc_dt::uint64 end_range)
  {
    // Dummy method
  }

  int base_address;
  int data; // Internal data buffer used by initiator with generic payload
};


// Target module representing a simple memory

struct Memory: sc_module, tlm::tlm_fw_transport_if<>
{
  // TLM-2 socket, 32-bits wide, base protocol, may be bound twice
  tlm::tlm_target_socket<32, tlm::tlm_base_protocol_types, 2> socket;

  enum { SIZE = 256 };
  int mem[SIZE];

  SC_CTOR(Memory)
  : socket("socket")
  {
    socket.bind(*this);

    // Initialize memory with random data
    for (int i = 0; i < SIZE; i++)
      mem[i] = rand() % 256;
  }

  // TLM-2 blocking transport method
  virtual void b_transport( tlm::tlm_generic_payload& trans, sc_time& delay )
  {
    tlm::tlm_command cmd = trans.get_command();
    sc_dt::uint64    adr = trans.get_address();
    unsigned char*   ptr = trans.get_data_ptr();
    unsigned int     len = trans.get_data_length();
    unsigned char*   byt = trans.get_byte_enable_ptr();
    unsigned int     wid = trans.get_streaming_width();

    // Obliged to check address range and check for unsupported features,
    //   i.e. byte enables, streaming, and bursts
    // Can ignore DMI hint and extensions
    // Using the SystemC report handler is an acceptable way of signalling an error

    if (adr >= sc_dt::uint64(SIZE) * 4 || adr % 4)
    {
      trans.set_response_status( tlm::TLM_ADDRESS_ERROR_RESPONSE );
      return;
    }
    else if (byt != 0)
    {
      trans.set_response_status( tlm::TLM_BYTE_ENABLE_ERROR_RESPONSE );
      return;
    }
    else if (len > 4 || wid < len)
    {
      trans.set_response_status( tlm::TLM_BURST_ERROR_RESPONSE );
      return;
    }

    // Obliged to implement read and write commands
    if ( cmd == tlm::TLM_READ_COMMAND )
      memcpy(ptr, &mem[adr/4], len);
    else if ( cmd == tlm::TLM_WRITE_COMMAND )
      memcpy(&mem[adr/4], ptr, len);

    // Memory access time
    delay = delay + sc_time(100, SC_NS);

    // Obliged to set response status to indicate successful completion
    trans.set_response_status( tlm::TLM_OK_RESPONSE );
  }

  // TLM-2 forward non-blocking transport method
  virtual tlm::tlm_sync_enum nb_transport_fw( tlm::tlm_generic_payload& trans,
                                              tlm::tlm_phase& phase, sc_time& delay )
  {
    // Dummy method (not TLM-2.0 compliant)
    return tlm::TLM_ACCEPTED;
  }

  // TLM-2 forward DMI method
  virtual bool get_direct_mem_ptr(tlm::tlm_generic_payload& trans,
                                  tlm::tlm_dmi& dmi_data)
  {
    // Dummy method
    return false;
  }

  // TLM-2 debug transport method
  virtual unsigned int transport_dbg(tlm::tlm_generic_payload& trans)
  {
    // Dummy method
    return 0;
  }
};


SC_MODULE(Top)
{
  Initiator* init1;
  Initiator* init2;
  Memory*         memory;

  SC_CTOR(Top)
  {
    init1  = new Initiator("init1");
    init1->set_base_address(000);
    init2  = new Initiator("init2");
    init2->set_base_address(128);
    memory = new Memory("memory");

    init1->socket.bind( memory->socket );
    init2->socket.bind( memory->socket );
  }
};

int sc_main( int argc, char* argv[])
{
    Top top("top");
    sc_start();
    return 0;
}
