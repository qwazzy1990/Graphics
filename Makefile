



# Frameworks for newer MACOS, where include files are moved
INCLUDES = -F/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/System/Library/Frameworks/ -framework OpenGL -framework GLUT -lm -Wno-deprecated-declarations
# Mac OS opengl target
TARGET = -mmacosx-version-min=10.8

# Vic library
LIB_INC = -I./include

# Run the program.
run: compile
	cd bin; ./run image.txt

#compile the program
compile:
	gcc -Wall -std=c11 ./assets/*.c -o ./bin/run $(INCLUDES) $(TARGET)


