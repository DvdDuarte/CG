#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


#define _USE_MATH_DEFINES


float camX = 00, camY = 30, camZ = 40;
int startX, startY, tracking = 0;
float raio = 10;

float alpha = 0, beta = 35, r = 10;

int w,h;
char s[30];
int timebase=0;
int frame=0;

float orange[4] = {0.8f, 0.4f , 0.4f,1.0f};
float green[4] = {0.4f, 0.8f, 0.4f, 1.0f};
float black[4] = {0.0f,0.0f,0.0f,0.0f};
float white[4] = {1.0f, 1.0f , 1.0f,1.0f};
float blue[4] = { 0.0f, 0.45f, 0.8f, 1.0f };

unsigned int picked = 0;


void converte() {

	camX = raio * cos(beta) * sin(alpha);
	camY = raio * sin(beta);
	camZ = raio * cos(beta) * cos(alpha);
}

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void draw_axis(){
    glBegin(GL_LINES);
    // X axis in red
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-100.0f, 0.0f, 0.0f);
    glVertex3f( 100.0f, 0.0f, 0.0f);
    // Y Axis in Green
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -100.0f, 0.0f);
    glVertex3f(0.0f, 100.0f, 0.0f);
    // Z Axis in Blue
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f,-100.0f);
    glVertex3f(0.0f, 0.0f, 100.0f);
    glEnd();
}

void drawCylinder(float radius, float height, int slices) {

// put code to draw cylinder in here
	
	// Base
	float angle = (2*M_PI) / slices;
	for (int slice = 1; slice <= slices; slice++){
		glBegin(GL_TRIANGLES);
		if(slice%2 == 0) glColor3f(1.0f,0.2f,1.0f);
		else glColor3f(1.0f,0.0f,1.0f);
		glVertex3f(0,0,0);
		glVertex3f(radius*sin(angle*slice),0,radius*cos(angle*slice));
		glVertex3f(radius*sin(angle*(slice+1)),0,radius*cos(angle*(slice+1)));
		glEnd();
	}

	// Sides
	for(int side = 1; side <= slices; side++){
		glBegin(GL_TRIANGLES);
		// 1 Triangulo
		glColor3f(0.0f,0.5f,1.0f);
		glVertex3f(radius*sin(angle*(side+1)),0,radius*cos(angle*(side+1))); // P1
		glVertex3f(radius*sin(angle*(side+1)),height,radius*cos(angle*(side+1))); // P2
		glVertex3f(radius*sin(angle*side),height,radius*cos(angle*side)); // P3		

		// 2 Triangulo
		glColor3f(0.0f,0.3f,1.0f);
		glVertex3f(radius*sin(angle*side),height,radius*cos(angle*side)); // P3
		glVertex3f(radius*sin(angle*side),0,radius*cos(angle*side)); // P4
		glVertex3f(radius*sin(angle*(side+1)),0,radius*cos(angle*(side+1))); // P1x

		glEnd();
	}

	// Topo
	for (int slice = 1; slice <= slices; slice++){
		glBegin(GL_TRIANGLES);
		if(slice%2 == 0) glColor3f(0.0f,0.2f,1.0f);
		else glColor3f(0.0f,0.0f,1.0f);
		glVertex3f(0,height,0);
		glVertex3f(radius*sin(angle*slice),height,radius*cos(angle*slice));
		glVertex3f(radius*sin(angle*(slice+1)),height,radius*cos(angle*(slice+1)));
		glEnd();
	}

}


void drawCone(float radius, float height, int slices) {

// put code to draw cone in here
	
	// Base
	float angle = (2*M_PI) / slices;
	for (int slice = 1; slice <= slices; slice++){
		glBegin(GL_TRIANGLES);
		if(slice%2 == 0) glColor3f(1.0f,0.2f,1.0f);
		else glColor3f(1.0f,0.0f,1.0f);
		glVertex3f(0,0,0);
		glVertex3f(radius*sin(angle*slice),0,radius*cos(angle*slice));
		glVertex3f(radius*sin(angle*(slice+1)),0,radius*cos(angle*(slice+1)));
		glEnd();
	}

	// Sides
	float color = 0.0;
	for(int side = 1; side <= slices; side++){
		glBegin(GL_TRIANGLES);

		// 1 Triangulo
		glColor3f(color,0.0f,0.0f);
		glVertex3f(radius*sin(angle*(side+1)),0,radius*cos(angle*(side+1))); // P1
		glVertex3f(0,height,0); // P2
		glVertex3f(radius*sin(angle*side),0,radius*cos(angle*side)); // P4	
		color = color + 0.1;

		glEnd();
	}

}

