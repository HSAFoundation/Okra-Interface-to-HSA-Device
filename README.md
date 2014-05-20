OKRA is a runtime library that enables applications to do compute offloads to 
HSA-enabled GPUs.

Note: Master branch always maps to the latest release - Now on v0.5. For binaries from
previous releases refer to other branches. You can do 'git branch -a' to see all
branches.

### OKRA binaries:

#### okra/dist
* okra.jar

#### okra/dist/bin
* libokra_x86_64.so
* libnewhsacore64.so
* libamdhsacl64.so
* libhsakmt.so.1

### OKRA public headers:

#### okra/dist/include
* okraContext.h

### OKRA samples:

#### okra/samples/src/cpp/Squares
* Squares.cpp
* Squares.hsail

#### Build OKRA samples
* $cd okra/samples
* $./build.sh

This will create okra/samples/dist and the binaries will be placed there

### Running OKRA samples

There are three pre-requisites that should be satisfied to successfuly use OKRA 
runtime library and samples.
	
* A working setup of an HSA platform
* Ubuntu 13.10 linux with HSA drivers
* Refer to instructions in  https://github.com/HSAFoundation/Linux-HSA-Drivers-And-Images-AMD
  for both the pre-requisites (branch:master)
* Install libelf-dev package: sudo apt-get install libelf-dev

#### To run OKRA samples:
* $cd okra/samples
* $./runSquares.sh

### Using other software infrastructures on top of OKRA 

* If you want aparapi to use OKRA, refer to https://code.google.com/p/aparapi/wiki/HSAEnablementOfLambdaBranch
* If you want Sumatra (openJDK) to use OKRA, refer to https://wiki.openjdk.java.net/display/Sumatra/Main
