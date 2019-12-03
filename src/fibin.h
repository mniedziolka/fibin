//
// Created by chedat on 03.12.2019.
//

#include <type_traits>

#ifndef _FIBIN_H
#define _FIBIN_H


template <typename Condition, typename Then, typename Else> class If;
//true branch
template <typename Then, typename Else> class If <std::true_type, Then, Else>{
    typedef double result;
};

//false branch
template <typename Then, typename Else> class If <std::false_type, Then, Else>{
    typedef int result;
};




template <typename ValueType> class Fibin {

    template <typename Expr>
    static typename std::enable_if<std::is_integral<ValueType>::value, ValueType>::type eval(){

    }
    template <typename Expr>
    static typename std::enable_if<!std::is_integral<ValueType>::value, void>::type eval(){

    }
};


#endif _FIBIN_H
