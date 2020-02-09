# Fibin

This is primitive functional language written in C++.
Here's short list of what's in it:
* Literals Lit - the only literals allowed are Fibonnaci numbers and True/False.
```
Example: Lit<Fib<0>>, Lit<True>
```

* Variables Var
```
Example: Var("A"), Var("01234"), Var("Cdefg")
```

* Arithmetic operation Sum, Inc1, Inc10.
	- Sum<...> - sum many arguments (at least two).
	- Inc1<Arg> - increment Arg by Fib<1>.
	- Inc10<Arg> - increment Arg by Fib<10>.
```
Example: Sum<Lit<Fib<0>>, Lit<Fib<1>>, Lit<Fib<3>>>, Inc1<Lit<Fib<0>>>
```

* Comparison Eq<Left, Right> - compares Left with Right.
Returns True, when they're equal, if not returns False.
```
Example: Eq<Lit<Fib<0>>, Lit<Fib<1>>>
```

* Reference Ref<Var> - returns the value of Var.
```
Example: Ref<Var("A")>
```

* Let<Var, Value, Expression> - assigns Value to Var and calculate Expression.
```
Example: Let<Var("A"), Lit<Fib<1>>, Ref<Var("A")>>
```

* If<Condition, Then, Else> - if the Condition evaluates to True, calculate Then,
if not, calculate Else.
```
Example: If<Lit<True>, Lit<Fib<1>>, Lit<Fib<0>>>
```

* Lambda<Var, Body> - represents anonymous function with one Var parameter and the Body.
```
Example: Lambda<Var("x"), Ref<Var("x")>>
```

* Invoke<Function, Param> - calculates Function value for the given Param.
```
Example: Invoke<Lambda<Var("x"), Ref<Var("x")>>, Lit<Fib<0>>>
```