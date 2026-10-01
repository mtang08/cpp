CXX := clang++
CXXFLAGS := -std=c++20 -Wall -Wextra -Wpedantic -O0 -g
SANFLAGS := -fsanitize=address,undefined -fno-omit-frame-pointer
.PHONY: run run-sanitized
run: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o buggy
	./buggy
run-sanitized: main.cpp
	$(CXX) $(CXXFLAGS) $(SANFLAGS) main.cpp -o buggy
	./buggy
