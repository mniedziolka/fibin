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
template <uint64_t Var, typename Value, typename Tail>
struct Cons;

template <typename List, uint64_t Var>
struct FindInList {};

// Find in empty list.
template <uint64_t Var>
struct FindInList<Nil, Var> {};

// Searched element is in the current head.
template <uint64_t CurrVar, typename CurrValue, typename Tail>
struct FindInList <Cons<CurrVar, CurrValue, Tail>, CurrVar> {
    using value = CurrValue;
};

// Searched element is not in the current head but can be in tail.
template <uint64_t CurrVar, typename CurrValue, typename Tail, uint64_t SearchedVar>
struct FindInList <Cons<CurrVar, CurrValue, Tail>, SearchedVar> {
    using value = typename FindInList<Tail, SearchedVar>::value;
};

template <int N>
struct Fib {
    static_assert(N >= 0, "N in Fib<N> should be non-negative");
};

static constexpr uint64_t Var(const char* x) {
    return 1;
}

// We use "substitution failure is not an error".
template <typename ValueType, typename = void>
class Fibin {
public:
    template <typename Expr>
    static void eval(){
        std::cout << "Fibin doesn't support: " << typeid(ValueType).name() << "\n";;
    }
};

template <typename ValueType>
class Fibin <ValueType, typename std::enable_if<std::is_integral<ValueType>::value>::type> {
private:
    // We will store in the environmnent type for every integer.
    template <ValueType N>
    struct IntValue {};

    template <typename Exp, typename Env>
    struct Eval {};

    // Apply value of the arguments to function.
    template <typename Proc, typename Value>
    struct Apply {};

    template <typename Env>
    struct Eval <Lit<True>, Env> {
        using value = True;
    };

    template <typename Env>
    struct Eval <Lit<False>, Env> {
        using value = False;
    };

    template <int N, typename Env>
    struct Eval <Lit<Fib<N>>, Env> {
        static constexpr IntValue value = Eval<Lit<Fib<N - 1>>, Env>::value
                                          + Eval<Lit<Fib<N - 2>>, Env>::value;
    };

    template <typename Env>
    struct Eval <Lit<Fib<0>>, Env> {
        static constexpr IntValue value = 0;
    };

    template <typename Env>
    struct Eval <Lit<Fib<1>>, Env> {
        static constexpr IntValue value = 1;
    };

    // Get Var value from Env.
    template <unsigned Var, typename Env>
    struct Eval <Ref<Var>, Env> {
        using result =  typename FindInList<Env, Var>::value;
    };

    // If True.
    template <typename Then, typename Else, typename Env>
    struct Eval<If<True, Then, Else>, Env> {
        using result = typename Eval<Then, Env>::result;
    };

    // If False.
    template <typename Then, typename Else, typename Env>
    struct Eval<If<False, Then, Else>, Env> {
        using result = typename Eval<Else, Env>::result;
    };

    // Evaluate the condition.
    template <typename Condition, typename Then, typename Else, typename Env>
    struct Eval <If<Condition, Then, Else>, Env> {
        using result = typename Eval<If<
                typename Eval<Condition, Env>::result, Then, Else>,
                Env>::result;
    };



public:
    template <typename Expr>
    static ValueType eval(){
        return 1;
    }
};

#endif // __FIBIN_H__
