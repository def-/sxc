# Makefile for the File namespace

### config

CXX = "g++"
#DEF = -DECHO
SRC = Input.cpp Output.cpp

### end config


# preparation

OBJ = $(SRC:.cpp=.o)
CMD = ${CXX} $(DEFINES)

# targets

all: %.o

%.o: %.cpp
	$(CMD) -c $<


clean:
	rm -rf $(OBJ)
