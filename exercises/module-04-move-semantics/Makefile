CXX := clang++
CXXFLAGS := -std=c++20 -Wall -Wextra -Wpedantic -O0 -g
SANFLAGS := -fsanitize=address,undefined -fno-omit-frame-pointer

.PHONY: run run-sanitized run-no-elide clean
run: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o exercise
	./exercise
run-sanitized: main.cpp
	$(CXX) $(CXXFLAGS) $(SANFLAGS) main.cpp -o exercise-sanitized
	./exercise-sanitized
run-no-elide: main.cpp
	$(CXX) $(CXXFLAGS) -fno-elide-constructors main.cpp -o exercise-no-elide
	./exercise-no-elide
clean:
	rm -f exercise exercise-sanitized exercise-no-elide
