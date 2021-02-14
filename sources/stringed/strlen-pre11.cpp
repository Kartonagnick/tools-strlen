
// [2021y-02m-14d] Idrisov Denis R.

#include <tools/assert.hpp>
#include <tools/features.hpp>
#include <cstring>
#include <cwchar>

//==============================================================================
//==============================================================================

namespace tools 
{
    namespace old
    {
        size_t strlen(char* text) dNOEXCEPT
        {
            dASSERT(text);

            #ifdef _MSC_VER
                return ::std::strlen(text);
            #else
                return __builtin_strlen(text);
            #endif
        }

        size_t strlen(wchar_t* text) dNOEXCEPT
        {
            dASSERT(text);
            return ::std::wcslen(text);
        }

    } // namespace old
} // namespace tools 

//==============================================================================
//==============================================================================
