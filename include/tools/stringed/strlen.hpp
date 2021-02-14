
// [2021y-02m-14d] Idrisov Denis R.
#pragma once
#ifndef dTOOLS_STRLEN_CPP_USED_
#define dTOOLS_STRLEN_CPP_USED_ 100

#include <tools/features.hpp>
#include <tools/assert.hpp>

//==============================================================================
//==============================================================================

#if defined(dHAS_CPP17)
    dMESSAGE("tools/strlen: build for c++17 (or newer)")
    #include <tools/stringed/strlen/strlen-cpp17.hpp>
#elif defined(dHAS_CPP14)
    dMESSAGE("tools/strlen: build for c++14")
    #include <tools/stringed/strlen/strlen-cpp14.hpp>
#elif defined(dHAS_CPP11)
    dMESSAGE("tools/strlen: build for c++11")
    #include <tools/stringed/strlen/strlen-cpp11.hpp>
#else
    dMESSAGE("tools/strlen: build for pre11")
    #include <tools/stringed/strlen/strlen-pre11.hpp>
#endif

//==============================================================================
//==============================================================================
#endif // !dTOOLS_STRLEN_CPP_USED_

