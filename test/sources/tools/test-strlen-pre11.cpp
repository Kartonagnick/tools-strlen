
// [2021y-02m-14d] Idrisov Denis R.
#include <mygtest/modern.hpp>
//==============================================================================
//==============================================================================

#ifdef TEST_TOOLS_STRLEN

#include <tools/features.hpp>
#if !defined(dHAS_CPP11)

#define dTEST_COMPONENT tools
#define dTEST_METHOD strlen
#define dTEST_TAG pre11

#include <tools/strlen.hpp>
#include "test-staff.hpp"

#ifdef dHAS_RVALUE_ARRAY
    dMESSAGE("[test][pre11] tools/strlen.hpp: enabled -> dHAS_RVALUE_ARRAY")
#else
    dMESSAGE("[test][pre11] tools/strlen.hpp: disabled -> dHAS_RVALUE_ARRAY")
#endif

namespace me = ::tools;
using namespace staff;
//==============================================================================
//==============================================================================

namespace test_strlen_pre11
{
    template<class type> void array()
    {
        type arr[] = { '\0' };
        type (&ref)[1] = arr;
        ASSERT_TRUE(me::strlen(arr) == 0);
        ASSERT_TRUE(me::strlen(ref) == 0);
        #ifdef dHAS_RVALUE_ARRAY
            type (&&rval)[1] = std::move(ref);
            ASSERT_TRUE(me::strlen(rval) == 0);
            ASSERT_TRUE(me::strlen(arr ) == 0);
            ASSERT_TRUE(me::strlen(ref ) == 0);
            ASSERT_TRUE(me::strlen(rval) == 0);
        #endif
    }
	
    template<class str> void string()
    {
        typedef typename str::value_type ch;

        ch arr[2]  = {};
        str txt    = arr;
        str& ref   = txt;

        ASSERT_TRUE(me::strlen(txt ) == 0);
        ASSERT_TRUE(me::strlen(ref ) == 0);

        #ifdef dHAS_RVALUE_REFERENCES
        str&& rval = std::move(txt);
        ASSERT_TRUE(me::strlen(rval) == 0);

        ASSERT_TRUE(me::strlen(std::move(txt )) == 0);
        ASSERT_TRUE(me::strlen(std::move(ref )) == 0);
        ASSERT_TRUE(me::strlen(std::move(rval)) == 0);
        #endif
    }

    template<class ptr> void pointer()
    {
        ptr val    = 0;
        ptr& ref   = val;
        size_t len = 0;
        ASSERT_DEATH_DEBUG(len = me::strlen(val ));
        ASSERT_DEATH_DEBUG(len = me::strlen(ref ));

        #ifdef dHAS_RVALUE_REFERENCES
        ptr&& rval = std::move(ref);
        ASSERT_DEATH_DEBUG(len = me::strlen(rval));

        ASSERT_DEATH_DEBUG(len = me::strlen(std::move(val )));
        ASSERT_DEATH_DEBUG(len = me::strlen(std::move(ref )));
        ASSERT_DEATH_DEBUG(len = me::strlen(std::move(rval)));
        #endif

        (void) len;
    }

    #define dINITIALIZE(initial)                        \
        enum { size = sizeof(text) / sizeof(text[0]) }; \
        enum { len = size - 1 };                        \
        ch initial[size];                               \
        for (size_t i = 0; i != size; ++i)              \
            initial[i] = static_cast<ch>(text[i]);      \
        ASSERT_TRUE(initial[len] == 0)
    
     
    template<class ch, class type, class str> void array(const str& text)
    {
        dINITIALIZE(arr);
        type (&ref)[size] = arr;

        ASSERT_TRUE(me::strlen(arr) == len);
        ASSERT_TRUE(me::strlen(ref) == len);
        #ifdef dHAS_RVALUE_ARRAY
            type (&&rval)[size] = std::move(ref);
            ASSERT_TRUE(me::strlen(rval) == len);
            ASSERT_TRUE(me::strlen(std::move(arr )) == len);
            ASSERT_TRUE(me::strlen(std::move(ref )) == len);
            ASSERT_TRUE(me::strlen(std::move(rval)) == len);
        #endif
    }


    template<class str, class arr> void string(const arr& text)
    {
        typedef typename str::value_type ch;
        dINITIALIZE(initial);
        str txt    = initial;
        str& ref   = txt;

        ASSERT_TRUE(me::strlen(txt ) == len);
        ASSERT_TRUE(me::strlen(ref ) == len);

        #ifdef dHAS_RVALUE_REFERENCES
        str&& rval = std::move(txt);
        ASSERT_TRUE(me::strlen(rval) == len);

        ASSERT_TRUE(me::strlen(std::move(txt )) == len);
        ASSERT_TRUE(me::strlen(std::move(ref )) == len);
        ASSERT_TRUE(me::strlen(std::move(rval)) == len);
        #endif
    }


