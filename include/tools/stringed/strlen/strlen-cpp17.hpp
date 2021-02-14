
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
    namespace cpp17
    {
        #define dNOEXCEPT noexcept
        #define dTEMPLATE template<class s> constexpr

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
            return cpp17::strlen_(text);
        }

        constexpr size_t strlen(const char* text) dNOEXCEPT
        {
            dASSERT(text);
            return __builtin_strlen(text);
        }

        constexpr size_t strlen(const wchar_t* text) dNOEXCEPT
        {
            dASSERT(text);
            #ifdef _MSC_VER
                return __builtin_wcslen(text);
            #else
                return cpp17::strlen_(text);
            #endif
        }

        #if defined(__cpp_char8_t) && __cpp_char8_t
            size_t strlen(const char8_t* text) dNOEXCEPT
            {
                dASSERT(text);
                #ifdef _HAS_U8_INTRINSICS
                    return __builtin_u8strlen(text);
                #else
                    return cpp17::strlen_(text);
                #endif
            }
        #endif // !__cpp_char8_t

        constexpr size_t limit(const size_t i, const size_t n) dNOEXCEPT
        {
            (void)n;
            dASSERT(n != 0 && i < n && 
                "tools::strlen: invalid null-terminator");
            return i;
        }

    } // namespace cpp17

    namespace cpp17_detail
    {
        dTEMPLATE size_t strlen(s*& p)                dNOEXCEPT { return cpp17::strlen(p); }
        dTEMPLATE size_t strlen(s* const& p)          dNOEXCEPT { return cpp17::strlen(p); }
        dTEMPLATE size_t strlen(s* volatile& p)       dNOEXCEPT { return cpp17::strlen(p); }
        dTEMPLATE size_t strlen(s* volatile const& p) dNOEXCEPT { return cpp17::strlen(p); }

        template<class ch, size_t n> constexpr
        size_t strlen(const ch(&text)[n]) dNOEXCEPT
        {
            return cpp17::limit(cpp17::strlen(&text[0]), n);
        }

        dTEMPLATE size_t strlen(const s& text) dNOEXCEPT
        { 
            return text.length();
        }

        #undef dTEMPLATE

    }  // namespace cpp17_detail

    template<class s> constexpr
    size_t strlen(s&& text) dNOEXCEPT
        { return cpp17_detail::strlen(text); }

} // namespace tools 

//==============================================================================
//==============================================================================
#endif // !dTOOLS_STRLEN_CPP17_USED_

