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

#ifndef OKRACONTEXT_H
#define OKRACONTEXT_H
#include "common.h"   // includes jni.h for jxxxx args

// Abstract interface to an Okra Implementation
class OkraContext{
public:
	enum OkraStatus {
		OKRA_OK,
		OKRA_OTHER_ERROR
	};

	class Kernel {
	public:
		// various methods for setting different types of args into the arg stack
		virtual OkraStatus pushFloatArg(jfloat) = 0;
		virtual OkraStatus pushIntArg(jint) = 0;
		virtual OkraStatus pushBooleanArg(jboolean) = 0;
		virtual OkraStatus pushByteArg(jbyte) = 0;
		virtual OkraStatus pushLongArg(jlong) = 0;
		virtual OkraStatus pushDoubleArg(jdouble) = 0;
		virtual OkraStatus pushPointerArg(void *addr) = 0;
		virtual OkraStatus clearArgs() = 0;
		// allow a previously pushed arg to be changed
		virtual OkraStatus setPointerArg(int idx, void *addr) = 0;

		// setting number of dimensions and sizes of each
		virtual OkraStatus setLaunchAttributes(int dims, size_t *globalDims, size_t *localDims) = 0;

		// run a kernel and wait until complete
		virtual OkraStatus dispatchKernelWaitComplete() = 0;
	};

	// create a kernel object from the specified HSAIL text source and entrypoint
	virtual Kernel * createKernel(const char *source, const char *entryName) = 0;

	// create a kernel object from the specified Brig binary source and entrypoint
	virtual Kernel * createKernelFromBinary(const char *binary, size_t size, const char *entryName) = 0;

	// dispose of an environment including all programs
	virtual OkraStatus dispose() = 0;

	virtual OkraStatus registerArrayMemory(void *addr, jint lengthInBytes) = 0;

	void setVerbose(bool b) {verbose = b;}
	bool isVerbose() {return verbose;}

	DLLExport static OkraContext* Create();

	static bool isSimulator();

	static OkraStatus setCoherence(bool isCoherent);
	static bool getCoherence();

private:
	bool verbose;
};

extern "C" DLLExport void * vqueryLargest(void *addr, size_t *pSize, bool show);
extern "C" DLLExport void  commitAndRegisterWholeHeap(void *startAddr, void *endAddr);

#endif // OKRACONTEXT_H
