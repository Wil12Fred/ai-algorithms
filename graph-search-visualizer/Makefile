CXX      ?= g++
CXXFLAGS ?= -std=c++11 -O2 -Wno-deprecated-declarations
TARGET   := main
SRC      := busqueda.cc

ifeq ($(shell uname -s),Darwin)
  LDLIBS := -framework OpenGL -framework GLUT
else
  LDLIBS := -lglut -lGLU -lGL
endif

all: $(TARGET)

$(TARGET): $(SRC) $(wildcard *.h)
	$(CXX) $(CXXFLAGS) -o $@ $(SRC) $(LDLIBS)

TESTS    := $(patsubst tests/%.cc,build/%,$(wildcard tests/test_*.cc))

build/%: tests/%.cc $(wildcard *.h)
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDLIBS)

test: $(TESTS)
	@set -e; for t in $(TESTS); do ./$$t; done

# Headless run on a private Xvfb display (never the real desktop).
smoke: $(TARGET)
	sh tests/smoke.sh

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(TARGET) build

.PHONY: all test smoke run clean
