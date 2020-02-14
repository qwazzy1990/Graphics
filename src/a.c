
/* Derived from scene.c in the The OpenGL Programming Guide */

#include <stdio.h>
#include <stdlib.h>
/*
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
*/
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

	/* flags used to control the appearance of the image */
int lineDrawing = 1;	// draw polygons as solid or lines
int lighting = 0;	// use diffuse and specular lighting
int smoothShading = 0;  // smooth or flat shading
int textures = 0;
GLubyte  Image[64][64][4];
GLuint   textureID[1];

/*  Initialize material property and light source.
 */
void init (void)
{
   GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
   GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat light_full_off[] = {0.0, 0.0, 0.0, 1.0};
   GLfloat light_full_on[] = {1.0, 1.0, 1.0, 1.0};

   GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

	/* if lighting is turned on then use ambient, diffuse and specular
	   lights, otherwise use ambient lighting only */
   if (lighting == 1) {
      glLightfv (GL_LIGHT0, GL_AMBIENT, light_ambient);
      glLightfv (GL_LIGHT0, GL_DIFFUSE, light_diffuse);
      glLightfv (GL_LIGHT0, GL_SPECULAR, light_specular);
   } else {
      glLightfv (GL_LIGHT0, GL_AMBIENT, light_full_on);
      glLightfv (GL_LIGHT0, GL_DIFFUSE, light_full_off);
      glLightfv (GL_LIGHT0, GL_SPECULAR, light_full_off);
   }
   glLightfv (GL_LIGHT0, GL_POSITION, light_position);
   
   glEnable (GL_LIGHTING);
   glEnable (GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);
}

void display (void)
{
GLfloat blue[]  = {0.0, 0.0, 1.0, 1.0};
GLfloat red[]   = {1.0, 0.0, 0.0, 1.0};
GLfloat green[] = {0.0, 1.0, 0.0, 1.0};
GLfloat white[] = {1.0, 1.0, 1.0, 1.0};

   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* draw surfaces as either smooth or flat shaded */
   if (smoothShading == 1)
      glShadeModel(GL_SMOOTH);
   else
      glShadeModel(GL_FLAT);

	/* draw polygons as either solid or outlines */
   if (lineDrawing == 1)
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   else 
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	/* set starting location of objects */
   glPushMatrix ();
   glTranslatef(0.0, 0.0, -7.0);
   glRotatef (20.0, 1.0, 0.0, 0.0);

	/* give all objects the same shininess value */
   glMaterialf(GL_FRONT, GL_SHININESS, 30.0);

	/* set colour of cone */
   glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red);
   glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	/* move to location for object then draw it */
   glPushMatrix ();
   glTranslatef (-0.75, -0.5, 0.0); 
   glRotatef (270.0, 1.0, 0.0, 0.0);
   glutSolidCone (1.0, 2.0, 15, 15);
   glPopMatrix ();

	/* set colour of sphere */
   glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, green);
   glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	/* move to location for object then draw it */
   glPushMatrix ();
   glTranslatef (0.75, 0.0, -1.0); 

	/* turn texturing on */
   if (textures == 1) {
      glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, textureID[0]);
	/* if textured, then use white as base colour */
      glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
   }

   glutSolidSphere (1.0, 20, 20);

   if (textures == 1) 
      glDisable(GL_TEXTURE_2D);
   glPopMatrix ();

	/* set colour of torus */
   glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue);
   glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	/* move to location for object then draw it */
   glPushMatrix ();
   glTranslatef (-0.75, 0.5, 0.0); 
   glRotatef (90.0, 1.0, 0.0, 0.0);
   glutSolidTorus (0.275, 0.85, 15, 15);
   glPopMatrix ();

   glPopMatrix ();
   glFlush ();
}


