OKRA is a runtime library that enables applications to do compute offloads to 
HSA-enabled GPUs.

### OKRA binaries:

#### okra/dist
* okra.jar

#### okra/dist/bin
* libokra_x86_64.so
* libnewhsacore64.so
* libamdhsacl64.so

### OKRA public headers:

#### okra/dist/include
* okraContext.h

### OKRA samples:

#### okra/samples/dist
* Squares (along with Squares.hsail)

### Running OKRA samples

There are two pre-requisites that should be satisfied to successfuly use OKRA 
runtime library and samples.
	
* A working setup of an HSA platform
* Ubuntu 13.10 linux with HSA drivers
* Refer to instructions in  https://github.com/HSAFoundation/Linux-HSA-Drivers-And-Images-AMD
  for both the pre-requisites

#### To run OKRA samples:
* $cd okra/samples
* $./runSquares.sh

### Using other software infrastructures on top of OKRA 

* If you want aparapi to use OKRA, refer to https://code.google.com/p/aparapi/wiki/HSAEnablementOfLambdaBranch
* If you want Sumatra (openJDK) to use OKRA, refer to https://wiki.openjdk.java.net/display/Sumatra/Main
