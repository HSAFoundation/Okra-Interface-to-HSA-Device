OKRA is a runtime library that enables applications to do compute offloads to 
HSA-enabled GPUs.

OKRA binaries:
==============
okra/dist
	okra.jar

okra/dist/bin
	libokra_x86_64.so
	libnewhsacore64.so
	libamdhsacl64.so

OKRA public headers:
====================
okra/dist/include
	okraContext.h

OKRA samples:
=============
okra/samples/dist
	Squares (along with Squares.hsail)

Running OKRA samples
====================
There are two pre-requisites that should be satisfied to successfuly use OKRA 
runtime library and samples.
	
	1. A working setup of an HSA platform - Interested reader should refer to
	(~/cite John's public location)
	2. Ubuntu 13.10 linux with HSA drivers - Interested reader should refer to
	(~/cite John's public location)

To run OKRA samples:
	$cd okra/samples
	$./runSquares.sh

Using other software infrastructures on top of OKRA 
===================================================
1. If you want aparapi to use OKRA, refer to https://code.google.com/p/aparapi/wiki/HSAEnablementOfLambdaBranch
2. If you want Sumatra (openJDK) to use OKRA, refer to https://wiki.openjdk.java.net/display/Sumatra/Main
