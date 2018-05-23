#define WIN32_LEAN_AND_MEAN

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(linker, "/subsystem:console")
#pragma comment (lib,"glaux.lib")

#include "windows.h"

#include <gl/gl.h>            // standard OpenGL include
#include <gl/glu.h>           // OpenGL utilties
#include <glut.h>             // OpenGL utilties

#include <mmsystem.h>

#include "particleSystem.h"
using namespace MyMathLibrary;


#include "stdlib.h"
#include "stdio.h"

#include "BoundingSphere.h"
#include <vector>

ObjMesh* tankBody;
ObjMesh* tankTurret;
ObjMesh* tankMainGun;
ObjMesh* tankSecondaryGun;
ObjMesh* tankWheel;

ObjMesh* tankBodyLow;
ObjMesh* tankTurretLow;
ObjMesh* tankMainGunLow;
ObjMesh* tankSecondaryGunLow;
ObjMesh* tankWheelLow;

int g_nActiveSystem = 0;
CParticleSystem *g_pParticleSystems[1];
void initParticles(void);
float  g_fElpasedTime;
double g_dCurTime;
double g_dLastTime;


void load_tank_objs(void);
void load_low_tank_objs(void);
void drawObject(ObjMesh *pMesh);
void potentialPenetration(void);
void potentialPenetrationLine(MyVector v);


float zPos = -250.0;
float yRot = 0.0;
float zRot = 0.0;

//Position pos;
float dotX = 0.0;
float dotY = -50.0;
float dotZ = 0.0;


// Variables for rotating different objects
float tRot = 0.0; // Turret rot
float mgRot = 0.0; // Main gun
float sgRot = 0.0; // Secondary gun
float wrRot = 0.0; // Wheels right
float wlRot = 0.0; // Wheels left

				   // List id's
int tankBodyid;
int tankTurretid;
int tankMainGunid;
int tankSecondaryGunid;
int tankWheelid;
int tankBodyLowid;
int tankTurretLowid;
int tankMainGunLowid;
int tankSecondaryGunLowid;
int tankWheelLowid;
// Vectors to hold lists of mesh objects
std::vector <ObjMesh*> wholeTankVector;
std::vector <ObjMesh*> tankBodyVector;
std::vector <ObjMesh*> tankTurretVector;
std::vector <ObjMesh*> tankMainGunVector;
std::vector <ObjMesh*> tankSecondaryGunVector;
std::vector <ObjMesh*> tankWheelVector;

// Declaring the spheres
BoundingSphere wholeTankSphere;
BoundingSphere tankBodySphere;
BoundingSphere tankTurretSphere;
BoundingSphere tankMainGunSphere;
BoundingSphere tankSecondaryGunSphere;
BoundingSphere tankWheelSphere;

