// University of Illinois/NCSA
// Open Source License
// 
// Copyright (c) 2013, Advanced Micro Devices, Inc.
// All rights reserved.
// 
// Developed by:
// 
//     Runtimes Team
// 
//     Advanced Micro Devices, Inc
// 
//     www.amd.com
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal with
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
// of the Software, and to permit persons to whom the Software is furnished to do
// so, subject to the following conditions:
// 
//     * Redistributions of source code must retain the above copyright notice,
//       this list of conditions and the following disclaimers.
// 
//     * Redistributions in binary form must reproduce the above copyright notice,
//       this list of conditions and the following disclaimers in the
//       documentation and/or other materials provided with the distribution.
// 
//     * Neither the names of the LLVM Team, University of Illinois at
//       Urbana-Champaign, nor the names of its contributors may be used to
//       endorse or promote products derived from this Software without specific
//       prior written permission.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
// CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS WITH THE
// SOFTWARE.
//===----------------------------------------------------------------------===//

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
   OKRA_KERNEL_MISSING_DATA_SECTION,
   OKRA_KERNEL_MISSING_CODE_SECTION,
   OKRA_KERNEL_MISSING_OPERAND_SECTION,
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
//Dimensions:
//assert(range->dimension >=1 && range->dimension <=3)
//Global Size:
// 0 for global size any dimension is invalid, should be atleast 1. 
//Group size:
//For instance, this is valid: group_size[0]=x;group_size[1]=y;group_size[2] = z; where x,y,z is >=1
//However assert(group_size[0] * group_size[1] * group_size[2] <= 2048)
//This is valid too: group_size[0]=group_size[1]=group_size[2]=0; - runtime will choose an 
//appropriate size in this case, depending on the number of dimensions
//This set of input is invalid: If dimension=2, then group_size[0]=256, group_size[1]=group_size[2]=0;
//Either pass required group_size for each valid dimension or let the runtime choose group size for each
//valid dimension
okra_status_t OKRA_API okra_execute_kernel(okra_context_t* context, okra_kernel_t* kernel, okra_range_t* range);

//cleanup kernel
okra_status_t OKRA_API okra_dispose_kernel(okra_kernel_t* kernel);

//cleanup any resource allocated by okra context
okra_status_t OKRA_API okra_dispose_context(okra_context_t* context);


#ifdef __cplusplus
} // end of extern "C"
#endif

#endif //OKRA_H
