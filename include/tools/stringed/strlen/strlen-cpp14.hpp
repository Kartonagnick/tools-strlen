
// [2021y-02m-14d] Idrisov Denis R.
#pragma once
#ifndef dTOOLS_STRLEN_CPP14_USED_
#define dTOOLS_STRLEN_CPP14_USED_ 100

#ifdef dHAS_CPP17
    #error use "strlen-cpp17.hpp" (or newer)
#endif

#include <tools/assert.hpp>

//==============================================================================
//==============================================================================
namespace tools
{
    #define dNOEXCEPT noexcept
    #define dTEMPLATE template<class s> constexpr

    namespace cpp14
    {
        dTEMPLATE size_t strlen(s* text) dNOEXCEPT
        {
            dASSERT(text);
            const s* p = text;
            while (*p != 0)
                ++p;
            return static_cast<size_t>(p - text);
        }

    } // namespace cpp14

    dTEMPLATE size_t strlen(s*& p)                dNOEXCEPT { return cpp14::strlen(p); }
    dTEMPLATE size_t strlen(s* const& p)          dNOEXCEPT { return cpp14::strlen(p); }
    dTEMPLATE size_t strlen(s* volatile& p)       dNOEXCEPT { return cpp14::strlen(p); }
    dTEMPLATE size_t strlen(s* volatile const& p) dNOEXCEPT { return cpp14::strlen(p); }

    template<class ch, size_t n> 
    constexpr size_t strlen(const ch(&text)[n]) dNOEXCEPT
    {
        for (size_t i = 0; i != n; ++i)
            if (text[i] == 0)
                return i;
        dASSERT(false && "tools::strlen: invalid null-terminator");
        return n;
    }

    dTEMPLATE size_t strlen(const s& text) dNOEXCEPT
    { 
        return text.length();
    }

    dTEMPLATE size_t strlen(s*&& p)                dNOEXCEPT { return cpp14::strlen(p); }
    dTEMPLATE size_t strlen(s* const&& p)          dNOEXCEPT { return cpp14::strlen(p); }
    dTEMPLATE size_t strlen(s* volatile&& p)       dNOEXCEPT { return cpp14::strlen(p); }
    dTEMPLATE size_t strlen(s* volatile const&& p) dNOEXCEPT { return cpp14::strlen(p); }

    #ifdef dHAS_RVALUE_ARRAY
    template<class ch, size_t n> 
    constexpr size_t strlen(const ch(&&text)[n]) dNOEXCEPT
    {
        return ::tools::strlen(text);
    }
    #endif

    #undef dTEMPLATE

} // namespace tools 

//==============================================================================
//==============================================================================
#endif // !dTOOLS_STRLEN_CPP14_USED_

