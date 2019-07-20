# cpp-decorators


Anyone who's had a fair share doing OOP programming is probably familiar with a somewhat tricky - sometimes very effective pattern called **Decorator**.

However, This pattern is not solely used in traditional OOP - and one can see abilities in languages like Python that allow one to wrap functions with decorations.

Unfortunately (or maybe not), C++ doesn't give out-of-the-box support for functions to be decorated.

So suppose one will get some variable/callback containing a function - one has no way to decorate it's functionality in an easy manner.

This library proposes a solution - one that is **Simple** (~ 70 lines) and **Easy to use** (one header file).

# Usage Example

```c
auto callback = &callback_function;

// decltype(decorator_func) should be as decltype(callback)
const auto decorator = make_decorator(&callback, &decorator_func);

// this will also call decorator_func
callback();
```

For more please see the tests folder :)

### Todos

 - Support different calling conventions - like stdcall
 
License
----

MIT :)
