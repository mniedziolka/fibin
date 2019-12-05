#ifndef __FIBIN_H__
#define __FIBIN_H__

#include <type_traits>
#include <iostream>

struct True;
struct False;

template <typename T>
struct Lit {};

template <unsigned T>
struct Ref {};

template <typename Condition, typename Then, typename Else>
struct If {};


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
struct FindInList <Cons<CurrVar, CurrValue, Tail>, CurrVar> {
    using value = CurrValue;
};

// Searched element is not in the current head but can be in tail.
template <unsigned CurrVar, typename CurrValue, typename Tail, unsigned SearchedVar>
struct FindInList <Cons<CurrVar, CurrValue, Tail>, SearchedVar> {
    using value = typename FindInList<Tail, SearchedVar>::value;
};

template <int N>
struct Fib {
    static_assert(N >= 0, "N in Fib<N> should be non-negative");
};

//template <>
//struct Lit<True> {};
//
//template <>
//struct Lit<False> {};

//template <int N>
//struct Lit<Fib<N>> {
//static constexpr unsigned long long value = Lit<Fib<N - 1>>::value + Lit<Fib<N - 2>>::value;
//};
//
//template <>
//struct Lit<Fib<0>> {
//static constexpr unsigned long long value = 0;
//};
//
//template <>
//struct Lit<Fib<1>> {
//static constexpr unsigned long long value = 1;
//};

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
private:
    template <typename Exp, typename Env>
    struct Eval {};

    template <typename Proc, typename Value>
    struct Apply {};

    template <typename Env>
    struct Eval <Lit<ValueType>, Env> {
        ValueType typedef result;
    };

    // Get Var value from Env.
    template <unsigned Var, typename Env>
    struct Eval <Ref<Var>, Env> {
        typename FindInList<Env, Var>::value typedef result;
    };



public:
    template <typename Expr>
    static ValueType eval(){
        return 1;
    }
};

#endif // __FIBIN_H__
