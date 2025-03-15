EXE = lab_intro
OBJS = main.o png.o rgbapixel.o

COMPILER = g++ 
COMPILER_OPTS = -std=c++17 -c -g -O0 -Wall -Wextra -pedantic-errors -Werror 
LINKER = g++
LINKER_OPTS = -lpng

all : $(EXE)

$(EXE) : $(OBJS)
	$(LINKER) $(OBJS) $(LINKER_OPTS) -o $(EXE)

main.o : main.cpp png.h rgbapixel.h
	$(COMPILER) $(COMPILER_OPTS) main.cpp

png.o : png.cpp png.h rgbapixel.h
	$(COMPILER) $(COMPILER_OPTS) png.cpp

rgbapixel.o : rgbapixel.cpp rgbapixel.h
	$(COMPILER) $(COMPILER_OPTS) rgbapixel.cpp

clean :
	-rm -f *.o $(EXE)
