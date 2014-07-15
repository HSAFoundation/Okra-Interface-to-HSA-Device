/*
OKRA Runtime C interface
*/

#ifndef OKRA_H
#define OKRA_H

#include "stdint.h"
#include "stddef.h"

#if defined (_WIN32)
   #ifndef __EXPORT__
      #define OKRA_API __declspec(dllimport)
   #else
      #define OKRA_API __declspec(dllexport)
   #endif
#else
   #define OKRA_API 
#endif

#ifdef __cplusplus
extern "C" {
#endif

//opaque okra context
typedef uint64_t okra_context_t;

//opaque okra kernel
typedef uint64_t okra_kernel_t;

//launch attributes that defines execution range
typedef struct okra_range_s
{
  uint32_t dimension;        //max value is 3
  uint32_t global_size[3];
  uint32_t group_size[3];
  uint32_t reserved;         //For future use
} okra_range_t;


//This is the list of errors that okra supports
//@Note: Will add more error codes as needed
typedef enum okra_status_t {
   OKRA_SUCCESS=0,
   OKRA_CONTEXT_NO_DEVICE_FOUND,
   OKRA_CONTEXT_QUEUE_CREATION_FAILED,
   OKRA_SET_MEMORY_POLICY_FAILED,
   OKRA_MEMORY_REGISTRATION_FAILED,
   OKRA_MEMORY_DEREGISTRATION_FAILED,
   OKRA_CONTEXT_CREATE_FAILED,
   OKRA_CONTEXT_ALREADY_EXIST,
   OKRA_KERNEL_HSAIL_ASSEMBLING_FAILED,
   OKRA_KERNEL_FINALIZE_FAILED,
   OKRA_KERNEL_CREATE_FAILED,
   OKRA_KERNEL_ELF_INITIALIZATION_FAILED,
   OKRA_KERNEL_INVALID_ELF_CONTAINER,
   OKRA_KERNEL_INVALID_SECTION_HEADER,
   OKRA_KERNEL_MISSING_STRING_SECTION,
   OKRA_KERNEL_MISSING_DIRECTIVE_SECTION,
   OKRA_KERNEL_MISSING_CODE_SECTION,
   OKRA_KERNEL_MISSING_OPERANDS_SECTION,
   OKRA_KERNEL_MISSING_DEBUG_SECTION,
   OKRA_LOAD_BRIG_FAILED,
   OKRA_UNLOAD_BRIG_FAILED,
   OKRA_KERNEL_CREATE_FROM_BINARY_FAILED,
   OKRA_KERNEL_PUSH_KERNARG_FAILED,
   OKRA_KERNEL_CLEARARG_FAILED,
   OKRA_RANGE_INVALID_DIMENSION,
   OKRA_RANGE_INVALID_GLOBAL_SIZE,
   OKRA_RANGE_INVALID_GROUP_SIZE,
   OKRA_EXECUTE_FAILED,
   OKRA_DISPOSE_FAILED,
   OKRA_INVALID_ARGUMENT,
   OKRA_UNKNOWN
}okra_status_t;

//Get a okra context - does device detection, command queue creation internally
//Note context is singleton at the moment - may change later if requirement
//changes
//This means you have one context, device and queue per process, but sufficient
//for most common cases
okra_status_t OKRA_API okra_get_context(okra_context_t** context);

//create kernel that can be dispatched - takes in hsail text as input and creates
// a kernel - does HSAIL assembling and finalize
okra_status_t OKRA_API okra_create_kernel(okra_context_t* context, 
                        const char *hsail_source, const char *entryName, 
                        okra_kernel_t **kernel);

//create kernel that can be dispatched - takes in binary as input and creates a
//kernel
okra_status_t OKRA_API okra_create_kernel_from_binary(okra_context_t *context, 
                        const char *binary, size_t size, const char *entryName,
                        okra_kernel_t **kernel);

//Following are set of apis to push kernel args to the kernel
//for pointers and objects
okra_status_t OKRA_API okra_push_pointer(okra_kernel_t* kernel, 
                        void* address);

//unsigned char is equivalent for jboolean-use this for passing boolean 
//if using from java world
okra_status_t OKRA_API okra_push_boolean(okra_kernel_t* kernel, 
                        unsigned char value);

//char is equivalent for jbyte-use this for passing byte if using
//from java world
okra_status_t OKRA_API okra_push_byte(okra_kernel_t* kernel, 
                        char value);   

//use this if passing jdouble from java world
okra_status_t OKRA_API okra_push_double(okra_kernel_t* kernel, 
                        double value);

//use this if passing jfloat from java world
okra_status_t OKRA_API okra_push_float(okra_kernel_t* kernel, 
                        float value);

//use this if passing jint from java world
okra_status_t OKRA_API okra_push_int(okra_kernel_t* kernel, 
                        int value);

//use this if passing jlong from java world
okra_status_t OKRA_API okra_push_long(okra_kernel_t* kernel, 
                        long value);

// Call clearargs between executions of a kernel before setting the new args
okra_status_t OKRA_API okra_clear_args(okra_kernel_t* kernel);
//end of kernel arg related APIs

//execute the kernel - takes kernel, execution range as input
//This is a synchronous call - returns only after kernel completion
//If the user pass 0's for group size, the runtime will choose one
okra_status_t OKRA_API okra_execute_kernel(okra_context_t* context, okra_kernel_t* kernel, okra_range_t* range);

//cleanup kernel
okra_status_t OKRA_API okra_dispose_kernel(okra_kernel_t* kernel);

//cleanup any resource allocated by okra context
okra_status_t OKRA_API okra_dispose_context(okra_context_t* context);


#ifdef __cplusplus
} // end of extern "C"
#endif

#endif //OKRA_H