//prototypes for our callback functions
void draw(void);    //our drawing routine
void idle(void);    //what to do when nothing is happening
void key(unsigned char k, int x, int y);  //handle key presses
void reshape(int width, int height);      //when the window is resized
void init_drawing(void); //drawing intialisation
void drawPoint(void);
void hitIsTrue(BoundingSphere hitSphere, int sphereid);
Position closestPoint(MyVector line, Position center);

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
	initParticles();
	load_tank_objs();
	load_low_tank_objs();


	// Lists
	tankBodyid = glGenLists(1);
	tankTurretid = tankBodyid + 1;
	tankMainGunid = tankBodyid + 2;
	tankSecondaryGunid = tankBodyid + 3;
	tankWheelid = tankBodyid + 4;
	/*tankBodyLowid = tankBodyid + 5;
	tankTurretLowid = tankBodyid + 6;
	tankMainGunLowid = tankBodyid + 7;
	tankSecondaryGunLowid = tankBodyid + 8;
	tankWheelLowid = tankBodyid + 9;*/

	// Adding objects to the vectors
	wholeTankVector.resize(5);
	wholeTankVector[0] = tankBody;
	wholeTankVector[1] = tankTurret;
	wholeTankVector[2] = tankMainGun;
	wholeTankVector[3] = tankSecondaryGun;
	wholeTankVector[4] = tankWheel;

	tankBodyVector.resize(1);
	tankBodyVector[0] = tankBody;

	tankTurretVector.resize(1);
	tankTurretVector[0] = tankTurret;

	tankMainGunVector.resize(1);
	tankMainGunVector[0] = tankMainGun;

	tankSecondaryGunVector.resize(1);
	tankSecondaryGunVector[0] = tankSecondaryGun;

	tankWheelVector.resize(1);
	tankWheelVector[0] = tankWheel;

	// Initializing the spheres, calculating radius and center
	wholeTankSphere.initMesh(wholeTankVector);
	tankBodySphere.initMesh(tankBodyVector);
	tankTurretSphere.initMesh(tankTurretVector);
	tankMainGunSphere.initMesh(tankMainGunVector);
	tankSecondaryGunSphere.initMesh(tankSecondaryGunVector);
	tankWheelSphere.initMesh(tankWheelVector);

	glNewList(tankBodyid, GL_COMPILE);
	//DrawOBJ(tankBody->m_iMeshID);
	drawObject(tankBody);
	/*glPushMatrix();
	glColor3f(1, 1, 1);
	GLUquadricObj* quad = gluNewQuadric();
	glTranslatef(tankTurretSphere.center.x, tankTurretSphere.center.y, tankTurretSphere.center.z);
	gluSphere(quad, tankTurretSphere.radius, 40, 20);
	glTranslatef(-tankTurretSphere.center.x, -tankTurretSphere.center.y, -tankTurretSphere.center.z);
	gluDeleteQuadric(quad);
	printf("%f  ", tankTurretSphere.radius);
	glPopMatrix();
	*/
	
	glEndList();

	glNewList(tankTurretid, GL_COMPILE);
	//DrawOBJ(tankTurret->m_iMeshID);
	drawObject(tankTurret);
	glEndList();

	glNewList(tankMainGunid, GL_COMPILE);
	//DrawOBJ(tankMainGun->m_iMeshID);
	drawObject(tankMainGun);
	glEndList();

	glNewList(tankSecondaryGunid, GL_COMPILE);
	//DrawOBJ(tankSecondaryGun->m_iMeshID);
	drawObject(tankSecondaryGun);
	glEndList();

	glNewList(tankWheelid, GL_COMPILE);
	//DrawOBJ(tankWheel->m_iMeshID);
	drawObject(tankWheel);
	glEndList();



	//tell glut the names of our callback functions point to our 
	//functions that we defined at the start of this file
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutIdleFunc(idle);
	glutDisplayFunc(draw);

	//request a window size of 600 x 600
	glutInitWindowSize(600, 600);
	glutReshapeWindow(600, 600);


	//go into the main loop
	//this loop won't terminate until the user exits the 
	//application
	glutMainLoop();
	return 0;
}

void load_tank_objs(void)
{
	tankBody = LoadOBJ(".\\tankobjs\\tankbody.obj");
	tankTurret = LoadOBJ(".\\tankobjs\\tankturret.obj");
	tankMainGun = LoadOBJ(".\\tankobjs\\tankmaingun.obj");
	tankSecondaryGun = LoadOBJ(".\\tankobjs\\tanksecondarygun.obj");
	tankWheel = LoadOBJ(".\\tankobjs\\tankwheel.obj");
	SetTextures(tankBody->m_iMeshID, NULL, ".\\tankobjs\\texture.tga");
}

void load_low_tank_objs(void)
{
	tankBodyLow = LoadOBJ(".\\tankobjs\\tankbodyLow.obj");
	tankTurretLow = LoadOBJ(".\\tankobjs\\tankturretLow.obj");
	tankMainGunLow = LoadOBJ(".\\tankobjs\\tankmaingunLow.obj");
	tankSecondaryGunLow = LoadOBJ(".\\tankobjs\\tanksecondarygunLow.obj");
	tankWheelLow = LoadOBJ(".\\tankobjs\\tankwheelLow.obj");
	//SetTextures(tankBody->m_iMeshID, NULL, ".\\tankobjs\\texture.tga");
}

