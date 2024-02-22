# Compiler flags
CXXFLAGS := -IC:\minge\include   # Add SDL2 include path
LDFLAGS := -LC:\minge\lib             # Add SDL2 library path

# OBJS specifies which files to compile as part of the project
OBJS := BulletHole.o LTexture.o LTarget.o OpenBlank.o Sound.o SDL.o Media.o Movement.o Player.o Hud.o Game.o Event.o Detect.o Round.o Title.o Rounds/Fountain.o Rounds/Telephone.o Rounds/Simon.o Rounds/Speller.o Rounds/ShootNumbers.o Rounds/Asteroids.o Rounds/QuickDraw.o Rounds/Burger.o Rounds/Saloon.o Background.o

# OBJ_NAME specifies the name of our executable
OBJ_NAME := OpenBlank

# This is the target that compiles our executable
all: $(OBJ_NAME)

$(OBJ_NAME): $(OBJS)
	g++ $(OBJS) $(LDFLAGS) -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf -o $(OBJ_NAME)

# Rule to compile source files
%.o: %.cpp
	g++ $(CXXFLAGS) -c $< -o $@

clean:
	del $(OBJ_NAME).exe
	del *.o

