
// [2021y-02m-14d] Idrisov Denis R.
#pragma once
#ifndef dTOOLS_STRLEN_PRE11_USED_
#define dTOOLS_STRLEN_PRE11_USED_ 100

#include <tools/features.hpp>
#include <tools/assert.hpp>

#ifdef dHAS_CPP11
    #error use "strlen-cpp11.hpp" (or newer)
#endif

//==============================================================================
//==============================================================================
namespace tools
{
    #define dTEMPLATE template<class s> inline

    namespace old
    {
        dTEMPLATE size_t strlen(s* text) dNOEXCEPT
        {
            dASSERT(text);
            const s* p = text;
            while (*p != 0)
                ++p;
            return static_cast<size_t>(p - text);
        }

        size_t strlen(char*    text) dNOEXCEPT;
        size_t strlen(wchar_t* text) dNOEXCEPT;

    } // namespace old

    dTEMPLATE size_t strlen(s*& p)                dNOEXCEPT { return old::strlen(p); }
    dTEMPLATE size_t strlen(s* const& p)          dNOEXCEPT { return old::strlen(p); }
    dTEMPLATE size_t strlen(s* volatile& p)       dNOEXCEPT { return old::strlen(p); }
    dTEMPLATE size_t strlen(s* volatile const& p) dNOEXCEPT { return old::strlen(p); }

    template<class ch, size_t n> 
    inline size_t strlen(const ch(&text)[n]) dNOEXCEPT
    {
        return ::tools::old::strlen(text);
    }

    dTEMPLATE size_t strlen(const s& text) dNOEXCEPT
    { 
        return text.length();
    }

    #ifdef dHAS_RVALUE_REFERENCES
    dTEMPLATE size_t strlen(s*&& p)                dNOEXCEPT { return old::strlen(p); }
    dTEMPLATE size_t strlen(s* const&& p)          dNOEXCEPT { return old::strlen(p); }
    dTEMPLATE size_t strlen(s* volatile&& p)       dNOEXCEPT { return old::strlen(p); }
    dTEMPLATE size_t strlen(s* volatile const&& p) dNOEXCEPT { return old::strlen(p); }
    #endif

    #ifdef dHAS_RVALUE_ARRAY
    template<class ch, size_t n> 
    inline size_t strlen(const ch(&&text)[n]) dNOEXCEPT
    {
        return ::tools::strlen(text);
    }
    #endif

    #undef dTEMPLATE

} // namespace tools 

//==============================================================================
//==============================================================================

#endif // !dTOOLS_STRLEN_PRE11_USED_

