#define WIN32_LEAN_AND_MEAN

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(linker, "/subsystem:console")

#include "stdlib.h"
#include "windows.h"
#include "stdio.h"

#include <gl/gl.h>            // standard OpenGL include
#include <gl/glu.h>           // OpenGL utilties
#include "glut.h"

//#include "myvector.h"
//#include "mymatrix.h"
#include "myQuat.h"
using namespace MyMathLab;



//prototypes for our callback functions
void draw(void);    //our drawing routine
void idle(void);    //what to do when nothing is happening
void key(unsigned char k, int x, int y);  //handle key presses
void reshape(int width, int height);      //when the window is resized
void init_drawing(void);                  //drawing intialisation
void drawSquare(void);
void drawSquareAroundVertex(void);
void rotateQuat(void);
void rotateQuat2(void);
int angle = 0;
int f;

static GLfloat myIdentityMatrix[16] =
{
	1.0,0.0,0.0,0.0,
	0.0,1.0,0.0,0.0,
	0.0,0.0,1.0,0.0,
	0.0,0.0,0.0,1.0
};

//our main routine
int main(int argc, char *argv[])
{
  //Initialise Glut and create a window
  glutInit(&argc, argv);
  //sets up our display mode
  //here we've selected an RGBA display with depth testing 
  //and double buffering enabled
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
  //create a window and pass through the windows title
  glutCreateWindow("Basic Glut Application");

  //run our own drawing initialisation routine
  init_drawing();

  //tell glut the names of our callback functions point to our 
  //functions that we defined at the start of this file
  glutReshapeFunc(reshape);
  glutKeyboardFunc(key);
  glutIdleFunc(idle);
  glutDisplayFunc(draw);

  //request a window size of 600 x 600
  glutInitWindowSize(600,600);
  glutReshapeWindow(600,600);

  //go into the main loop
  //this loop won't terminate until the user exits the 
  //application
  glutMainLoop();

  return 0;
}

//draw callback function - this is called by glut whenever the 
//window needs to be redrawn
void draw(void)
{
	//clear the current window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//make changes to the modelview matrix
   // glMatrixMode(GL_MODELVIEW);
	//initialise the modelview matrix to the identity matrix
	//glLoadIdentity();

	//***DO ALL YOUR DRAWING HERE****//

	switch (f)
	{
	case 1:
		rotateQuat();
		break;
	case 2:
		rotateQuat2();
		break;
	}



	 
	 GLfloat translationMatrix[16] =
  {
	  1.0,0.0,0.0,0.0,
	  0.0,1.0,0.0,0.0,
	  0.0,0.0,1.0,0.0,
	  1.0,1.0,-5.0,1.0
  };

 GLfloat rotationMatrix[16] =
 {
	 cos(angle),sin(angle),0.0,0.0,
	 -sin(angle),cos(angle),0.0,0.0,
	 0.0,0.0,1.0,0.0,
	 0.0,0.0,0.0,1.0
 };

	MyMatrix matrix;
	matrix.loadIdentity();
	matrix.getGLModelviewMatrix();
	glMatrixMode(GL_MODELVIEW);
	matrix.setGLMatrix();
	glPushMatrix();
	glMultMatrixf(rotationMatrix);
	glMultMatrixf(translationMatrix);

		//glTranslatef(1.0, 1.0, -5.0);
		//glRotatef(angle, 0.0f, 0.0f, -5.0f);
		drawSquare();
	glPopMatrix();
	
	//glPushMatrix();
		//glTranslatef(-1.0, 1.0, -5.0);
		//glRotatef(angle, 0.0f, 0.0f, -5.0f);
		//drawSquare();
	//glPopMatrix();
	
	

  //flush what we've drawn to the buffer
  glFlush();
  //swap the back buffer with the front buffer
  glutSwapBuffers();
}

void drawSquare(void) {
	glBegin(GL_POLYGON);
		glColor3f(1.0,0.0,0.0);
		glVertex3f(-1.0, 1.0, 0.0);
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(-1.0, -1.0, 0.0);
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(1.0, -1.0, 0.0);
		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(1.0, 1.0, 0.0);
	glEnd();

}

//idle callback function - this is called when there is nothing 
//else to do
void idle(void)
{
  //this is a good place to do animation
  //since there are no animations in this test, we can leave 
  //idle() empty
	/*if (angle != 0)
	{
		angle += 5;
		draw();
	}*/
	
}

void drawSquareAroundVertex(void) {
	//clear the current window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//make changes to the modelview matrix
	glMatrixMode(GL_MODELVIEW);
	//initialise the modelview matrix to the identity matrix
	glLoadIdentity();

	//***DO ALL YOUR DRAWING HERE****//

	glPushMatrix();
	glTranslatef(0.0, 0.0, -5.0);
	glRotatef(angle, 0.0, 0.0, 1.0);
	glTranslatef(0.0, 0.0, 5.0);
	glTranslatef(1.0, 1.0, -5.0);
	drawSquare();
	glPopMatrix();

glPushMatrix();
	glTranslatef(0.0, 0.0, -5.0);
	glRotatef(angle, 0.0f, 0.0f, -1.0f);
	glTranslatef(0.0, 0.0, 5.0);
	glTranslatef(-1.0, 1.0, -5.0);
	drawSquare();
	glPopMatrix();

	//flush what we've drawn to the buffer
	glFlush();
	//swap the back buffer with the front buffer
	glutSwapBuffers();
}

//key callback function - called whenever the user presses a 
//key
void key(unsigned char k, int x, int y)
{
  switch(k)
  {
    case 27: //27 is the ASCII code for the ESCAPE key
      exit(0);
      break;
	
	case 114: //r
		angle += 5;
		draw();
		break;
	case 118: //v
		angle += 5;
		drawSquareAroundVertex();
		break;
	
	
	case 49: //1
		f = 1;
		draw();
		break;
	case 50://2
		f = 2;
		draw();
		break;
  }
}