void draw_tank(float x, float y, float z)
{


	glPushMatrix();
	glTranslatef(x, y, z);

	//glScalef(0.1, 0.1, 0.1); //reduce the size of the tank on screen
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
									//DrawOBJ(tankBody->m_iMeshID);
	glCallList(tankBodyid);



	//Use your own draw code here to draw the rest of the tank
	//Here's the code for each individual part
	//Each part is placed with respect to the origin
	//you'll need to add in glPushMatrix/glTranslatef/glRotatef/glPopMatrix commands as necessary
	//DrawOBJ(tankTurret->m_iMeshID);
	//DrawOBJ(tankMainGun->m_iMeshID);
	//DrawOBJ(tankSecondaryGun->m_iMeshID);
	//DrawOBJ(tankWheel->m_iMeshID);

	// Select turret
	glPushMatrix();
	glTranslatef(0.0, 13.0, 0.0);
	glRotatef(tRot, 0.0, 1.0, 0.0); // Rotates turret and children
	glCallList(tankTurretid);
	// Select main gun
	glPushMatrix();
	glTranslatef(20.0, -30.0, 25.0);
	glRotatef(mgRot, 1.0, 0.0, 0.0); // Rotate main gun
	glTranslatef(-20.0, 30.0, -25.0);
	glTranslatef(54.0, -102.0, 10.0);
	glCallList(tankMainGunid);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-13.0, 14.5, -4.0);
	glTranslatef(0.0, 0.0, -10.0); // translate to where we want to rotate around in z
	glRotatef(sgRot, 0.0, 1.0, 0.0);
	glTranslatef(0.0, 0.0, 10.0); // translate back
	glCallList(tankSecondaryGunid);
	glPopMatrix();
	glPopMatrix();
	//WHEELS ON THE RIGHT SIDE
	glPushMatrix();
	glTranslatef(-24.0, -10.0, 43.0);
	glRotatef(wrRot, 1.0, 0.0, 0.0);
	glCallList(tankWheelid);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-24.0, -10.0, 22.0);
	glRotatef(wrRot, 1.0, 0.0, 0.0);
	DrawOBJ(tankWheel->m_iMeshID);
	glPopMatrix();


	float wheelz = 22;
	for (int i = 0; i < 5; i++)
	{
		wheelz -= 15;
		glPushMatrix();
		glTranslatef(-24.0, -10.0, wheelz);
		glRotatef(wrRot, 1.0, 0.0, 0.0);
		DrawOBJ(tankWheel->m_iMeshID);
		glPopMatrix();
	}

	//WHEELS ON THE LEFT SIDE
	glPushMatrix();
	glTranslatef(24.0, -10.0, 43.0);
	glRotatef(180, 0.0, 0.0, 1.0);
	glRotatef(-wlRot, 1.0, 0.0, 0.0);
	DrawOBJ(tankWheel->m_iMeshID);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(24.0, -10.0, 22.0);
	glRotatef(180, 0.0, 0.0, 1.0);
	glRotatef(-wlRot, 1.0, 0.0, 0.0);
	DrawOBJ(tankWheel->m_iMeshID);
	glPopMatrix();
	wheelz = 22;
	for (int i = 0; i < 5; i++)
	{
		wheelz -= 15;
		glPushMatrix();
		glTranslatef(24.0, -10.0, wheelz);
		glRotatef(180, 0.0, 0.0, 1.0);
		glRotatef(-wlRot, 1.0, 0.0, 0.0);
		DrawOBJ(tankWheel->m_iMeshID);
		glPopMatrix();
	}
	glPopMatrix();

}

