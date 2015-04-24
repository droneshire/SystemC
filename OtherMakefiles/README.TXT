This directory contains examples of makefiles for Mentor Graphics Modelsim,  
Cadence Incisive Unified Simulator, and Synopsys System Studio.


For Modelsim:
-------------

Makefile.modelsim
Makefile.Modelsimdefs

You must edit the Makefile.modelsim to point to the work library. The
default is ./lib

For Cadence IUS:
----------------

Makefile.ncsim
Makefile.depends

For Cadence, the preferred method is to now use ncsc_run to compile and 
launch simulations.


For Synosys System Studio:
--------------------------

Makefile.ccss
Makefile.ccssdefs

You can run Makefile.ccss after creating a System Studio project.
The Makefile.ccss assumes the source files are in a directory called
lib.

After creating the code, you can run it by using
 
simdbg run.x 

to run under the graphical interface, or by using 

run.x

to run at the command line.

For CoWare ConvergenSC:
-----------------------

Makefile.cnscdefs

You can run the normal Makefile. It is wise to do 

 make clean
 
first to remove any old "Debug" directories (e.g. if you've already run
scsh).

After the gmake command completes, you can start the ConvergenSC
shell by the command scsh.

In the ConvergenSC shell type 

    scsh>sim run.x

to select the built simulation before running or debugging it.
To start a debug gui (basic gui ddd), type the command gui at 
the scsh prompt, eg.

    scsh>gui

Alternatively, you can run the simulation without a debugger, by
the command run, eg.

    scsh>run

At the end of the simulation session, you can  exit the 
ConvergenSC environment by quit at the scsh> prompt.

You can also run the simulation directly by typing

   Debug/run.x
   
 at the UNIX shell command prompt.
