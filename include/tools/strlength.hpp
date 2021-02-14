
// [2021y-02m-08d] Idrisov Denis R.
#pragma once
#ifndef dTOOLS_STRLENGTH_USED_
#define dTOOLS_STRLENGTH_USED_ 100

#include <tools/features.hpp>
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
    namespace stringed_v1
    {
        #define dATTRIBUTES_CPP11 dNODISCARD dCONSTEXPR_CPP11
        #define dATTRIBUTES_CPP14 dNODISCARD dCONSTEXPR_CPP14

        #define dTEMPLATE_CPP11 template<class s> dATTRIBUTES_CPP11
        #define dTEMPLATE_CPP14 template<class s> dATTRIBUTES_CPP14

        dTEMPLATE_CPP14 size_t strlen_pointer(s* text) dNOEXCEPT
        {
            dASSERT(text);
            const s* p = text;
            while (*p != 0)
                ++p;
            return static_cast<size_t>(p - text);
        }

        dTEMPLATE_CPP14 size_t strlength(s*& p)                dNOEXCEPT { return strlen_pointer(p); }
        dTEMPLATE_CPP14 size_t strlength(s* const& p)          dNOEXCEPT { return strlen_pointer(p); }
        dTEMPLATE_CPP14 size_t strlength(s* volatile& p)       dNOEXCEPT { return strlen_pointer(p); }
        dTEMPLATE_CPP14 size_t strlength(s* volatile const& p) dNOEXCEPT { return strlen_pointer(p); }

        dTEMPLATE_CPP11
        size_t strlength(const s& text) dNOEXCEPT 
            { return text.length(); }

        template<class ch, size_t n>
        dATTRIBUTES_CPP11
        size_t strlen_recursieve(const ch(&text)[n], const size_t i) dNOEXCEPT
        {
            dASSERT(i < n);
            namespace x = ::tools::stringed_v1;
            return text[i] != 0 ?
                x::strlen_recursieve(text, i + 1) : i;
        }

        #define dEXPRESSION(...) \
            typename ::tools::if_< (__VA_ARGS__), size_t >::type

        #define dSMALL_ARRAY dEXPRESSION(n <  256)
        #define dBIG_ARRAY   dEXPRESSION(n >= 256)

        template<class ch, size_t n>
        dATTRIBUTES_CPP11
        dSMALL_ARRAY strlength(const ch (&text)[n]) dNOEXCEPT
        {
            namespace x = ::tools::stringed_v1;
            return x::strlen_recursieve(text, 0);
        }

        #ifndef NDEBUG
        dCONSTEXPR_CPP14 size_t limit(const size_t i, const size_t n) dNOEXCEPT
        {
            dASSERT(n != 0 && i < n && 
                "tools::strlength: invalid null-terminator");
            return i;
        }
        #endif

        template<class ch, size_t n> 
        dATTRIBUTES_CPP14
        dBIG_ARRAY strlength(const ch (&text)[n]) dNOEXCEPT
        { 
            for (size_t i = 0; i != n; ++i)
                if (text[i] == 0)
                    return i;

            #ifdef NDEBUG
                return n;
            #else
                namespace x = ::tools::stringed_v1;
                return x::limit(n, n);
            #endif
        }

        #undef dEXPRESSION
        #undef dSMALL_ARRAY
        #undef dBIG_ARRAY

    } // namespace stringed_v1

    #ifdef dHAS_RVALUE_REFERENCES

        dTEMPLATE_CPP11 size_t strlength(s&& text) dNOEXCEPT
        { 
            return ::tools::stringed_v1::strlength(text);
        }

    #else

        dTEMPLATE_CPP11 size_t strlength(const s& text) dNOEXCEPT
        { 
            return ::tools::stringed_v1::strlength(text);
        }

    #endif // !dHAS_RVALUE_ARRAY

    #undef dATTRIBUTES_CPP11
    #undef dATTRIBUTES_CPP14
    #undef dTEMPLATE_CPP11
    #undef dTEMPLATE_CPP14

} // namespace tools 
//==============================================================================
//==============================================================================
#endif // !dTOOLS_STRLENGTH_USED_