void draw_tank_low(float x, float y, float z)
{


	glPushMatrix();
	glTranslatef(x, y, z);

	//glScalef(0.1, 0.1, 0.1);		//reduce the size of the tank on screen
									//DrawOBJ(tankBody->m_iMeshID);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glColor3ub(49, 41, 30);
	DrawOBJ(tankBodyLow->m_iMeshID);



	//Use your own draw code here to draw the rest of the tank
	//Here's the code for each individual part
	//Each part is placed with respect to the origin
	//you'll need to add in glPushMatrix/glTranslatef/glRotatef/glPopMatrix commands as necessary
	//DrawOBJ(tankTurret->m_iMeshID);
	//DrawOBJ(tankMainGun->m_iMeshID);
	//DrawOBJ(tankSecondaryGun->m_iMeshID);
	//DrawOBJ(tankWheel->m_iMeshID);

	// Select turret
	glPushMatrix();
	glTranslatef(0.0, 13.0, 0.0);
	glRotatef(tRot, 0.0, 1.0, 0.0); // Rotates turret and children
	DrawOBJ(tankTurretLow->m_iMeshID);
	// Select main gun
	glPushMatrix();
	glTranslatef(20.0, -30.0, 25.0);
	glRotatef(mgRot, 1.0, 0.0, 0.0); // Rotate main gun
	glTranslatef(-20.0, 30.0, -25.0);
	glTranslatef(54.0, -102.0, 10.0);
	DrawOBJ(tankMainGunLow->m_iMeshID);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-13.0, 14.5, -4.0);
	glTranslatef(0.0, 0.0, -10.0); // translate to where we want to rotate around in z
	glRotatef(sgRot, 0.0, 1.0, 0.0);
	glTranslatef(0.0, 0.0, 10.0); // translate back
	DrawOBJ(tankSecondaryGunLow->m_iMeshID);
	glPopMatrix();
	glPopMatrix();
	//WHEELS ON THE RIGHT SIDE
	glPushMatrix();
	glTranslatef(-24.0, -10.0, 43.0);
	glRotatef(wrRot, 1.0, 0.0, 0.0);
	DrawOBJ(tankWheelLow->m_iMeshID);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-24.0, -10.0, 22.0);
	glRotatef(wrRot, 1.0, 0.0, 0.0);
	DrawOBJ(tankWheelLow->m_iMeshID);
	glPopMatrix();


	float wheelz = 22;
	for (int i = 0; i < 5; i++)
	{
		wheelz -= 15;
		glPushMatrix();
		glTranslatef(-24.0, -10.0, wheelz);
		glRotatef(wrRot, 1.0, 0.0, 0.0);
		DrawOBJ(tankWheelLow->m_iMeshID);
		glPopMatrix();
	}

	//WHEELS ON THE LEFT SIDE
	glPushMatrix();
	glTranslatef(24.0, -10.0, 43.0);
	glRotatef(180, 0.0, 0.0, 1.0);
	glRotatef(-wlRot, 1.0, 0.0, 0.0);
	DrawOBJ(tankWheelLow->m_iMeshID);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(24.0, -10.0, 22.0);
	glRotatef(180, 0.0, 0.0, 1.0);
	glRotatef(-wlRot, 1.0, 0.0, 0.0);
	DrawOBJ(tankWheelLow->m_iMeshID);
	glPopMatrix();
	wheelz = 22;
	for (int i = 0; i < 5; i++)
	{
		wheelz -= 15;
		glPushMatrix();
		glTranslatef(24.0, -10.0, wheelz);
		glRotatef(180, 0.0, 0.0, 1.0);
		glRotatef(-wlRot, 1.0, 0.0, 0.0);
		DrawOBJ(tankWheelLow->m_iMeshID);
		glPopMatrix();
	}
	glPopMatrix();

}

//draw callback function - this is called by glut whenever the 
//window needs to be redrawn
void draw(void)
{
	//printf("draw");
	//clear the current window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//make changes to the modelview matrix
	glMatrixMode(GL_MODELVIEW);
	//initialise the modelview matrix to the identity matrix
	glLoadIdentity();

	glTranslatef(0.0, 0.0, zPos);

	glRotatef(yRot, 0.0, 1.0, 0.0);
	glRotatef(zRot, 0.0, 0.0, 1.0);

	//draw the tank on screen at a position
	float switchPoint = -500.0;
	if (zPos > switchPoint)
	{
		draw_tank(0.0, 0.0, 0.0);
	}
	else
	{
		draw_tank_low(0.0, 0.0, 0.0);
	}
	
	drawPoint();

	/*
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, g_pParticleSystems[g_nActiveSystem]->GetTextureID());
	//g_pParticleSystems[0]->SetPosition(MyVector(dotX,dotY,dotZ));
	g_pParticleSystems[g_nActiveSystem]->Render();
	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);

	*/


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

	g_dCurTime = timeGetTime();
	g_fElpasedTime = (float)((g_dCurTime - g_dLastTime) * 0.001);
	g_dLastTime = g_dCurTime;

	g_pParticleSystems[g_nActiveSystem]->Update((float)g_fElpasedTime);
	glutPostRedisplay();
}


