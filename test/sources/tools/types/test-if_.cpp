
// [2021y-02m-09d] Idrisov Denis R.
#include <mygtest/modern.hpp>
//==============================================================================
//==============================================================================

#ifdef TEST_TOOLS_IF_

#define dTEST_COMPONENT tools, types
#define dTEST_METHOD if_
#define dTEST_TAG tdd

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

namespace me = ::tools;
//==============================================================================
//==============================================================================

namespace test_if_
{
    template<class t, class u> struct is_same
    {
        enum { value = false }; 
    };

    template<class t> struct is_same<t, t>
    { 
        enum { value = true  };
    };

    template<class t> struct check
    {
        enum { val = is_same<t, int>::value };
        typedef typename me::if_<val, char>::type
             type;
    };

    #define dENABLE_FOR(t) \
        typename me::if_< is_same<t, int>::value, bool >::type

    #define dDISABLE_FOR(t) \
        typename me::if_< !is_same<t, int>::value, bool >::type 

    template<class t> dENABLE_FOR(t)  case_1(t) { return true ; }
    template<class t> dDISABLE_FOR(t) case_1(t) { return false; }

    #undef dDISABLE_FOR
    #undef dENABLE_FOR

    #ifdef dHAS_TEMPLATE_FUNCTION_DEFAULT_PARAM
        #define dENABLE_FOR(t) \
            typename me::if_< is_same<t, int>::value >::type* = nullptr

        #define dDISABLE_FOR(t) \
            typename me::if_< !is_same<t, int>::value >::type* = nullptr

        template<class t, dENABLE_FOR(t) > bool case_2(t) { return true ; }
        template<class t, dDISABLE_FOR(t)> bool case_2(t) { return false; }

        #undef dDISABLE_FOR
        #undef dENABLE_FOR
    #endif

} // namespace test_if_
using namespace test_if_;

//==============================================================================
//==============================================================================

TEST_COMPONENT(000)
{
    const bool ok = is_same<check<int>::type, char>::value;
    ASSERT_TRUE(ok);
}
TEST_COMPONENT(001)
{
    ASSERT_TRUE( case_1( 1 ));
    ASSERT_TRUE(!case_1('a'));
}

#ifdef dHAS_TEMPLATE_FUNCTION_DEFAULT_PARAM
TEST_COMPONENT(002)
{
    ASSERT_TRUE( case_2( 1 ));
    ASSERT_TRUE(!case_2('a'));
}
#endif

//==============================================================================
//==============================================================================

#endif // !TEST_TOOLS_IF_
