EXE = intro
OBJS = main.cpp intro.h intro.cpp RGBA/*

COMPILER = g++ 
COMPILER_OPTS = -std=c++17 -c -g -O0 -Wall -Wextra -pedantic-errors -Werror 
LINKER = g++
LINKER_OPTS = -lpng

all : $(EXE)

$(EXE) : $(OBJS)
	$(LINKER) $(OBJS) $(LINKER_OPTS) -o $(EXE)

main.o : main.cpp intro.h RGBA/*
	$(COMPILER) $(COMPILER_OPTS) main.cpp

intro.o : intro.cpp intro.h RGBA/*
	$(COMPILER) $(COMPILER_OPTS) intro.cpp

clean :
	-rm -f *.o $(EXE)
