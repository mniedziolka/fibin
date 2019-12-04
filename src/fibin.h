#ifndef __FIBIN_H__
#define __FIBIN_H__

#include <type_traits>
#include <iostream>

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


template<unsigned long long n>
struct Fib {
    static constexpr unsigned long long value = Fib<n-1>::value + Fib<n-2>::value;
};

template<>
struct Fib<0> {
    static constexpr int value = 0;
};

template<>
struct Fib<1> {
    static constexpr int value = 1;
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

// We use "substitution failure is not an error".
template <typename ValueType, typename = void>
class Fibin {
public:
    template <typename Expr>
    static void eval(){
        std::cout << "Fibin doesn't support: " << std::string(typeid(ValueType)) << "\n";;
    }
};

template <typename ValueType>
class Fibin <ValueType, typename std::enable_if<std::is_integral<ValueType>::value>::type> {
public:
    template <typename Expr>
    static int eval(){
        return 1;
    }
};

#endif // __FIBIN_H__