//key callback function - called whenever the user presses a 
//key
void key(unsigned char k, int x, int y)
{
	switch (k)
	{
	case 'd':
		//zPos--;
		zPos-= 10;
		break;
	case 'e':
		zPos += 10;
		break;
	case 'r':
		yRot += 5;
		break;
	case 't':
		yRot -= 5;
		break;
	case 'q':
		zRot -= 5;
		break;
	case 'i':
		tRot += 5;
		break;
	case 'o':
		if (mgRot > -10.0) {
			mgRot -= 5;
		}
		break;
	case 'p':
		if (mgRot < 10.0) {
			mgRot += 5;
		}
		break;

	case '9':
		sgRot += 5;
		break;
	case 'k':
		wlRot += 5;
		break;
	case 'l':
		wrRot += 5;
		break;
	case 'g': //left arrow
		dotX -= 5;
		break;
	case 'y': //up arrow
		dotY += 5;
		break;
	case 'j': //right
		dotX += 5;
		break;
	case 'h': //down
		dotY -= 5;
		break;
	case 'v':
		dotZ += 5;
		break;
	case 'b':
		dotZ -= 5;
		break;



	case 27: //27 is the ASCII code for the ESCAPE key
		exit(0);
		break;
	}
	glutPostRedisplay();
}

//reshape callback function - called when the window size changed
void reshape(int width, int height)
{
	//set the viewport to be the same width and height as the window
	glViewport(0, 0, width, height);
	//make changes to the projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//set up our projection type
	//we'll be using a perspective projection, with a 90 degree 
	//field of view
	//gluPerspective(45.0, (float)width / (float)height, 1.0, 100.0);
	gluPerspective(45.0, (float)width / (float)height, 1.0, 1000.0);
	
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

	GLfloat specular[] = { 0.2,0.2,0.2,1.0 };
	GLfloat ambient[] = { 1.0,1.0,1.0,1.0 };
	GLfloat diffuse[] = { 1.0,1.0,1.0,1.0 };
	GLfloat position[] = { 0.0,30.0,0.0,1.0 };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHTING);

	GLfloat position1[] = { 10.0,30.0,0.0,1.0 };
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, position1);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);



	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);
}
void drawObject(ObjMesh *pMesh)
{
	glBegin(GL_TRIANGLES);
	// Loop through each face 
	for (int i = 0; i < pMesh->m_iNumberOfFaces; i++) {
		ObjFace *pf = &pMesh->m_aFaces[i]; //Get a specific face

										   //Counting to three, since each face comes in sets of three
		for (int j = 0; j < 3; j++)
		{
			int tc_i = pf->m_aTexCoordIndicies[j];	//Get the specific texture coordinate index
			int nor_i = pf->m_aNormalIndices[j];	//Get the specific normal index
			int ver_i = pf->m_aVertexIndices[j];	//Get the specific verrticies index

													//The drawing
			glTexCoord2f(pMesh->m_aTexCoordArray[tc_i].u, pMesh->m_aTexCoordArray[tc_i].v);
			glNormal3f(pMesh->m_aNormalArray[nor_i].x, pMesh->m_aNormalArray[nor_i].y, pMesh->m_aNormalArray[nor_i].z);
			glVertex3f(pMesh->m_aVertexArray[ver_i].x, pMesh->m_aVertexArray[ver_i].y, pMesh->m_aVertexArray[ver_i].z);
		}

	}
	glEnd();
}