    template<class ch, class ptr, class arr> 
    void pointer(const arr& text)
    {
        dINITIALIZE(initial);
        ptr val    = initial;
        ptr& ref   = val;
        ASSERT_TRUE(me::strlen(val ) == len);
        ASSERT_TRUE(me::strlen(ref ) == len);

        #ifdef dHAS_RVALUE_REFERENCES
        ptr&& rval = std::move(ref);
        ASSERT_TRUE(me::strlen(rval) == len);

        ASSERT_TRUE(me::strlen(std::move(val )) == len);
        ASSERT_TRUE(me::strlen(std::move(ref )) == len);
        ASSERT_TRUE(me::strlen(std::move(rval)) == len);
        #endif
    }

} // namespace test_strlen_pre11
namespace test = test_strlen_pre11;

//..............................................................................

namespace test_strlen_pre11
{
    template<class ch> void array_case()
    {
        test::array<ch>();
        test::array<const ch>();
        test::array<volatile ch>();
        test::array<volatile const ch>();
    }

    template<class str> void string_case()
    {
        test::string<str_t>();
        test::string<const str_t>();
     // test::string<volatile str_t>(); <--- not support
    }

    template<class ch> void pointer_case()
    {
        test::pointer<ch*>();
       
        test::pointer<ch* const>();
        test::pointer<ch* volatile>();
        test::pointer<ch* volatile const>();
       
        test::pointer<const ch*>();
        test::pointer<volatile ch*>();
        test::pointer<volatile const ch*>();
       
        test::pointer<const ch* const>();
        test::pointer<volatile ch* const >();
        test::pointer<volatile const ch* const >();
       
        test::pointer<const ch* volatile>();
        test::pointer<volatile ch* volatile >();
        test::pointer<volatile const ch* volatile >();
       
        test::pointer<const ch* volatile const>();
        test::pointer<volatile ch* volatile const>();
        test::pointer<volatile const ch* volatile const>();
    }

}// namespace test_strlen_pre11

//..............................................................................

namespace test_strlen_pre11
{

    template<class ch, class arr>
    void array_case(const arr& text)
    {
        test::array<ch, ch>(text);
        test::array<ch, const ch>(text);
        test::array<ch, volatile ch>(text);
        test::array<ch, volatile const ch>(text);
    }

    template<class ch, class arr>
    void string_case(const arr& text)
    {
        test::string<str_t>(text);
        test::string<const str_t>(text);
     // test::string<volatile str_t>(); <--- not support
    }

    template<class ch, class arr>
    void pointer_case(const arr& text)
    {
        test::pointer<ch, ch*>(text);
       
        test::pointer<ch, ch* const>(text);
        test::pointer<ch, ch* volatile>(text);
        test::pointer<ch, ch* volatile const>(text);
       
        test::pointer<ch, const ch*>(text);
        test::pointer<ch, volatile ch*>(text);
        test::pointer<ch, volatile const ch*>(text);
       
        test::pointer<ch, const ch* const>(text);
        test::pointer<ch, volatile ch* const >(text);
        test::pointer<ch, volatile const ch* const >(text);
       
        test::pointer<ch, const ch* volatile>(text);
        test::pointer<ch, volatile ch* volatile >(text);
        test::pointer<ch, volatile const ch* volatile >(text);
       
        test::pointer<ch, const ch* volatile const>(text);
        test::pointer<ch, volatile ch* volatile const>(text);
        test::pointer<ch, volatile const ch* volatile const>(text);
    }

} // namespace test_strlen_pre11

//==============================================================================
//==============================================================================

//--- array
TEST_COMPONENT(000)
{
    test::array_case<char>();
    test::array_case<wchar_t>();

    test::array_case<char>("");
    test::array_case<wchar_t>("");
}

TEST_COMPONENT(001)
{
    test::array_case<char>("12");
    test::array_case<wchar_t>("12");
}

//--- string
TEST_COMPONENT(002)
{
    test::string_case<str_t>();
    test::string_case<str_w>();
    test::string_case<str_i>();

    test::string_case<str_t>("");
    test::string_case<str_w>("");
    test::string_case<str_i>("");
}
TEST_COMPONENT(003)
{
    test::string_case<str_t>("12");
    test::string_case<str_w>("12");
    test::string_case<str_i>("12");
}

//--- null pointer
#ifndef NDEBUG
TEST_COMPONENT(004)
{
    test::pointer_case<char>();
    test::pointer_case<wchar_t>();
}
#endif

//--- pointer
TEST_COMPONENT(005)
{
    test::pointer_case<char>("");
    test::pointer_case<wchar_t>("");

    test::pointer_case<char>("12");
    test::pointer_case<wchar_t>("12");
}

//==============================================================================
//==============================================================================
#endif // !defined(dHAS_CPP11)
#endif // !TEST_TOOLS_STRLEN