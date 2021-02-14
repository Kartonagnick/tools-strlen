
// [2021y-02m-14d] Idrisov Denis R.
#pragma once
#ifndef dTOOLS_STRLEN_CPP11_USED_
#define dTOOLS_STRLEN_CPP11_USED_ 100

#ifdef dHAS_CPP14
    #error use "strlen-cpp14.hpp" (or newer)
#endif

#include <tools/assert.hpp>

//==============================================================================
//=== if_ ======================================================================
#ifndef dTOOLS_IF_USED_ 
#define dTOOLS_IF_USED_
namespace tools 
{
    template <bool, class ret = void> struct if_;
    template <class ret> struct if_<true, ret>
        { typedef ret type; };

} // namespace tools 
#endif // !dTOOLS_IF_USED_
//==============================================================================
//==============================================================================
namespace tools
{
    #define dNOEXCEPT noexcept
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

        template<class ch, size_t n>
        constexpr size_t 
        strlen(const ch(&text)[n], const size_t beg) dNOEXCEPT
        {
            dASSERT(beg < n);
            return text[beg] != 0 ?
                ::tools::old::strlen(text, beg + 1) :
                beg;
        }

        #define dEXPRESSION(...) \
            typename ::tools::if_< (__VA_ARGS__), size_t >::type

        #define dSMALL_ARRAY dEXPRESSION(n <  256)
        #define dBIG_ARRAY   dEXPRESSION(n >= 256)

        #ifndef NDEBUG
        inline size_t limit(const size_t i, const size_t n) dNOEXCEPT
        {
            dASSERT(n != 0 && i < n &&
                "tools::strlen: invalid null-terminator");
            return i;
        }
        #endif

    } // namespace old

    dTEMPLATE size_t strlen(s*& p)                dNOEXCEPT { return old::strlen(p); }
    dTEMPLATE size_t strlen(s* const& p)          dNOEXCEPT { return old::strlen(p); }
    dTEMPLATE size_t strlen(s* volatile& p)       dNOEXCEPT { return old::strlen(p); }
    dTEMPLATE size_t strlen(s* volatile const& p) dNOEXCEPT { return old::strlen(p); }


    template<class ch, size_t n> inline
    dBIG_ARRAY strlen(const ch(&text)[n]) dNOEXCEPT
    {
        const auto* ptr = text;
        const size_t len = old::strlen(ptr);
        #ifdef NDEBUG
            return len;
        #else
            return old::limit(len, n);
        #endif
    }

    template<class ch, size_t n> constexpr
    dSMALL_ARRAY strlen(const ch (&text)[n]) dNOEXCEPT
    {
        return ::tools::old::strlen(text, 0);
    }

    dTEMPLATE constexpr 
    size_t strlen(const s& text) dNOEXCEPT
    { 
        return text.length();
    }

    //--- rvalue

    dTEMPLATE constexpr
    size_t strlen(const s&& text) dNOEXCEPT
    {
        return text.length();
    }

    dTEMPLATE size_t strlen(s*&& p)                dNOEXCEPT { return old::strlen(p); }
    dTEMPLATE size_t strlen(s* const&& p)          dNOEXCEPT { return old::strlen(p); }
    dTEMPLATE size_t strlen(s* volatile&& p)       dNOEXCEPT { return old::strlen(p); }
    dTEMPLATE size_t strlen(s* volatile const&& p) dNOEXCEPT { return old::strlen(p); }

    #ifdef dHAS_RVALUE_ARRAY
    template<class ch, size_t n> inline
    dBIG_ARRAY strlen(const ch(&&text)[n]) dNOEXCEPT
    {
        return ::tools::strlen(text);
    }

    template<class ch, size_t n> constexpr
    dSMALL_ARRAY strlen(const ch(&&text)[n]) dNOEXCEPT
    {
        return ::tools::strlen(text);
    }
    #endif

    #undef dEXPRESSION
    #undef dSMALL_ARRAY
    #undef dBIG_ARRAY
    #undef dTEMPLATE

} // namespace tools 

//==============================================================================
//==============================================================================
#endif // !dTOOLS_STRLEN_CPP11_USED_

