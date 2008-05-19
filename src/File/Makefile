# Makefile for the File namespace

### config

CXX = g++
#CXXFLAGS = 
#DEF = -DECHO
SRC = InputBase.cpp

### end config


# preparation

OBJ = $(SRC:.cpp=.o)
CMD = $(CXX) $(DEF)

# targets

all: $(OBJ)
	@echo "successfully compiled namespace: File"

%.o: %.cpp
	$(CMD) -c $<


clean:
	rm -rf $(OBJ)
