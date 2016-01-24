all:
	clang++ \
	-std=c++14 \
	-Wall \
	main.cpp \
	compiler/lexer.cpp \
	-Iheader/compiler/lexer/ \
	-Iheader/core \
	-O3 -o bin/cpp

rs:
	rustc -C opt-level=3 ~/CODE/bench/c_vs_rust/rust/main.rs -o ~/CODE/resembler/src/bin/rs
