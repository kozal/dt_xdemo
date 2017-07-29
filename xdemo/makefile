TARGET = xdemo
CC = g++

IDIR = ../include
IDIR += ../../lib/libxlib.so
ODIR = obj

CPPSRC = xdemo.cpp diag2.cpp
_DEPS = diag2.h
DEPS = $(addprefix inc/,$(_DEPS))

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
OBJ2 = $(addprefix $(ODIR)/,$(CPPSRC:.cpp=.o))

# creating obj files
$(ODIR)/%.o: %.cpp $(DEPS)
#%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CPPFLAGS)
	

all: $(OBJ2)
#	$(CC) $(CPPFLAGS) $(OBJ) -I$(IDIR) -o $(TARGET) $(DEPS)
	$(CC) $(CPPFLAGS) $^ -I$(IDIR) -o $(TARGET)

clean:
	rm -f $(TARGET)
	rm -f $(OBJ)
	rm -f $(OBJ2)

debug:
	@echo $(OBJ)
	@echo $(OBJ2)
	@echo $(ODIR)
	@echo $(DEPS)

.PHONY: clean debug all
	