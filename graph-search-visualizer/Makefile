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

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
