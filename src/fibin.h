#ifndef __FIBIN_H__
#define __FIBIN_H__

#include <type_traits>
#include <cassert>
#include <iostream>

struct True;
struct False;

template <typename T>
struct Lit {};

template <uint64_t T>
struct Ref {};

template <uint64_t Var, typename Value, typename Expr>
struct Let {};

template <typename Left, typename Right>
struct Eq {};

template <typename T>
struct Inc1 {};

template <typename T>
struct Inc10 {};

template <typename ... Args>
struct Sum {};

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

// Substitution failure is not an error
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
    // We will store type for every integer in the environment .
    template <ValueType N>
    struct IntValue {
        static constexpr ValueType value = N;
    };

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
        using value = IntValue<Eval<Lit<Fib<N-1>>, Env>::value::value + Eval<Lit<Fib<N-2>>, Env>::value::value>;
    };

    template <typename Env>
    struct Eval <Lit<Fib<0>>, Env> {
        using value = IntValue<0>;
    };

    template <typename Env>
    struct Eval <Lit<Fib<1>>, Env> {
        using value = IntValue<1>;
    };

    // Get Var value from Env.
    template <unsigned Var, typename Env>
    struct Eval <Ref<Var>, Env> {
        using value = typename FindInList<Env, Var>::value;
    };

    // Define new variable and evaluate expression with new environment.
    template <uint64_t Var, typename Value, typename Expr, typename Env>
    struct Eval <Let<Var, Value, Expr>, Env> {
        using value = typename Eval<Expr, Cons<Var, typename Eval<Value, Env>::value, Env>>::value;

    };

    template <typename Left, typename Right>
    struct EqHelper {};

    // Evaluated values are different.
    template <ValueType A, ValueType B>
    struct EqHelper <IntValue<A>, IntValue<B>> {
        using value = typename Eval<Lit<False>, Nil>::value;
    };

    // Evaluated values are the same.
    template <ValueType N>
    struct EqHelper <IntValue<N>, IntValue<N>> {
        using value = typename Eval<Lit<True>, Nil>::value;
    };

    template <typename Left, typename Right, typename Env>
    struct Eval <Eq<Left, Right>, Env> {
        using value = typename EqHelper<Eval<Left, Env>, Eval<Right, Env>>::value;
    };

    // If True.
    template <typename Then, typename Else, typename Env>
    struct Eval <If<True, Then, Else>, Env> {
        using value = typename Eval<Then, Env>::value;
    };

    // If False.
    template <typename Then, typename Else, typename Env>
    struct Eval <If<False, Then, Else>, Env> {
        using value = typename Eval<Else, Env>::value;
    };

    // Evaluate the condition.
    template <typename Condition, typename Then, typename Else, typename Env>
    struct Eval <If<Condition, Then, Else>, Env> {
        using value = typename Eval<If<
                typename Eval<Condition, Env>::value, Then, Else>,
                Env>::value;
    };

    template <typename A, typename B>
    struct IncHelper {};

    template <ValueType A, ValueType B>
    struct IncHelper <IntValue<A>, IntValue<B>> {
        using value = IntValue<A + B>;
    };

    template <typename Arg, typename Env>
    struct Eval <Inc1<Arg>, Env> {
        using value = typename IncHelper<
                typename Eval<Arg, Env>::value,
                typename Eval<Lit<Fib<1>>, Nil>::value
            >::value;
    };

    template <typename Arg, typename Env>
    struct Eval <Inc10<Arg>, Env> {
        using value = typename IncHelper<
                typename Eval<Arg, Env>::value,
                typename Eval<Lit<Fib<10>>, Nil>::value
        >::value;
    };

    template <typename Arg1, typename Arg2, typename ... Args, typename Env>
    struct Eval <Sum<Arg1, Arg2, Args...>, Env> {
        using value = typename IncHelper<
                typename Eval<Arg1, Env>::value,
                typename Eval<Sum<Arg2, Args...>, Env>::value
            >::value;
    };

    template <typename Arg1, typename Arg2, typename Env>
    struct Eval <Sum<Arg1, Arg2>, Env> {
        using value = typename IncHelper<
                typename Eval<Arg1, Env>::value,
                typename Eval<Arg2, Env>::value
        >::value;
    };

public:
    template <typename Expr>
    constexpr static ValueType eval(){
        return Eval<Expr, Nil>::value::value;
    }
};

#endif // __FIBIN_H__
