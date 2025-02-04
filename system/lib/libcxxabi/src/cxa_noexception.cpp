//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//
//  This file implements the "Exception Handling APIs"
//  https://itanium-cxx-abi.github.io/cxx-abi/abi-eh.html
//
//===----------------------------------------------------------------------===//

// Support functions for the no-exceptions libc++ library

#include "cxxabi.h"

#include <exception>        // for std::terminate
#include "cxa_exception.h"
#include "cxa_handlers.h"

namespace __cxxabiv1 {

extern "C" {

void
__cxa_increment_exception_refcount(void *thrown_object) throw() {
    if (thrown_object != nullptr)
        std::terminate();
}

void
__cxa_decrement_exception_refcount(void *thrown_object) throw() {
    if (thrown_object != nullptr)
      std::terminate();
}


void *__cxa_current_primary_exception() throw() { return nullptr; }

void
__cxa_rethrow_primary_exception(void* thrown_object) {
    if (thrown_object != nullptr)
      std::terminate();
}

bool
__cxa_uncaught_exception() throw() { return false; }

unsigned int
__cxa_uncaught_exceptions() throw() { return 0; }

#if __EMSCRIPTEN__
// Under emscripten this code is also linked when building when
// DISABLE_EXCEPTION_CATCHING is set but DISABLE_EXCEPTION_THROWING is not.
// TODO(sbc): Perhaps just call std::terminate here. It could
// just be some test code that needs updating.
void *__cxa_allocate_exception(size_t thrown_size) _NOEXCEPT {
  char* allocation = (char*)malloc(thrown_size + sizeof(__cxa_exception));
  return allocation + sizeof(__cxa_exception);
}

static
inline
__cxa_exception*
cxa_exception_from_thrown_object(void* thrown_object)
{
    return static_cast<__cxa_exception*>(thrown_object) - 1;
}

//  Free a __cxa_exception object allocated with __cxa_allocate_exception.
void __cxa_free_exception(void *thrown_object) _NOEXCEPT {
    // Compute the size of the padding before the header.
    char *raw_buffer =
        ((char *)cxa_exception_from_thrown_object(thrown_object));
    free((void *)raw_buffer);
}
#endif

}  // extern "C"

// provide dummy implementations for the 'no exceptions' case.
uint64_t __getExceptionClass  (const _Unwind_Exception*)           { return 0; }
void     __setExceptionClass  (      _Unwind_Exception*, uint64_t) {}
bool     __isOurExceptionClass(const _Unwind_Exception*)           { return false; }

}  // abi
