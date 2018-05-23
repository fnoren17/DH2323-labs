#define WIN32_LEAN_AND_MEAN

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(linker, "/subsystem:console")

#include "windows.h"
#include "vector.h"
#include "glut.h"             // OpenGL utilties
#include "stdio.h"
#include "stdlib.h"

using namespace MyOGLProg;



/******************************************************************
//Global variables												  *
******************************************************************/
int fnum;


/****************************************
//prototypes for our callback functions *
****************************************/
void DisplayScene(void);				  //our drawing routine
void idle(void);						  //what to do when nothing is happening
void key(unsigned char k, int x, int y);  //handle key presses
void reshape(int width, int height);      //when the window is resized
void init_drawing(void);                  //drawing intialisation
void Answer1(void);
void Answer2(void);
void Answer3(void);
void Answer4(void);
void Answer5(void);
void Answer6(void);
void Answer7(void);

void DrawVector(Position& startPos, Vector& v1)
{
	//draw the vector v1 starting from position startPos
	//this function will only work as long as the z coordinate for both positions is zero
	float length = sqrt((v1.x * v1.x) + (v1.y * v1.y) + (v1.z * v1.z));
	Vector v;
	if (length > 0.0){ v.x = v1.x/length; v.y = v1.y/length; v.z = v1.z/length; }
	else return;
	float d = (v.x * 0.0) + (v.y * 1.0) + (v.z * 0.0); //Skalärmultiplikastion med enhets-vektor i y-led
	float a = RAD2DEG(acos(d));
	if (v.x > 0.0) a = -a;

	glPushMatrix();
	glTranslatef(startPos.x, startPos.y, startPos.z);
	glRotatef(a,0.0,0.0,1.0);
	float space = 0.25;
	glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, length, 0.0);

		glVertex3f(0.0, length, 0.0);
		glVertex3f(-space, length - (space * 1.5), 0.0);

		glVertex3f(0.0, length, 0.0);
		glVertex3f(space, length - (space * 1.5), 0.0);
	glEnd();
	glPopMatrix();
}

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
  glutDisplayFunc(DisplayScene);

  //request a window size of 600 x 600
  glutInitWindowSize(600,600);
  glutReshapeWindow(600,600);

  //go into the main loop
  //this loop won't terminate until the user exits the 
  //application
  glutMainLoop();

  return 0;
}



/*****************************************************************************
 DisplayScene()

 The work of the application is done here. This is called by glut whenever the 
//window needs to be redrawn
*****************************************************************************/

void DisplayScene(void)
{
  //clear the current window
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //make changes to the modelview matrix
  glMatrixMode(GL_MODELVIEW);
  //initialise the modelview matrix to the identity matrix
  glLoadIdentity();

  glTranslatef(-3.0,-3.0,-10.0);
  
  /*glColor3f(1.0,0.0,0.0);
  glBegin(GL_POINTS);
	glVertex3f(0.0,0.0,-5.0);
  glEnd();*/

  GLfloat yellow[4] = { 1.0f, 1.0f, 0.2f, 1.0f };
  GLfloat blue[4] = { 0.2f, 0.2f, 1.0f, 1.0f };
  GLfloat green[4] = { 0.2f, 1.0f, 0.2f, 1.0f };
Position origin;
origin.x = origin.y = origin.z = 0.0;

switch (fnum)
{
case 1:
	Answer1();
	break;
case 2:
	Answer2();
	break;
case 3:
	Answer3();
	break;
case 4:
	Answer4();
	break;
case 5:
	Answer5();
	break;
case 6:
	Answer6();
	break;
case 7:
	Answer7();
	break;
}

  //define a position and a vector
/*  
Position p1;
  p1.x = 1.0; p1.y = 1.0; p1.z = 0.0;
  Vector v1(4.0, 4.0, 0.0);

  //draw the vector at position
  glDisable(GL_LINE_STIPPLE);
  glLineWidth(1.0);
  glColor3f(1.0,1.0,0.0);
  DrawVector(p1,v1);
  */

  //draw a red horizontal line, one unit long
  glLineWidth(3.0);
  glColor3f(1.0,0.0,0.0);
  glPushMatrix();
	  glTranslatef(0.0, 0.0, 0.0);
	  glDisable(GL_LINE_STIPPLE);
	  glBegin(GL_LINES);
		glVertex2f(0.0,0.0);
		glVertex2f(1.0,0.0);
	  glEnd();
  glPopMatrix();

  //draw a blue vertical line, one unit high
  glLineWidth(3.0);
  glColor3f(0.0,0.0,1.0);
  glPushMatrix();
	  glBegin(GL_LINES);
		glVertex2f(0.0,0.0);
		glVertex2f(0.0,1.0);
	  glEnd();
  glPopMatrix();

 /* 
  glBegin(GL_TRIANGLES);
  glVertex3f(0.0f, 0.0f, 0.0f);
  glVertex3f(1.0f, 0.0f, 0.0f);
  glVertex3f(0.0f, 1.0f, 0.0f);
  glEnd();
  */

  //draw a white point at the origin
  glPointSize(2.0);
  glColor3f(1.0,1.0,1.0);
  glPushMatrix();
	  glTranslatef(0.0, 0.0, 0.0);
	  glBegin(GL_POINTS);
		glVertex2f(0.0,0.0);
	  glEnd();
  glPopMatrix();

  //flush what we've drawn to the buffer
  glFlush();
  //swap the back buffer with the front buffer
  glutSwapBuffers();
}

