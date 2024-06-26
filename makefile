# Define the compiler
CC = g++

# Define the compiler flags
CCFLAGS = -IC:\MinGW\include\SDL2 -c

# Define the linker flags
LDFLAGS = -LC:\MinGW\lib -lmingw32 -lSDL2main -lSDL2


# Rule to build the executable
out.exe: base.o render.o
	$(CC) base.o render.o -o out.exe $(LDFLAGS)

base.o: base.cpp render.hh
	$(CC) $(CCFLAGS) base.cpp -o base.o

render.o: render.hh render.cpp
	$(CC) $(CCFLAGS) render.cpp -o render.o

# Clean rule to remove the executable
clean:
	del -fR *.o
	del -fR out.exe