CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

TEST_FILE = tests/test_value.cpp
TEST_BINARY = build/test_value

.PHONY: all test clean

all: test

$(TEST_BINARY): $(TEST_FILE) include/value.hpp
	mkdir -p build
	$(CXX) $(CXXFLAGS) $(TEST_FILE) -o $(TEST_BINARY)

test: $(TEST_BINARY)
	./$(TEST_BINARY)

clean:
	rm -rf build