void drawCube() {
	   glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
      // Top face (y = 1.0f)
      // Define vertices in counter-clockwise (CCW) order with normal pointing out
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
      glVertex3f( 1.0f, 1.0f, -1.0f);
      glVertex3f(-1.0f, 1.0f, -1.0f);
      glVertex3f(-1.0f, 1.0f,  1.0f);
      glVertex3f( 1.0f, 1.0f,  1.0f);
 
      // Bottom face (y = -1.0f)
      glColor3f(1.0f, 0.5f, 0.0f);     // Orange
      glVertex3f( 1.0f, -1.0f,  1.0f);
      glVertex3f(-1.0f, -1.0f,  1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f( 1.0f, -1.0f, -1.0f);
 
      // Front face  (z = 1.0f)
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f( 1.0f,  1.0f, 1.0f);
      glVertex3f(-1.0f,  1.0f, 1.0f);
      glVertex3f(-1.0f, -1.0f, 1.0f);
      glVertex3f( 1.0f, -1.0f, 1.0f);
 
      // Back face (z = -1.0f)
      glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
      glVertex3f( 1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f,  1.0f, -1.0f);
      glVertex3f( 1.0f,  1.0f, -1.0f);
 
      // Left face (x = -1.0f)
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(-1.0f,  1.0f,  1.0f);
      glVertex3f(-1.0f,  1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f,  1.0f);
 
      // Right face (x = 1.0f)
      glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
      glVertex3f(1.0f,  1.0f, -1.0f);
      glVertex3f(1.0f,  1.0f,  1.0f);
      glVertex3f(1.0f, -1.0f,  1.0f);
      glVertex3f(1.0f, -1.0f, -1.0f);
   glEnd();  // End of drawing color-cube
}

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(5.0,5.0,5.0, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

	draw_axis();
	//drawCylinder(1,2,20);
	//drawCube();
	glRotatef(45, 0, 0, 1);
	glTranslatef(0,sin(45),cos(45));
	drawCube();
	//drawCone(1,2,20);
	// End of frame
	glutSwapBuffers();
}


void processNormalKeys(unsigned char key, int x, int y) {

	switch(key) {
	
		case 27: exit(0);
		case 'c': printf("Camera : %f %f %f\n", alpha, beta, r); break;
	}
}

unsigned char  picking(int x, int y) {

	unsigned char res[4];

	return res[0];
}

void processMouseButtons(int button, int state, int xx, int yy) 
{
	printf("%d %d\n", xx, yy);
	if (state == GLUT_DOWN)  {
		startX = xx;
		startY = yy;
		if (button == GLUT_LEFT_BUTTON)
			tracking = 1;
		else if (button == GLUT_RIGHT_BUTTON)
			tracking = 2;
		else { // Middle button
			tracking = 0;
			picked = picking(xx,yy);
			if (picked)
				printf("Picked Snowman number %d\n", picked);
			else
				printf("Nothing selected\n");
			glutPostRedisplay();
		}
	}
	else if (state == GLUT_UP) {
		if (tracking == 1) {
			alpha += (xx - startX);
			beta += (yy - startY);
		}
		else if (tracking == 2) {
			
			r -= yy - startY;
			if (r < 3)
				r = 3.0;
		}
		tracking = 0;
	}
}


void processMouseMotion(int xx, int yy)
{

	int deltaX, deltaY;
	int alphaAux, betaAux;
	int rAux;

	if (!tracking)
		return;

	deltaX = xx - startX;
	deltaY = yy - startY;

	if (tracking == 1) {


		alphaAux = alpha + deltaX;
		betaAux = beta + deltaY;

		if (betaAux > 85.0)
			betaAux = 85.0;
		else if (betaAux < -85.0)
			betaAux = -85.0;

		rAux = r;
	}
	else if (tracking == 2) {

		alphaAux = alpha;
		betaAux = beta;
		rAux = r - deltaY;
		if (rAux < 3)
			rAux = 3;
	}
	camX = rAux * sin(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
	camZ = rAux * cos(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
	camY = rAux * 							     sin(betaAux * 3.14 / 180.0);

	glutPostRedisplay();
}



void processSpecialKeys(int key, int xx, int yy) {

// put code to process special keys in here

}

int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");
		
// registo de funções 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

// registo da funções do teclado e rato
	glutKeyboardFunc(processNormalKeys);
	glutMouseFunc(processMouseButtons);
	glutMotionFunc(processMouseMotion);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