void potentialPenetration(void) {
	
	MyVector vec;
	vec.x = dotX - wholeTankSphere.center.x;
	vec.y = dotY - wholeTankSphere.center.y;
	vec.z = dotZ - wholeTankSphere.center.z;

	float veclength = vec.getMagnitude();

	if (veclength < wholeTankSphere.radius) {

		// Hit on whole sphere, check body
		// TANKBODY
		vec.x = dotX - tankBodySphere.center.x;
		vec.y = dotY - tankBodySphere.center.y;
		vec.z = dotZ - tankBodySphere.center.z;

		 veclength = vec.getMagnitude();
		if (veclength < tankBodySphere.radius) {
			// We inside radius, so it is a hit
			// Now check next thing -> turret
			vec.x = dotX - tankTurretSphere.center.x;
			vec.y = dotY - tankTurretSphere.center.y;
			vec.z = dotZ - tankTurretSphere.center.z;

			veclength = vec.getMagnitude();
			if (veclength < tankTurretSphere.radius) {
				// Hit on turret
				// Check main guin
				vec.x = dotX - tankMainGunSphere.center.x;
				vec.y = dotY - tankMainGunSphere.center.y;
				vec.z = dotZ - tankMainGunSphere.center.z;

				veclength = vec.getMagnitude();
				if (veclength < tankMainGunSphere.radius)
				{
					// hit on main gun
					printf("Hit on main gun");
					hitIsTrue(tankMainGunSphere, tankMainGunid);
					return;
				}

				// Check secondary gun
				vec.x = dotX - tankSecondaryGunSphere.center.x;
				vec.y = dotY - tankSecondaryGunSphere.center.y;
				vec.z = dotZ - tankSecondaryGunSphere.center.z;
				veclength = vec.getMagnitude();
				if (veclength < tankSecondaryGunSphere.radius)
				{
					//hit on secondary gun
					printf("Hit on secondary gun");
					hitIsTrue(tankSecondaryGunSphere, tankSecondaryGunid);
					return;
				}

				printf("Hit on turret");
				//hitIsTrue(tankTurretSphere, tankTurretid);
				return;
			}

			// Check wheels
			vec.x = dotX - tankWheelSphere.center.x;
			vec.y = dotY - tankWheelSphere.center.y;
			vec.z = dotZ - tankWheelSphere.center.z;
			veclength = vec.getMagnitude();
			if (veclength < tankWheelSphere.radius)
			{
				//hit on wheel
				hitIsTrue(tankWheelSphere, tankWheelid);
				printf("Hit on Wheel");
			}
			hitIsTrue(tankBodySphere, tankBodyid);
			printf("Hit on Body");
			
			return;
		}
	}
}

void drawPoint(void)
{
	MyVector t(dotX, dotY, dotZ);
	glPointSize(10.0);
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(dotX,dotY,dotZ);
	glBegin(GL_POINTS);
	glVertex3f(0.0, 0.0, 0.0);
	glEnd();
	glPopMatrix();

	glColor3f(1.0, 1.0, 1.0);


	printf("%f ", dotX);
	printf("%f ", dotY);
	printf("%f ", dotZ);
	//MyVector v(30.0, 70.0, 20.0);
	potentialPenetration();
}

void hitIsTrue(BoundingSphere hitSphere, int sphereid) {
	printf("Inne i HitIsTrue ");
	//We have a hit on current dotX,dotY,dotZ position.
	// Now we can draw spheres
	//printf("%f ",hitSphere.center);
	//printf("%f RADIUS:  ", hitSphere.radius);
	/*glTranslatef(0.0, 0.0,0.0);
	glNewList(sphereid, GL_COMPILE);
	glPushMatrix();
		glColor3f(1, 1, 1);
		GLUquadricObj* quad = gluNewQuadric();
		glTranslatef(hitSphere.center.x, hitSphere.center.y, hitSphere.center.z);
		gluSphere(quad, hitSphere.radius, 40, 20);
		glTranslatef(-hitSphere.center.x, -hitSphere.center.y, -hitSphere.center.z);
		gluDeleteQuadric(quad);
	glPopMatrix();
	glEndList();*/


	
	glPushMatrix();
		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_FALSE);

		
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
		g_pParticleSystems[0]->SetPosition(MyVector(dotX, dotY, dotZ));
		g_pParticleSystems[g_nActiveSystem]->RenderSimple();

		glDepthMask(GL_TRUE);

		/*
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		//specify blending function here using glBlendFunc

		glBindTexture(GL_TEXTURE_2D, g_pParticleSystems[g_nActiveSystem]->GetTextureID());
		g_pParticleSystems[0]->SetPosition(MyVector(dotX,dotY,dotZ));
		g_pParticleSystems[g_nActiveSystem]->Render();
		glDisable(GL_BLEND);
		glDepthMask(GL_TRUE);

		*/
		
	glPopMatrix();
	//glBindTexture(GL_TEXTURE_2D, NULL);
	
}

