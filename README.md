OKRA is a runtime library that enables applications to do compute offloads to 
HSA-enabled GPUs. OKRA provides a C interface now. check out okra.h.

Note: Master branch always maps to the latest release - which is v0.8 at this point. For binaries and instructions from
previous releases refer to other branches. You can do 'git branch -a' to see all
branches, and switch to the preferred branch using command line  or use the web interface in github.com to choose the branch you want.

### What's new with this release?
- OKRA uses the HSA Runtime API and the implementation from: https://github.com/HSAFoundation/HSA-Runtime-AMD which is
based on 1.0P specification. For documentation of the specification refer to: https://github.com/HSAFoundation/HSA-docs/wiki
- Bug fixes
- OKRA repository does not host HSA Runtime and compiler libraries (previously libnewhsacore64.so, libamdhsacl64.so)
and HSA KMT library (libhsakmt.so.1) anymore. Since the HSA Runtime Programmer's Manual 1.0P is public, the HSA public headers
and the corresponding libraries are hosted separately. For HSA Runtime headers and libraries, see: https://github.com/HSAFoundation/HSA-Runtime-AMD.
For HSA KMT library, see: https://github.com/HSAFoundation/HSA-Drivers-Linux-AMD. See libhsakmt directory.
- As a result of above, there are changes in the instructions of how to build and run OKRA Squares sample.
- Environment variable: OKRA\_DISABLE\_FIX\_HSAIL. HSA Programmer's Reference Manual 1.0P specification has been released recently. Refer to
https://github.com/HSAFoundation/HSA-docs-AMD/wiki for documentation. However, all users of OKRA have not upgraded their code
generation to 1.0P HSAIL. That is, some customers are still generating 0.95 HSAIL. For those customers who do not yet generate 1.0P instructions (which is the majority today),
OKRA fixes the hsail instructions to match up to 1.0P instructions. Note that, this is not a universal fix for all possible instructions. This
has been done only for a known set of tests from what we have seen before from our customers (see known issues). But, if the OKRA user is already generating 1.0P HSAIL instructions,
then they should disable OKRA from doing any fixup. They can do so by setting environment variable OKRA\_DISABLE\_FIX\_HSAIL=1

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
* libokra\_x86\_64.so

### OKRA public headers:

#### okra/dist/include
* okra.h

### OKRA samples:

#### okra/samples/src/cpp/Squares
* Squares.cpp
* Squares.hsail

### Pre-requisites
There are some pre-requisites that should be satisfied to successfuly use OKRA 
runtime library and samples.
	
* A working setup of an HSA platform
* Ubuntu 13.10 or 14.04LTS linux with HSA drivers - Download and follow instructions in  https://github.com/HSAFoundation/Linux-HSA-Drivers-And-Images-AMD
  (branch:master, kfd-v0.8) to install the driver
* Download HSA Runtime libraries from repo: https://github.com/HSAFoundation/HSA-Runtime-AMD
* Install build-essential package: sudo apt-get install build-essential
* Install libelf-dev package: sudo apt-get install libelf-dev
* Setup the ENVIRONMENT by editing the following variables in **okra/samples/env.sh** (also see comments in env.sh)
    * HSA\_OKRA\_PATH: This should point to top of the directory obtained after downloading from this github repo: https://github.com/HSAFoundation/Okra-Interface-to-HSA-Device
    * HSA\_RUNTIME\_PATH: This should point to top of the directory obtained after downloading from this github repo: https://github.com/HSAFoundation/HSA-Runtime-AMD
    * HSA\_KMT\_PATH: This should point to libhsakmt directory obtained after downloading from this github repo: https://github.com/HSAFoundation/HSA-Drivers-Linux-AMD/tree/master/kfd-0.8/libhsakmt

#### Build OKRA samples
* $cd okra/samples
* $./build.sh

This will create okra/samples/dist and the binaries will be placed there

### Running OKRA samples

#### To run OKRA samples:
* $cd okra/samples
* $./runSquares.sh

The test should pass

### Using other software infrastructures on top of OKRA 

* If you want aparapi to use OKRA/HSA, refer to: http://code.google.com/p/aparapi/wiki/SettingUpLinuxHSAMachineForAparapi
* If you want Sumatra (openJDK) to use OKRA/HSA, refer to https://wiki.openjdk.java.net/display/Sumatra/Main

### FAQs

* I see build errors while doing ./build.sh
    * Answer: Check the Environment variables setup in okra/samples/env.sh. Each variable should be setup as instructed in the comment above it.
* I keep getting an error saying 'error while loading shared libraries: libokra\_x86\_64.so: cannot open shared object file: No such file or directory'. 
    * Answer: The libokra\_x86\_64.so library directory isn't in the LD\_LIBRARY\_PATH or the version of libokra\_x86\_64.so is incorrect.
* I keep getting an error saying 'error while loading shared libraries: libhsa-runtime64.so.1: cannot open shared object file: No such file or directory'. 
    * Answer: The libhsa-runtime64.so.1 library directory isn't in the LD\_LIBRARY\_PATH or the version of libhsa-runtime64.so.1 is incorrect.
* I keep getting an error saying 'error while loading shared libraries: libhsakmt.so.1: cannot open shared object file: No such file or directory'. 
    * Answer: The libhsakmt.so.1 library directory isn't in the LD\_LIBRARY\_PATH or the version of libhsamkt.so.1 is incorrect.
* I can initialize the runtime, using hsa\_init, but there is no GPU device. 
    * Answer: The /dev/kfd device is not properly initialized or it has the wrong permissions assigned to it. The command 'ls -l /dev/kfd' will list the permission 
  on the kfd device. The device /dev/kfd should exist and have 0666 permissions assigned to it. Consult the HSA driver documentation for information on how to configure the kfd device.

### Known Issues

* OKRA 32-bit binary is not available. Not tested and will be available in future
* HSAIL 0.95 to HSAIL 1.0P instruction fix up is not for all universal set of HSAIL instructions. So it is possible to see new compilation (assembling) errors. 
* More features like device query, linker capabilities do not exist with okra API. May be added in future if needed.
