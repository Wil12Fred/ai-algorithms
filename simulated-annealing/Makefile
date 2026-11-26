CXX      ?= g++
CXXFLAGS ?= -std=c++11 -O2
TARGET   := main

all: $(TARGET)

$(TARGET): main.cc $(wildcard *.h)
	$(CXX) $(CXXFLAGS) -o $@ main.cc

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