void potentialPenetrationLine(MyVector v) {
	MyVector vec;
	Position point = closestPoint(v, wholeTankSphere.center);
	vec.x = point.x - wholeTankSphere.center.x;
	vec.y = point.y - wholeTankSphere.center.y;
	vec.z = point.z - wholeTankSphere.center.z;

	float veclength = vec.getMagnitude();

	if (veclength < wholeTankSphere.radius) {

		// Hit on whole sphere, check body
		// TANKBODY
	    point = closestPoint(v, tankBodySphere.center);
		vec.x = point.x - tankBodySphere.center.x;
		vec.y = point.y - tankBodySphere.center.y;
		vec.z = point.z - tankBodySphere.center.z;

		float veclength = vec.getMagnitude();
		if (veclength < tankBodySphere.radius) {
			// We inside radius, so it is a hit
			// Now check next thing -> turret
			 point = closestPoint(v, tankTurretSphere.center);
			vec.x = point.x - tankTurretSphere.center.x;
			vec.y = point.y - tankTurretSphere.center.y;
			vec.z = point.z - tankTurretSphere.center.z;

			veclength = vec.getMagnitude();
			if (veclength < tankTurretSphere.radius) {
				// Hit on turret
				// Check main guin
				 point = closestPoint(v, tankMainGunSphere.center);
				vec.x = point.x - tankMainGunSphere.center.x;
				vec.y = point.y - tankMainGunSphere.center.y;
				vec.z = point.z - tankMainGunSphere.center.z;

				veclength = vec.getMagnitude();
				if (veclength < tankMainGunSphere.radius)
				{
					// hit on main gun
					printf("Hit on main gun");
					//hitIsTrue(tankMainGunSphere, tankMainGunid);
					return;
				}

				// Check secondary gun
			 point = closestPoint(v, tankSecondaryGunSphere.center);
				vec.x = point.x - tankSecondaryGunSphere.center.x;
				vec.y = point.y - tankSecondaryGunSphere.center.y;
				vec.z = point.z - tankSecondaryGunSphere.center.z;
				veclength = vec.getMagnitude();
				if (veclength < tankSecondaryGunSphere.radius)
				{
					//hit on secondary gun
					printf("Hit on secondary gun");
					//hitIsTrue(tankSecondaryGunSphere, tankSecondaryGunid);
					return;
				}

				printf("Hit on turret");
				//hitIsTrue(tankTurretSphere, tankTurretid);
				return;
			}

			// Check wheels
			 point = closestPoint(v, tankWheelSphere.center);
			vec.x = point.x - tankWheelSphere.center.x;
			vec.y = point.y - tankWheelSphere.center.y;
			vec.z = point.z - tankWheelSphere.center.z;
			veclength = vec.getMagnitude();
			if (veclength < tankWheelSphere.radius)
			{
				//hit on wheel
			}
			printf("Hit on Body");
			//hitIsTrue(tankBodySphere, tankBodyid);
			return;
		}
	}
}

	Position closestPoint(MyVector line, Position center) {
		MyVector v = line;
		MyVector ap(center.x - line.x, center.y - line.y, center.z - line.z);

		float vm2 = (float)v.getMagnitude() * (float)v.getMagnitude();

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
		c.x = line.x + (double)t * v.x;
		c.y = line.y + t * v.y;
		c.z = line.z + t * v.z;
		return c;
	}
	void initParticles(void)
	{
		g_dCurTime = timeGetTime();
		g_fElpasedTime = (float)((g_dCurTime - g_dLastTime) * 0.001);
		g_dLastTime = g_dCurTime;


		//
		// Exploding burst
		//

		g_pParticleSystems[0] = new CParticleSystem();

		//g_pParticleSystems[0]->SetTexture( "..\\particle.bmp" );
		g_pParticleSystems[0]->SetTexture("particle.bmp");
		g_pParticleSystems[0]->SetMaxParticles(100);
		g_pParticleSystems[0]->SetNumToRelease(100);
		g_pParticleSystems[0]->SetReleaseInterval(0.05f);
		g_pParticleSystems[0]->SetLifeCycle(0.5f);
		g_pParticleSystems[0]->SetSize(30.0f);
		g_pParticleSystems[0]->SetColor(MyVector(1.0f, 1.0f, 1.0f));
		g_pParticleSystems[0]->SetPosition(MyVector(50.0f, 0.0f, 0.0f));
		g_pParticleSystems[0]->SetVelocity(MyVector(0.0f, 0.0f, 0.0f));
		g_pParticleSystems[0]->SetGravity(MyVector(0.0f, 0.0f, 0.0f));
		g_pParticleSystems[0]->SetWind(MyVector(0.0f, 0.0f, 0.0f));
		g_pParticleSystems[0]->SetVelocityVar(10.0f);

		g_pParticleSystems[0]->Init();
	}


