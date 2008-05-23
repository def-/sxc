# Makefile for the Control::File namespace

### config

CXX = g++
#CXXFLAGS = 
#DEF = -DECHO
SRC = Input.cpp

### end config


# preparation

OBJ = $(SRC:.cpp=.o)
CMD = $(CXX) $(DEF)

# targets

all: $(OBJ)
	@echo "successfully compiled namespace: Control::File"

%.o: %.cpp
	$(CMD) -c $<


clean:
	rm -rf $(OBJ)

