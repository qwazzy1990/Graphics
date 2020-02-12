




all:
	gcc -Iinclude glad.c main.c dependencies/libglfw.so.3.2 -o output -ldl -L/dependencies/glfw -lm -lGL -lGLU -lglut

clean:
	rm output