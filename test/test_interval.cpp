#include <cassert>
#include <iostream>
#include <ostream>
#include <cstdint>
#include <cxxabi.h>

#include "../include/interval.hpp"
#include <boost/logic/tribool_io.hpp>

bool test1(){
    using namespace boost::numeric;
    std::cout << "test1" << std::endl;
    interval<std::int16_t> x = {-64, 63};
    std::cout << "x = " << x;
    interval<std::int16_t> y(-128, 126);
    std::cout << "y = " << y;
    assert(operator+<std::int16_t>(x,x) == y);
    std::cout << "x + x =" << operator+<std::int16_t>(x, x);
    std::cout << "x - x = " << operator-<std::int16_t>(x, x);
    return true;
}

bool test2(){
    using namespace boost::numeric;
    std::cout << "test2" << std::endl;
    boost::numeric::interval<std::int16_t> x = {-64, 63};
    std::cout << "x = " << x;
    std::cout << std::boolalpha << "(x == x) = " << (x == x) << std::endl;
    return true;
}

bool test3(){
    using namespace boost::numeric;
    std::cout << "test3" << std::endl;
    interval<std::int8_t> t;
    std::cout << "t = " << t;
    interval<std::uint64_t> u;
    std::cout << "u = " << u;
    using max_t = unsigned long long;
    interval< max_t> r = operator+<max_t>(t, u);
    std::cout << "r = " << r << std::endl;
    return true;
}

#include <limits>

namespace test4 {
    using namespace boost::numeric;
    using max_t = std::intmax_t;
    // typedef typename print<max_t>::type p_max_t;

    template<typename Tx>
    SAFE_NUMERIC_CONSTEXPR static const interval<Tx> r_upper(const interval<Tx> & t){
        static_assert(
            std::is_literal_type< interval<Tx> >::value,
            "interval<Tx> is not literal type"
        );
        return interval<Tx>(
            max(checked_result<Tx>(1), t.l),
            t.u
        );
    }
    template<typename Tx>
    SAFE_NUMERIC_CONSTEXPR static const interval<Tx> r_lower(const interval<Tx> & t){
        static_assert(
            std::is_literal_type< interval<Tx> >::value,
            "interval<Tx> is not literal type"
        );
        return interval<Tx>(
            t.l,
            min(checked_result<Tx>(-1), t.u)
        );
    }

    template<typename Tx, typename Ux>
    SAFE_NUMERIC_CONSTEXPR static const interval<max_t> r(
        const interval<Tx> & t,
        const interval<Ux> & u
    ){
        if(std::numeric_limits<Ux>::is_signed){
            if(u.l > 0 || u.u < 0){
                auto retval = operator/<max_t>(t, u);
                // typedef print<decltype(retval)> p_retval;
                return retval;
                //return operator/<max_t>(t, u);
            }
            else{
                auto lower = operator/<max_t>(t,r_lower(u));
                // typedef print<decltype(lower)> p_lower;
                auto upper = operator/<max_t>(t,r_upper(u));
                // typedef print<decltype(upper)> p_lower;
                return
                    interval< max_t>(
                        min(lower.l, upper.l),
                        max(lower.u, upper.u)
                    );
                /*
                */
                // return t;
            }
        }
        else{ // u is unsigned
            if(u.l > 0)
                return operator/<max_t>(t, u);
            else
                return operator/<max_t>(t, r_upper(u)) ;
        };
    };

    bool test1(){
        using namespace boost::numeric;
        int status;
        std::cout << "test4::test1" << std::endl;
        const interval<std::int8_t> t;
        std::cout
            << abi::__cxa_demangle(typeid(t).name(),0,0,&status)
            << " t = "
            << t;
        const interval<std::int8_t> u;
        std::cout
            << abi::__cxa_demangle(typeid(u).name(),0,0,&status)
            << " u = "
            << u;
        const interval<max_t> rx = r(t, u);
        std::cout
            << abi::__cxa_demangle(typeid(rx).name(),0,0,&status)
            << " rx = "
            << rx;
        return true;
    }
    bool test2(){
        using namespace boost::numeric;
        int status;
        std::cout << "test4::test2" << std::endl;
        const interval<std::int8_t> t;
        std::cout
            << abi::__cxa_demangle(typeid(t).name(),0,0,&status)
            << " t = "
            << t;
        const interval<std::int64_t> u;
        std::cout
            << abi::__cxa_demangle(typeid(u).name(),0,0,&status)
            << " u = "
            << u;
        const interval<max_t> rx = r(t, u);
        std::cout
            << abi::__cxa_demangle(typeid(rx).name(),0,0,&status)
            << " rx = "
            << rx;
        return true;
    }
    bool test3(){
        using namespace boost::numeric;
        int status;
        std::cout << "test4::test2" << std::endl;
        const interval<std::int8_t> t;
        std::cout
            << abi::__cxa_demangle(typeid(t).name(),0,0,&status)
            << " t = "
            << t;
        const interval<std::uint64_t> u;
        std::cout
            << abi::__cxa_demangle(typeid(u).name(),0,0,&status)
            << " u = "
            << u;
        const interval<max_t> rx = r(t, u);
        std::cout
            << abi::__cxa_demangle(typeid(rx).name(),0,0,&status)
            << " rx = "
            << rx;
        return true;
    }
};

int main(){
    return (
        test1() &&
        test2() &&
        test3() &&
        test4::test1() &&
        test4::test2() &&
        test4::test3()
    ) ? EXIT_SUCCESS : EXIT_FAILURE;
}