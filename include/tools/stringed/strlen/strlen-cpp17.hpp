
// [2021y-02m-14d] Idrisov Denis R.
#pragma once
#ifndef dTOOLS_STRLEN_CPP17_USED_
#define dTOOLS_STRLEN_CPP17_USED_ 100

#ifdef dHAS_CPP20
    #error use "strlen-cpp20.hpp" (or newer)
#endif

#include <tools/assert.hpp>

//==============================================================================
//==============================================================================
namespace tools
{
    #define dNOEXCEPT noexcept
    #define dHAS_RVALUE_ARRAY 1

    #define dTEMPLATE template<class s> constexpr

    namespace cpp14
    {
        dTEMPLATE size_t strlen_(const s* text) dNOEXCEPT
        {
            dASSERT(text);
            const s* p = text;
            while (*p != 0)
                ++p;
            return static_cast<size_t>(p - text);
        }

        dTEMPLATE size_t strlen(const s* text) dNOEXCEPT
        {
            dASSERT(text);
            return cpp14::strlen_(text);
        }

        constexpr size_t strlen(const char* text) dNOEXCEPT
        {
            dASSERT(text);
            return __builtin_strlen(text);
        }

        constexpr size_t strlen(const wchar_t* text) dNOEXCEPT
        {
            dASSERT(text);
            return __builtin_wcslen(text);
        }

        #if __cpp_char8_t
            size_t strlen(const char8_t* text) dNOEXCEPT
            {
                dASSERT(text);
                #ifdef _HAS_U8_INTRINSICS
                    return __builtin_u8strlen(text);
                #else
                    return cpp14::strlen_(text);
                #endif
            }
        #endif // !__cpp_char8_t

    } // namespace cpp14

    dTEMPLATE size_t strlen(s*& p)                dNOEXCEPT { return cpp14::strlen(p); }
    dTEMPLATE size_t strlen(s* const& p)          dNOEXCEPT { return cpp14::strlen(p); }
    dTEMPLATE size_t strlen(s* volatile& p)       dNOEXCEPT { return cpp14::strlen(p); }
    dTEMPLATE size_t strlen(s* volatile const& p) dNOEXCEPT { return cpp14::strlen(p); }

    template<class ch, size_t n> constexpr
    size_t strlen(const ch(&text)[n]) dNOEXCEPT
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

    #ifdef dHAS_RVALUE_ARRAY
    dTEMPLATE size_t strlen(s*&& p)                dNOEXCEPT { return cpp14::strlen(p); }
    dTEMPLATE size_t strlen(s* const&& p)          dNOEXCEPT { return cpp14::strlen(p); }
    dTEMPLATE size_t strlen(s* volatile&& p)       dNOEXCEPT { return cpp14::strlen(p); }
    dTEMPLATE size_t strlen(s* volatile const&& p) dNOEXCEPT { return cpp14::strlen(p); }

    template<class ch, size_t n> constexpr
    size_t strlen(const ch(&&text)[n]) dNOEXCEPT
    {
        return ::tools::strlen(text);
    }
    #endif

    #undef dTEMPLATE

} // namespace tools 

//==============================================================================
//==============================================================================
#endif // !dTOOLS_STRLEN_CPP17_USED_

