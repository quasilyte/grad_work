Transcompilation targets.

I am not sure if this project will ever have backends
other than C++, but for the sake of modularity and design
C++ related stuff is not highly coupled with lexer or parser.

For starters, C++ was chosen because it has far more features
than C, so I can generate less code to do the same tasks.
This is not the best choice, but I am not aware of any best choices
out there in the real world.

Some good backend alternatives:
- Java (or JVM bytecode) 
- Rust (possible can outperform my naive C++ runtime)
- C (to make foreign API more friendly)
- JavaScript
