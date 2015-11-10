**Resembler** is both a *toolkit* and a *platform*.

As a *platform* it enables execution of programs written in different programming languages with overhead-free cross-language communications enabled (Ruby program can call a function defined in Scheme, Python, Perl, etc.).

As a *toolkit* it provides a Rust codebase with libraries full of functions and macros to define new *transformators*.

*Transformator* is a program which serves as a transcompiler to translate arbitrary (defined by a *transformator* grammar) inputs into *final form*.

*Final form* is, currently, a C code with custom runtime.