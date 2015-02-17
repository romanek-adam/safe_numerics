//  Copyright (c) 2012 Robert Ramey
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#if 1

#include "safe_integer.hpp"

const intmax_t x = std::numeric_limits<
    boost::numeric::safe<
        signed char,
        boost::numeric::policies<
            boost::numeric::native,
            boost::numeric::relaxed, boost::numeric::throw_exception
        >
    >
>::min();

#endif

#if 0
#include <boost/mpl/print.hpp>

template<
    class T,
    class P
>
struct safe;

std::numeric_limits<int> ai0;

namespace std {

numeric_limits<int> ai2;

template<class T>
struct numeric_limits {
    // no message here with numeric_limits<int> because it's already
    // specialized in <limits>
    typedef typename boost::mpl::print<T>::type t0;
};

template<class T, class P>
struct std::numeric_limits <safe<T, P> > : public numeric_limits<T>{
    typedef typename boost::mpl::print<T>::type t0;
    typedef typename boost::mpl::print<P>::type t1;
};

numeric_limits<int> ai3;

} // std
#endif

#if 0

#include <limits>
#include <boost/mpl/print.hpp>

namespace std {
template<class T> class numeric_limits;
} // std

template<class T>
class std::numeric_limits {
    typedef typename boost::mpl::print<T>::type t0;
};

std::numeric_limits<int> ai;

#endif

#if 0

#include <limits>
#include <boost/mpl/print.hpp>

namespace std {

template<class T>
class numeric_limits {
    typedef typename boost::mpl::print<T>::type t0;
};

} // std

std::numeric_limits<int> ai;


#endif

#if 0
#include <exception>
#include <cstdlib>   // EXIT_SUCCESS
#include <iostream>

#include <boost/mpl/print.hpp>

#endif

#if 0
typedef boost::numeric::safe_signed_range<-64, 63> X;
//typedef boost::mpl::print<boost::numeric::get_policy<int, X>::type>::type t8 ;
//typedef boost::mpl::print<boost::numeric::get_policy<X, X>::type>::type t9 ;
//typedef boost::mpl::print<boost::numeric::get_policy<X, int>::type >::type t7 ;
//typedef boost::mpl::print<boost::numeric::is_safe<int>::type>::type t10;

typedef boost::mpl::print<boost::numeric::addition_result<int,X>::type>  t13;
#endif

#if 0
typedef boost::numeric::safe_signed_range<-64, 63> X;
typedef boost::mpl::print<boost::numeric::get_policy<short,X>::type>::type t12;
typedef boost::mpl::print<boost::numeric::addition_result<short,X>::type
> t11;

#endif

#if 0

bool test1(){
    std::cout << "test1" << std::endl;
    boost::numeric::safe_signed_range<-64, 63> x, y, z;
    x = 1;
    y = 2;
    z = 3;
    z = x + y;
    z = x - y;
    typedef boost::mpl::print<
        boost::numeric::addition_result_bits<
            boost::numeric::safe_signed_range<-64, 63>,
            int
        >::type
    >::type t1;
    typedef boost::mpl::print<
        boost::numeric::bits<
            boost::numeric::safe_signed_range<-64, 63>
        >::type
    >::type t2;
    typedef boost::mpl::print<
        boost::numeric::bits<
            int
        >::type
    >::type t3;

    try{
        short int yi, zi;
        yi = y;
        zi = x + yi;
    }
    catch(std::exception e){
        // none of the above should trap. Mark failure if they do
        std::cout << e.what() << std::endl;
        return false;
    }
    return true;
}

bool test2(){
    std::cout << "test2" << std::endl;
    boost::numeric::safe_unsigned_range<0, 64> x, y, z;
    x = 1;
    y = 2;
    z = 3;

    bool success = false;
    try{
        z = x - y; // should trap here
    }
    catch(std::exception e){
        success = true;
    }
    if(success == false)
        return false;
    
    try{
        int yi = y;
        z = x + yi; // should trap here
    }
    catch(std::exception e){
        // none of the above should trap. Mark failure if they do
        std::cout << e.what() << std::endl;
        return false;
    }
    return true;
}

bool test3(){
    std::cout << "test3" << std::endl;
    boost::numeric::safe<int> x, y, z;
    x = 1;
    y = 2;
    z = 3;
    try{
        z = x + y;
        z = x - y;
        int yi, zi;
        zi = x + yi;
        z = x + yi;
    }
    catch(std::exception e){
        // none of the above should trap. Mark failure if they do
        std::cout << e.what() << std::endl;
        return false;
    }
    return true;
}

bool test4(){
    std::cout << "test4" << std::endl;
    boost::numeric::safe<unsigned int> x, y, z;
    x = 1;
    y = 2;
    z = 3;
    z = x + y;
    bool success = false;
    try{
        z = x - y; // should trap here
    }
    catch(std::exception e){
        success = true;
    }
    if(success == false)
        return false;
    unsigned int yi, zi;
    zi = x;
    zi = x + yi;
    z = x + yi;
    zi = x + y;
    return true;
}

#include <boost/cstdint.hpp>

bool test5(){
    std::cout << "test5" << std::endl;
    boost::numeric::safe<boost::uint64_t> x, y, z;
    x = 1;
    y = 2;
    z = 3;
    z = x + y;
    bool success = false;
    try{
        z = x - y; // should trap here
    }
    catch(std::exception e){
        success = true;
    }
    if(success == false)
        return false;
    boost::uint64_t yi, zi;
    zi = x;
    zi = x + yi;
    z = x + yi;
    zi = x + y;
    return true;
}

int main(int argc, char *argv[]){
    return (
        test1() &&
        test2() &&
        test3() &&
        test4() &&
        test5()
    ) ? EXIT_SUCCESS : EXIT_FAILURE;
}

#endif
