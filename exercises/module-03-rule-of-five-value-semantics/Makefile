CXX := clang++
CXXFLAGS := -std=c++20 -Wall -Wextra -Wpedantic -O0 -g
SANFLAGS := -fsanitize=address,undefined -fno-omit-frame-pointer

SRC ?= main.cpp
BIN := dynamic-array

.PHONY: run run-sanitized clean

run: $(SRC)
	$(CXX) $(CXXFLAGS) -o $(BIN) $(SRC) && ./$(BIN)

run-sanitized: $(SRC)
	$(CXX) $(CXXFLAGS) $(SANFLAGS) -o $(BIN) $(SRC) && ./$(BIN)

clean:
	rm -f $(BIN)
