#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>




void display(void)
{
    //Clear all pixels
    glClear(GL_COLOR_BUFFER_BIT);

    //draw white polygon (rectangle) with corners at
    // (0.25, 0.25, 0.0) and (0.75, 0.75, 0.0)
    glColor3f(0.0,1.0,0.0);
    glBegin(GL_POLYGON);
        glVertex3f(0.50, 0.25, 0.0);
        glVertex3f(0.75, 0.25, 0.0);
        glVertex3f(0.75, 0.75, 0.0);
        glVertex3f(0.25, 0.75, 0.0);
    glEnd();
    
    // Don't wait start processing buffered OpenGL routines
    glFlush();
}
void init(void)
{
    //select clearing (background) color
    glClearColor(0.0, 0.0, 0.0, 0.0);

    //initialize viewing values 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

}

void splice(char** s, int idx, char* ss)
{
	char* temp = *s;
	char* prefix = calloc(strlen(*s)+strlen(ss)+10, sizeof(char));
	char* postfix = calloc(strlen(*s)+strlen(ss)+10, sizeof(char));
	for(int i = 0; i < idx; i++)
		prefix[i] = temp[i];
	
	int c = 0;
	int end = strlen(*s) - idx;
	for(int i = idx+1; i <=  end; i++)
	{
		postfix[c] = temp[i];
		c++;
	}
	strcat(prefix, ss);
	strcat(prefix, postfix);
	free(*s);
	*s = calloc(strlen(prefix)+10, sizeof(char));
	strcpy(*s, prefix);
	free(prefix);
	free(postfix);
	
}


void generate(char** s, int maxdepth, int count)
{
	printf("s is %s\n", *s);
	if(count == maxdepth)return;

	
	char* temp = *s;
	for(int i = 0; i < strlen(temp); i++)
	{
		if(temp[i] == 'a'){
		   splice(s, i, "ab");

		   generate(s, maxdepth, count+1);
		   i++;
		}
		else 
		{
		   splice(s, i, "a");
		   generate(s, maxdepth, count+1);
		}
	}
}
int main(int argc, char* argv[])
{
	

	//Initialise GLUT with command-line parameters. 
    glutInit(&argc, argv);
    
    	//Set Display Mode
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    
    //Set the window size
    glutInitWindowSize(250,250);
    
    //Set the window position
    glutInitWindowPosition(100,100);
    
    //Create the window
    glutCreateWindow("A Simple OpenGL Windows Application with GLUT");
    
    //Call init (initialise GLUT
    init();
    
    //Call "display" function
    glutDisplayFunc(display);
    
	char* s = calloc(20, sizeof(char));
	strcpy(s, "a");
	generate(&s, 3, 0);
	printf("%s\n", s);
	free(s);
    //Enter the GLUT event loop
    //glutMainLoop();
}


