# Stack Frames

A stack frame is a data structure used to store information about a specific function call and it is used by the processor during the execution of a program.

A stack frame for a given function typically contains the following information:
- **Return Address**, which is the address of the instruction to execute after the function returns.
- **Function Arguments**, which are the arguments passed to the function call via registers.
- **Local Variables**, which are the local variables defined within the function.

To manage the stacks, two registers are used: 
- **RSP** or Register Stack Pointer
- **RBP** or Register Base Pointer

# RSP (Register Stack Pointer)

- The RSP or Register Stack Pointer is used to keep track of the top of the stack, which is the area of memory that represents the boundary between the used stack and the space still available.
- In x86-64, the stack grows downwards towards lower addresses. Visually, we have the following situation:

``` 
0x7ffffff0e410 <-- lower address (unused)
...
0x7fffffffe410 <-- RSP (current top of stack)
...
0x7fffffffffff <-- higher address (bottom of stack)
```
- Any memory **below RSP** (lower addresses) is currently unused and available for future stack allocations.  
- To **reserve space** for local variables in a function, we use the `sub` instruction.
- For example, after `sub rsp, 0x20` (reserves 32 bytes of space). After this, RSP points **32 bytes lower**, creating space in the stack frame for locals or temporary data. Memory layout now looks like:
```
0x7ffffff0e410 <-- lower address (still unused)
...
0x7fffffffe3f0 <-- RSP (top of stack after allocation)
0x7fffffffe3f1 
0x7fffffffe3f2
0x7fffffffe3f3
0x7fffffffe3f4
0x7fffffffe3f5
0x7fffffffe3f6
0x7fffffffe3f7
0x7fffffffe3f8
0x7fffffffe3f9
0x7fffffffe3fa
0x7fffffffe3fb
0x7fffffffe3fc
0x7fffffffe3fd
0x7fffffffe3fe
0x7fffffffe3ff
0x7fffffffe400
0x7fffffffe401
0x7fffffffe402
0x7fffffffe403
0x7fffffffe404
0x7fffffffe405
0x7fffffffe406
0x7fffffffe407
0x7fffffffe408
0x7fffffffe409
0x7fffffffe40a
0x7fffffffe40b
0x7fffffffe40c
0x7fffffffe40d
0x7fffffffe40e
0x7fffffffe40f
0x7fffffffe410 <-- old RSP / previous top of stack
...
0x7fffffffffff <-- higher address (bottom of stack)
```