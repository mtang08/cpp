CXX := clang++
CXXFLAGS := -std=c++20 -Wall -Wextra -Wpedantic -O0 -g
SANFLAGS := -fsanitize=address,undefined -fno-omit-frame-pointer

.PHONY: build build-sanitized run run-sanitized clean
build: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o challenge
build-sanitized: main.cpp
	$(CXX) $(CXXFLAGS) $(SANFLAGS) main.cpp -o challenge-sanitized
run: build
	@failed=0; for case_name in delivery archive inspection; do ./challenge $$case_name || failed=1; done; exit $$failed
run-sanitized: build-sanitized
	@failed=0; for case_name in delivery archive inspection; do ./challenge-sanitized $$case_name || failed=1; done; exit $$failed
clean:
	rm -f challenge challenge-sanitized
