CXX := clang++
CXXFLAGS := -std=c++20 -Wall -Wextra -Wpedantic -g

SRC ?= main.cpp
BIN := scratch

.PHONY: run clean

run: $(SRC)
	$(CXX) $(CXXFLAGS) -o $(BIN) $(SRC) && ./$(BIN)

clean:
	rm -f $(BIN)
