#!/usr/bin/env bash
set -euo pipefail

# Usage: ./setup.sh [directory]  (defaults to current dir)

DIR="${1:-.}"

mkdir -p "$DIR"/{playground,exercises,debugging}

# compile_flags.txt for clangd / editor LSP
cat > "$DIR/compile_flags.txt" <<'EOF'
-xc++
-std=c++20
-Wall
-Wextra
-Wpedantic
EOF

# Makefile: playground
cat > "$DIR/playground/Makefile" <<'EOF'
CXX := clang++
CXXFLAGS := -std=c++20 -Wall -Wextra -Wpedantic -g

SRC ?= main.cpp
BIN := scratch

.PHONY: run clean

run: $(SRC)
	$(CXX) $(CXXFLAGS) -o $(BIN) $(SRC) && ./$(BIN)

clean:
	rm -f $(BIN)
EOF

# Makefile: exercises
cat > "$DIR/exercises/Makefile" <<'EOF'
CXX := clang++
CXXFLAGS := -std=c++20 -Wall -Wextra -Wpedantic -g
SANFLAGS := -fsanitize=address,undefined -fno-omit-frame-pointer

SRC ?= main.cpp
BIN := exercise

.PHONY: run run-sanitized clean

run: $(SRC)
	$(CXX) $(CXXFLAGS) -o $(BIN) $(SRC) && ./$(BIN)

run-sanitized: $(SRC)
	$(CXX) $(CXXFLAGS) $(SANFLAGS) -o $(BIN) $(SRC) && ./$(BIN)

clean:
	rm -f $(BIN)
EOF

# Makefile: debugging
cat > "$DIR/debugging/Makefile" <<'EOF'
CXX := clang++
CXXFLAGS := -std=c++20 -Wall -Wextra -Wpedantic -O0 -g
SANFLAGS := -fsanitize=address,undefined -fno-omit-frame-pointer

SRC ?= main.cpp
BIN := buggy

.PHONY: run run-sanitized clean

run: $(SRC)
	$(CXX) $(CXXFLAGS) -o $(BIN) $(SRC) && ./$(BIN)

run-sanitized: $(SRC)
	$(CXX) $(CXXFLAGS) $(SANFLAGS) -o $(BIN) $(SRC) && ./$(BIN)

clean:
	rm -f $(BIN)
EOF

# Stub main.cpp in each folder
for folder in playground exercises debugging; do
  cat > "$DIR/$folder/main.cpp" <<'EOF'
#include <iostream>

int main() {
    std::cout << "Hello, C++\n";
    return 0;
}
EOF
done

echo "Environment ready at $DIR"