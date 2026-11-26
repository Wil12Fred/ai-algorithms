CXX      ?= g++
CXXFLAGS ?= -std=c++11 -O2
TARGET   := main

all: $(TARGET)

$(TARGET): main.cc $(wildcard *.h)
	$(CXX) $(CXXFLAGS) -o $@ main.cc

TESTS    := $(patsubst tests/%.cc,build/%,$(wildcard tests/test_*.cc))

build/%: tests/%.cc $(wildcard *.h)
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -o $@ $<

test: $(TESTS) $(TARGET)
	@set -e; for t in $(TESTS); do ./$$t; done
	sh tests/run_check.sh

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(TARGET) build

.PHONY: all test run clean