//reshape callback function - called when the window size changed
void reshape(int width, int height)
{
  //set the viewport to be the same width and height as the window
  glViewport(0,0,width, height);
  //make changes to the projection matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  //set up our projection type
  //we'll be using a perspective projection, with a 90 degree 
  //field of view
  gluPerspective(110.0, (float) width / (float) height, 1.0, 100.0);
  //redraw the view during resizing
  draw();
}

//set up OpenGL before we do any drawing
//this function is only called once at the start of the program
void init_drawing(void)
{
  //blend colours across the surface of the polygons
  //another mode to try is GL_FLAT which is flat shading
  glShadeModel(GL_SMOOTH);
  //turn lighting off
  glDisable(GL_LIGHTING);
  //enable OpenGL hidden surface removal
  glDepthFunc(GL_LEQUAL);
  glEnable(GL_DEPTH_TEST);
}


void rotateQuat(void)
{
	//clear the current window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//make changes to the modelview matrix
	glMatrixMode(GL_MODELVIEW);
	//initialise the modelview matrix to the identity matrix
	glLoadIdentity();

	glTranslatef(-3.0, -3.0, -10.0);
	//draw a red horizontal line, one unit long
	glLineWidth(3.0);
	glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	glDisable(GL_LINE_STIPPLE);
	glBegin(GL_LINES);
	glVertex2f(0.0, 0.0);
	glVertex2f(1.0, 0.0);
	glEnd();
	glPopMatrix();

	//draw a blue vertical line, one unit high
	glLineWidth(3.0);
	glColor3f(0.0, 0.0, 1.0);
	glPushMatrix();
	glBegin(GL_LINES);
	glVertex2f(0.0, 0.0);
	glVertex2f(0.0, 1.0);
	glEnd();
	glPopMatrix();

	
	MyQuat qvec;

	qvec.w = 0.0;
	qvec.v.x = 1.0;
	qvec.v.y = 1.0;
	qvec.v.z = 0.0;
	
	MyVector axis;
	axis.x = 0.0;
	axis.y = 0.0;
	axis.z = 1.0;

	axis.normalise();

	MyVector rot;
	float rotangle = DEG2RAD(45); //Half pi rad = 90 deg
	rot.x = sin(rotangle/2);
	rot.y = sin(rotangle / 2);
	rot.z = sin(rotangle / 2);

	MyQuat q1;
	q1.w = cos(rotangle / 2);
	q1.v.x = rot.x*axis.x;
	q1.v.y = rot.y*axis.y;
	q1.v.z = rot.z*axis.z;


	MyQuat q1Conj = q1.getConjugate();
	MyQuat qrA = qvec.multiplyBy(q1Conj);
	MyQuat qres = q1.multiplyBy(qrA);
	
	
	glLineWidth(3.0);
	glColor3f(0.0, 1.0, 0.0);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(qvec.v.x, qvec.v.y, qvec.v.z);
	glEnd();
	glPopMatrix();

	glLineWidth(3.0);
	glColor3f(1.0, 1.0, 0.0);
	glPushMatrix();
		glTranslatef(0.0, 0.0, 0.0);
		glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(qres.v.x, qres.v.y, qres.v.z);
	glEnd();
	glPopMatrix();

}

void rotateQuat2(void)
{
	//clear the current window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//make changes to the modelview matrix
	glMatrixMode(GL_MODELVIEW);
	//initialise the modelview matrix to the identity matrix
	glLoadIdentity();

	glTranslatef(-3.0, -3.0, -10.0);
	//draw a red horizontal line, one unit long
	glLineWidth(3.0);
	glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	glDisable(GL_LINE_STIPPLE);
	glBegin(GL_LINES);
	glVertex2f(0.0, 0.0);
	glVertex2f(1.0, 0.0);
	glEnd();
	glPopMatrix();

	//draw a blue vertical line, one unit high
	glLineWidth(3.0);
	glColor3f(0.0, 0.0, 1.0);
	glPushMatrix();
	glBegin(GL_LINES);
	glVertex2f(0.0, 0.0);
	glVertex2f(0.0, 1.0);
	glEnd();
	glPopMatrix();


	MyQuat qvec;

	qvec.w = 0.0;
	qvec.v.x = 0.0;
	qvec.v.y = -10.0;
	qvec.v.z = 0.0;

	MyVector axis;
	axis.x = 10.0;
	axis.y = 0.0;
	axis.z = 0.0;

	axis.normalise();
	
	MyVector rot;
	float rotangle = DEG2RAD(45); //Half pi rad = 90 deg
	rot.x = sin(rotangle / 2);
	rot.y = sin(rotangle / 2);
	rot.z = sin(rotangle / 2);

	MyQuat q1;
	q1.w = cos(rotangle / 2);
	q1.v.x = rot.x*axis.x;
	q1.v.y = rot.y*axis.y;
	q1.v.z = rot.z*axis.z;


	MyQuat q1Conj = q1.getConjugate();
	MyQuat qrA = qvec.multiplyBy(q1Conj);
	MyQuat qres = q1.multiplyBy(qrA);


	glLineWidth(3.0);
	glColor3f(0.0, 1.0, 0.0);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(qvec.v.x, qvec.v.y, qvec.v.z);
	glEnd();
	glPopMatrix();

	glLineWidth(3.0);
	glColor3f(1.0, 1.0, 0.0);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(qres.v.x, qres.v.y, qres.v.z);
	glEnd();
	glPopMatrix();

	printf("%f  ", qres.v.x);
	printf("%f  ", qres.v.y);
	printf("%f  ", qres.v.z);
}