//idle callback function - this is called when there is nothing 
//else to do
void idle(void)
{
  //this is a good place to do animation
  //since there are no animations in this test, we can leave 
  //idle() empty
}

//key callback function - called whenever the user presses a 
//key
void key(unsigned char k, int x, int y)
{
  switch(k)
  {
  case 49:
	  fnum = 1;
	  DisplayScene();
	  break;
  case 50:
	  fnum = 2;
	  DisplayScene();
	  break;
  case 51:
	  fnum = 3;
	  DisplayScene();
	  break;
  case 52:
	  fnum = 4;
	  DisplayScene();
	  break;
  case 53:
	  fnum = 5;
	  DisplayScene();
	  break;
  case 54:
	  fnum = 6;
	  DisplayScene();
	  break;
  case 55:
	  fnum = 7;
	  DisplayScene();
	  break;
  case 27: //27 is the ASCII code for the ESCAPE key
     exit(0);
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
  gluPerspective(65.0, (float) width / (float) height, 1.0, 100.0);
  //redraw the view during resizing
  DisplayScene();
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
  //glDepthFunc(GL_LEQUAL);
  //glEnable(GL_DEPTH_TEST);

  //glClearColor(1.0,0.0,0.0,0.0);
}

void Answer1() 
{
	Vector v(4.0, 2.0, 0.0);
	Position p;
	p.x = 1.0; 
	p.y = 2.0; 
	p.z = 0.0;

	glDisable(GL_LINE_STIPPLE);
	glLineWidth(1.0);
	glColor3f(0.0, 1.0, 1.0);
	DrawVector(p, v);
}

void Answer2()
{
	Vector v(4.0, 2.0, 0.0);
	Vector u(-2.0, 3.0, 0.0);
	Position p;
	p.x = 0.0;
	p.y = 0.0;
	p.z = 0.0;

	Vector result = u.addTo(v);
	glDisable(GL_LINE_STIPPLE);
	glLineWidth(1.0);
	glColor3f(0.0, 1.0, 1.0);
	DrawVector(p, result);
}

void Answer3()
{
	Vector v(0.0, 1.0, 0.0);
	Vector u(0.707, 0.707, 0.0);
	Position p;
	p.x = 0.0;
	p.y = 0.0;
	p.z = 0.0;

	glDisable(GL_LINE_STIPPLE);
	glLineWidth(1.0);
	glColor3f(1.0, 0.0, 0.0);
	DrawVector(p, v);

	glColor3f(0.0, 1.0, 0.0);
	DrawVector(p, u);

	u.normalise();
	float dot = u.getDotProduct(v);
	float angle = RAD2DEG(acos(dot));

	printf("%.f ",angle);
}
void Answer4()
{
	Vector v(4.0, 4.0, 0.0);
	Vector u(-2.0, 3.0, 0.0);
	Position p;
	p.x = 0.0;
	p.y = 0.0;
	p.z = 0.0;

	glDisable(GL_LINE_STIPPLE);
	glLineWidth(1.0);
	glColor3f(0.0, 0.0, 1.0);
	DrawVector(p, v);

	glColor3f(0.0, 1.0, 0.0);
	DrawVector(p, u);

	v.normalise();
	u.normalise();

	float dot = v.getDotProduct(u);
	printf("%.f ", dot);

	if(fabs(dot - 1.f) < 0.001)
	{
		printf("Yes ");
	}
	else
	{
		printf("No ");
	}

}
void Answer5()
{
	Vector v(5.0, 4.0, 0.0);
	Vector u(3.0, 9.0, 0.0);
	Position p;
	p.x = 0.0;
	p.y = 0.0;
	p.z = 0.0;

	glDisable(GL_LINE_STIPPLE);
	glLineWidth(1.0);
	glColor3f(0.0, 0.0, 1.0);
	DrawVector(p, v);

	glColor3f(0.0, 1.0, 0.0);
	DrawVector(p, u);

	u.normalise();
	float dot = u.getDotProduct(v);

	glPointSize(5.0);
	glColor3f(0.0, 1.0, 1.0);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	glVertex2f(u.x*dot, u.y*dot);
	glEnd();
	glPopMatrix();


	glLineWidth(3.0);
	glColor3f(1.0, 1.0, 0.0);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	glLineStipple(1, 0x00FF);
	glEnable(GL_LINE_STIPPLE);
	glBegin(GL_LINES);
	glVertex2f(5.0, 4.0);
	glVertex2f(u.x*dot, u.y*dot);
	glDisable(GL_LINE_STIPPLE);
	glEnd();
	glPopMatrix();
}
void Answer6()
{
	Vector v(4.0, -4.0, 0.0);
	Vector u(-9.0, 0.0, 0.0);

	Position p1;
	Position p2;

	p1.x = 1.0;
	p1.y = 8.0;
	p1.z = 0.0;

	p2.x = 3.0;
	p2.y = 0.0;
	p2.z = 0.0;

	glDisable(GL_LINE_STIPPLE);
	glLineWidth(1.0);
	glColor3f(1.0, 0.0, 0.0);
	DrawVector(p1, v);

	glColor3f(0.0, 1.0, 0.0);
	DrawVector(p2, u);

	v.normalise();
	u.normalise();
	float dot = u.getDotProduct(v);
	float angle = RAD2DEG(acos(dot));

	printf("%.f ", angle);
}
void Answer7()
{
	Vector v(7.5, 0.0, 0.0);

	Position a;
	a.x = -2.5;
	a.y = -2.0;
	a.z = 0.0;

	Position p;
	p.x = 8.0;
	p.y = 3.0;
	p.z = 0.0;

	Vector ap(p.x - a.x, p.y - a.y, p.z - a.z);

	float vm2 = (float)v.getMagnitude() * (float) v.getMagnitude();

	float vdotap = v.getDotProduct(ap);
	float t = (float)vdotap / (float)vm2;
	if (t > 1.0)
	{
		t = 1.0;
	}
	else if (t < 0.0)
	{
		t = 0.0;
	}
	Position c;
	c.x = a.x + (double)t * v.x;
	c.y = a.y + t * v.y;
	c.z = a.z + t * v.z;



	glPointSize(5.0);
	glColor3f(0.0, 1.0, 1.0);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	glVertex2f(c.x, c.y);
	glEnd();
	glPopMatrix();

	glPointSize(5.0);
	glColor3f(1.0, 0.0, 1.0);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	glVertex2f(p.x, p.y);
	glEnd();
	glPopMatrix();

	glDisable(GL_LINE_STIPPLE);
	glLineWidth(1.0);
	glColor3f(1.0, 0.0, 0.0);
	DrawVector(a, v);

}