void splice(char** s, int idx, char* ss)
{
   //use a temp to not change value of og
	char* temp = *s;

   //prefix = temp from 0 up to and including index
	char* prefix = calloc(strlen(*s)+strlen(ss)+10, sizeof(char));
   //postfix = temp from index +1 up to strlen(temp)
	char* postfix = calloc(strlen(*s)+strlen(ss)+10, sizeof(char));

   //copy prefix
	for(int i = 0; i <= idx; i++)
		prefix[i] = temp[i];
	
   //temp idx
	int c = 0;

   //copy from idx+1 to end of temp in postfix
	for(int i = idx+1; i <  strlen(temp); i++)
	{
		postfix[c] = temp[i];
		c++;
	}

   //concatenate substring to prefix
	strcat(prefix, ss);
   //concat postfix to new prefix
	strcat(prefix, postfix);

   //free the prev string
	free(*s);

   //reallocate it
	*s = calloc(strlen(prefix)+10, sizeof(char));

   //strcpy prefix, i.e. new string to *s
	strcpy(*s, prefix);
	free(prefix);
	free(postfix);
	
}
void reshape(int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(45.0, (GLfloat)w/(GLfloat)h, 1.0, 10.0);
   glMatrixMode (GL_MODELVIEW);
   glLoadIdentity ();
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
      case 'q':
         exit(0);
         break;
      case '1':		// draw polygons as outlines
         lineDrawing = 1;
         lighting = 0;
         smoothShading = 0;
         textures = 0;
         init();
         display();
         break;
      case '2':		// draw polygons as filled
         lineDrawing = 0;
         lighting = 0;
         smoothShading = 0;
         textures = 0;
         init();
         display();
         break;
      case '3':		// diffuse and specular lighting, flat shading
         lineDrawing = 0;
         lighting = 1;
         smoothShading = 0;
         textures = 0;
         init();
         display();
         break;
      case '4':		// diffuse and specular lighting, smooth shading
         lineDrawing = 0;
         lighting = 1;
         smoothShading = 1;
         textures = 0;
         init();
         display();
         break;
      case '5':		// texture with  smooth shading
         lineDrawing = 0;
         lighting = 1;
         smoothShading = 1;
         textures = 1;
         init();
         display();
         break;
   }
}

void loadTexture() {
FILE *fp;
int  i, j;
int  red, green, blue;

   if ((fp = fopen("image.txt", "r")) == 0) {
      printf("Error, failed to find the file named image.txt.\n");
      exit(0);
   } 

   for(i=0; i<64; i++) {
      for(j=0; j<64; j++) {
         fscanf(fp, "%d %d %d", &red, &green, &blue);
         Image[i][j][0] = red;
         Image[i][j][1] = green;
         Image[i][j][2] = blue;
         Image[i][j][3] = 255;
      }
   }

   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
   glGenTextures(1,textureID);
   glBindTexture(GL_TEXTURE_2D, textureID[0]);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64, 64, 0, GL_RGBA,
      GL_UNSIGNED_BYTE, Image);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
   glEnable(GL_TEXTURE_GEN_S);
   glEnable(GL_TEXTURE_GEN_T);

   fclose(fp);
}


char* readFile(char* fileName)
{
   FILE* fp = fopen(fileName, "r");
   if(fp == NULL)return NULL;
   rewind(fp);
   fseek(fp, 0L, SEEK_END);
   long len = ftell(fp);
   rewind(fp);
   char* file = calloc(len+21, sizeof(char));
   for(int i = 0; i < len; i++)
   {
      char c = fgetc(fp);
      if(c == EOF)break;
      file[i] = c;
   }
   fclose(fp);
   return file;
}

