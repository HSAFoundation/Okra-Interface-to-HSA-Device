#Set the below environment variables appropriately

#This should point to top of the directory obtained after downloading from this github repo: https://github.com/HSAFoundation/Okra-Interface-to-HSA-Device
HSA_OKRA_PATH=<EDIT PATH>

#This should point to top of the directory obtained after downloading from this github repo: https://github.com/HSAFoundation/HSA-Runtime-AMD
HSA_RUNTIME_PATH=<EDIT PATH>

#This should point to the libhsakmt directory obtained after downloading from this github repo: https://github.com/HSAFoundation/HSA-Drivers-Linux-AMD/tree/master/kfd-0.8/libhsakmt
HSA_KMT_PATH=<EDIT PATH>

#OKRA has been tested only with 64 bit, so make sure you point to 64-bit binaries of HSA Runtime and KMT libraries
export LD_LIBRARY_PATH=$HSA_OKRA_PATH/okra/dist/bin:$HSA_RUNTIME_PATH/lib/x86_64:$HSA_KMT_PATH/lnx64a:$LD_LIBRARY_PATH
