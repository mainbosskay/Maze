#SOURCES identifies the files to be compiled for the project
SOURCES = src/*.c

#COMPILER indicates the compiler we are using
COMPILER = gcc

#INCLUDE_DIRS defines the additional include paths required
INCLUDE_DIRS = -ISDL2\include\SDL2

#LIBRARY_DIRS defines the additional library paths required
LIBRARY_DIRS = -LSDL2\lib

#FLAGS defines the additional compilation options we are using
# -w suppresses all warnings
# -Wl,-subsystem,windows gets rid of the console window
FLAGS = -Wall -Werror -Wextra -pedantic

#LINKER_FLAGS indicates the libraries we are linking against
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2
LINUX_LINKER_FLAGS = -lSDL2 -lm

#EXECUTABLE defines the name of our executable
EXECUTABLE = maze

#This target compiles our executable
all : $(SOURCES)
	$(COMPILER) $(SOURCES) $(INCLUDE_DIRS) $(LIBRARY_DIRS) $(FLAGS) $(LINKER_FLAGS) -o $(EXECUTABLE)

#Compiling SDL on Linux
linux : $(SOURCES)
	$(COMPILER) $(SOURCES) $(FLAGS) $(LINUX_LINKER_FLAGS) -DLINUX -o $(EXECUTABLE)

#Installation SDL on Linux
linux_install : 
	sudo apt-get install libsdl2-dev

#Compiling SDL on MAC
mac : $(SOURCES)
	$(COMPILER) $(SOURCES) $(FLAGS) $(LINUX_LINKER_FLAGS) -DMAC -o $(EXECUTABLE)