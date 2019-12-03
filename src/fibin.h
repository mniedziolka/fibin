#include <type_traits>

#ifndef __FIBIN_H__
#define __FIBIN_H__

// Empty list.
struct Nil;

// Head <Var, Value> + Tail.
template <unsigned Var, typename Value, typename Tail>
struct Cons;

template <typename List, unsigned Var>
struct FindInList {};

// Find in empty list.
template <unsigned Var>
struct FindInList<Nil, Var> {};

// Searched element is in the current head.
template <unsigned CurrVar, typename CurrValue, typename Tail>
struct FindInList<Cons<CurrVar, CurrValue, Tail>, CurrVar> {
    using value = CurrValue;
};

// Searched element is not in the current head but can be in tail.
template <unsigned CurrVar, typename CurrValue, typename Tail, unsigned SearchedVar>
struct FindInList<Cons<CurrVar, CurrValue, Tail>, SearchedVar> {
    using value = typename FindInList<Tail, SearchedVar>::value;
};

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


#endif // __FIBIN_H__