char** split(char* s, char* delims)
{
   char** arr = calloc(strlen(s), sizeof(char*));
   for(int i = 0; i < strlen(s); i++)
      arr[i] = calloc(strlen(s), sizeof(char));

   int rowCount = 0;
   char* copy = calloc(strlen(s), sizeof(char));
   strcpy(copy, s);

   char* token = strtok(copy, delims);
   while(token != NULL)
   {
      strcpy(arr[rowCount], token);
      token = strtok(NULL, delims);
      rowCount++;      
   }
   free(copy);
   arr[rowCount] = NULL;
   return arr;
}
void lSystem(char** s, int maxdepth, int count) 
{
   printf("Entering function count is %d maxDepth is %d\n", count, maxdepth);
   //base case = max growth
	if(count == maxdepth)return;

   //subtring to be replacing 'F' with is the current state of the string s at the current level
   char* subString = calloc(strlen(*s)+100, sizeof(char));
   //strcpy(subString, "F");
   strcat(subString, *s);

	
   //set temp to *s to ensure you are adjusting the correct 'F'.
	char* temp = *s;
   char** arr = calloc(strlen(*s)+10, sizeof(char*));
   int rowCount = 0; 
   int mem = 0; 
   

   //becuase *s will grow in length within same depth, it is not a staric val
	for(int i = 0; i < strlen(temp); i++)
	{
      //if F is found then replace with F and all of S
		if(temp[i] == 'F' && rowCount == 0){
         mem++;
         arr = calloc(mem, sizeof(char*));
         arr[rowCount] = calloc(strlen(subString)+10, sizeof(char));
         arr[rowCount][0] = 'F';
         strcat(arr[rowCount], subString);
         rowCount++;
         //continue;
         
		}
      //if rowCount = 0 and first character is not F
      else if(rowCount == 0)
      {
         mem++;
         arr = calloc(mem, sizeof(char*));
         arr[rowCount] = calloc(10, sizeof(char));
         arr[rowCount][0] = temp[i];
         rowCount++;
         //continue;
      }
      //see above
      else if(temp[i] == 'F')
      {
         mem++;
         arr = realloc(arr, mem*sizeof(char*));
         arr[rowCount] = calloc(strlen(subString)+10, sizeof(char));
         arr[rowCount][0] = 'F';
         strcat(arr[rowCount], subString);
         rowCount++;
      }
      //just add the character
      else {
         mem ++;
         arr = realloc(arr, mem*sizeof(char*));
         arr[rowCount] = calloc(10, sizeof(char));
         arr[rowCount][0] = temp[i];

         rowCount++;
      }
	}
   mem++;
   //terminate array with NULL
   arr = realloc(arr, mem*sizeof(char*));
   arr[mem] = NULL;

   //free substring
   free(subString);
   free(*s);
   int memSize = 10;

   //get the amount of memory needed for new string
   for(int i = 0; arr[i] != NULL; i++)
   {
   
      memSize += strlen(arr[i]);
   }

   //add the array to *s
   *s = calloc(memSize, sizeof(char));
   for(int i = 0; arr[i] != NULL; i++)
   {
      strcat(*s, arr[i]);
   }

   //free the array
   for(int i = 0; i < mem; i++)
   {
      free(arr[i]);
   }
   free(arr);

   //recursive call on lSys
   lSystem(s, maxdepth, count+1);
   //recurse   

}
/*  Main Loop
 *  Open window with initial window size, title bar, 
 *  RGBA display mode, and handle input events.
 */
int main(int argc, char** argv)
{
   // glutInit(&argc, argv);
   // glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
   // glutInitWindowSize (1024, 768);
   // glutCreateWindow (argv[0]);
   // init();
   // loadTexture();
   // glutReshapeFunc (reshape);
   // glutDisplayFunc(display);
   // glutKeyboardFunc (keyboard);
   // glutMainLoop();

   char* s = readFile(argv[1]);
   char** arr = split(s, "\n");

   int maxDepth = atoi(arr[0]);
   int rotation = atof(arr[1]);
   char* lSys = calloc(strlen(arr[2])+10, sizeof(char));
   strcpy(lSys, arr[2]);
   lSystem(&lSys, 4, 1);
   printf("%s\n", lSys);
   free(lSys);
   for(int i = 0; arr[i] != NULL; i++)
      free(arr[i]);
   
   free(arr);
   free(s);
   return 0; 
}

