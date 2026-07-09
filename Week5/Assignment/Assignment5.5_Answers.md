# Pointer Detective
Welcome to the agency detective. We ran into a couple of tough cases, and we need your help. As the best pointer detective in town, we thought of you first. 

## Introduction

A mysterious bug has appeared in several C++ programs. Your job as a **Pointer Detective** is to investigate each program and determine what is happening behind the scenes.

For **each mystery**, complete the following tasks **before running the program**:

1. Predict the program's output.
2. Explain **why** the output occurs.
3. Draw the call stack while the function executes.
4. Identify whether the function uses:
   - Pass by Copy
   - Pass by Reference
   - Pass by Pointer

After completing your predictions, compile and run the program to verify your answers.

---

# Mystery #1 – The Copycat

### Questions

1. What is the output of this program?
    
    It will print out "Inside addFive(): 15" from the addFive() function, then it will print out, "In main(): 10" from the main function.

2. Why doesn't `value` change after calling `addFive()`?
    
    Because value it's being _passed by copy_, so the function is modifying a copy of the variable, not its real value.

3. Where does the variable `number` exist?
    
    The variable `number` exists inside the addFive() function.

4. Draw the call stack while `addFive()` is executing.

    Top of stack
    +---------------+
    |   addFive()   |
    +---------------+
    |  number = 15  |
    +---------------+
    |     main()    |
    +---------------+
    |   value = 10  |
    +---------------+
    Bottom of stack

5. What happens to `number` after the function returns?

    It is removed from the stack alongside the function.

---

# Mystery #2 – The Mirror

### Questions

1. What is the output of this program?

    The program will output, "Inside investigate(): 15 5" from the investigate() function, then it will print 
    
    "15 5" from main() function.

2. Why does `score` change while `bonus` does not?
    
    Because score is _called by reference_ through suspect, a variable that exist in the function. Meanwhile, 
    
    although bonus is called by clue, the function never modifies its value, only reads it as parameter.

3. Why is `clue` declared as a `const` reference?
    
    So that the original value of the variable bonus is not modified by the function.

4. What would happen if the function attempted to modify `clue`?
    
    If the function attempted to modify `clue`, the program would not compile.

5. Draw the call stack while `investigate()` is executing.
    
    Top of Stack
    +-----------------------------+
    |       investigate()         |
    +-----------------------------+
    |    suspect = 10 + 5 = 15    |
    +-----------------------------+
    |           main()            |
    +-----------------------------+
    |         score = 10          |
    |         bonus = 5           |
    +-----------------------------+
    Bottom of Stack

---

# Mystery #3 – Following the Pointer

### Questions

1. What is the output of this program?
    
    The program will output 14 from the main() function.

2. Why do we pass `&clue` instead of `clue`?
    
    Because we want to pass the memory address location of `clue` to the function, not just the value,
    
    because the function is not expecting an integer, but a pointer to an integer.

3. What does `*evidence` do?
    
    It tells the function to go to the integer that `*evidence` is pointin at, so that its original value can be
    
    modified.

4. Why is the `nullptr` check important?
    
    The nullptr check is important because dereferencing a null pointer would be unsafe and 
    
    could crash the program.

5. What would happen if the function was called as `investigate(nullptr);`?
    
    If this was to happen, then the if condition would be true and the function would exit.

6. Draw the call stack while `investigate()` is executing.
    
    Top of Stack
    +-----------------------------+
    |       investigate()         |
    +-----------------------------+
    |       *evidence = 14        |
    +-----------------------------+
    |          main()             |
    +-----------------------------+
    |         clue = 7            |
    +-----------------------------+
    Bottom of Stack

---

# Mystery #4 – The Master Case

### Questions

1. Predict the output of the program.
    
    It will print out 29 in the `main()` function.

2. Draw the call stack after each function call.
    
    Top of Stack
    +--------------------+
    |       main()       |
    +--------------------+
    |     value = 29     |
    +--------------------+
    Bottom of Stack

3. Which function uses:
   - Pass by Copy? `int mysteryA()`
   - Pass by Reference? `void misteryB()`
   - Pass by Pointer? `void misteryC()`

4. Which functions modify the original variable?
    
    `misterybB()` and `misteryC()`

5. Why does `mysteryA()` return a value, while `mysteryB()` and `mysteryC()` do not?
    
    Because `misteryA()` is an integer function, so it returns a value, whereas `mysteryB()` and `misteryC()` are
    
    void functions, which don't need to return.

6. Which approach would you choose if your goal was to modify the original variable? Explain your reasoning.
    
    I would use the function `misteryB()` to modify the original variable, since it allows to modify the original
    
    value, but its syntax is easier to understand than pointers, since it doesn't rely on if-statements to 
    
    check if a null value is present.

---

# Reflection

Answer the following questions in complete sentences.

1. What is the difference between passing a variable by copy, by reference, and by pointer?
    
    Passing a variable by copy, as its name implies, passes a copy of the original variable's value, not the
    
    original. Pass by reference passes the original variable, allowing you to modify its direct value. Finally,
    
    pass by pointer points to the address of the variable in order to directly modify its value.

2. When would you choose to use a reference instead of a pointer?
    
    A reference would be used over a pointer when you want to change the name of an existing variable, or to 
    
    directly accessing variable's value with a cleaner syntax than that of pointers.

3. Why might a function accept a pointer instead of a reference?
    
    A function might accpet a pointer instead of a reference if the function needs to work with memory address,
    
    or if it needs to check for a nullptr.

4. What role does the `const` keyword play when working with references and pointers?
    
    `const` ensures that the original value of the variable doesn't get accidentally modified by the function once
    
    the variable is called by its parameters.

5. How does understanding the call stack help explain why variables change—or do not change—during function calls?
    
    The call stack shows a visualization of whether a function has its own copy of a variable or if it is 
    
    accessing the original through references or pointers, explaining why changes remains while others may not.

