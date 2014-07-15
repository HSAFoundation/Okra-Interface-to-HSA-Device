OKRA is a runtime library that enables applications to do compute offloads to 
HSA-enabled GPUs.

Note: Master branch always maps to the latest release - which is v0.6 at this point. For binaries from
previous releases refer to other branches. You can do 'git branch -a' to see all
branches or use the web interface in github.com.

New: OKRA has a C interface now. check out okra.h.

### Downloading OKRA and its binaries:
There are two ways of doing this. 
* One is through github.com web interface. Choose the branch and then click 'Download Zip' to get the zip.
* Second is through the commandline. git clone https://github.com/HSAFoundation/Okra-Interface-to-HSA-Device
  Remember this will default to 'master' branch and if you want to use binaries from a different branch
  you may do so using - git checkout

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
* okra.h

### OKRA samples:

#### okra/samples/src/cpp/Squares (updated to use okra.h)
* Squares.cpp
* Squares.hsail

#### Build OKRA samples
* $cd okra/samples
* $./build.sh

This will create okra/samples/dist and the binaries will be placed there

### Running OKRA samples

There are some pre-requisites that should be satisfied to successfuly use OKRA 
runtime library and samples.
	
* A working setup of an HSA platform
* Ubuntu 13.10 or 14.04LTS linux with HSA drivers
* Refer to instructions in  https://github.com/HSAFoundation/Linux-HSA-Drivers-And-Images-AMD
  for both the pre-requisites (branch:master, kfd-v0.6)
* Install build-essential package: sudo apt-get install build-essential
* Install libelf-dev package: sudo apt-get install libelf-dev

#### To run OKRA samples:
* $cd okra/samples
* $./runSquares.sh

### Using other software infrastructures on top of OKRA 

* If you want aparapi to use OKRA, refer to https://code.google.com/p/aparapi/wiki/HSAEnablementOfLambdaBranch
* If you want Sumatra (openJDK) to use OKRA, refer to https://wiki.openjdk.java.net/display/Sumatra/Main
