TARGET = xdemo
CC = g++

IDIR = ../include
IDIR += ../../lib/libxlib.so
ODIR=obj

CPPSRC = xdemo.cpp diag2.cpp
DEPS = diag2.h

# Optimization level
OPT = 0
# Debugging format
DEBUG =
# Compiler flag to set the C Standard level.
CPPSTANDARD = -std=c++11

CPPFLAGS = $(CPPSTANDARD)
CPPFLAGS += -g$(DEBUG)
CPPFLAGS += -O$(OPT)
CPPFLAGS += -Wall

# defining obj files
OBJ := $(CPPSRC:.cpp=.o)

# creating obj files
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CPPFLAGS)
	

all: $(OBJ)
	$(CC) $(CPPFLAGS) $(OBJ) -I$(IDIR) -o $(TARGET) $(DEPS)

clean:
	rm -f $(TARGET)
	rm -f $(OBJ)

debug:
	@echo $(OBJ)

.PHONY: clean debug all
	