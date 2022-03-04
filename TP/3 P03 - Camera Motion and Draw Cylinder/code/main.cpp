#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

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

	// Slices
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

	// Slices
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

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(5.0,5.0,5.0, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

	//draw_axis();
	drawCylinder(1,2,20);
	drawCone(1,2,20);

	// End of frame
	glutSwapBuffers();
}


void processKeys(unsigned char c, int xx, int yy) {

// put code to process regular keys in here

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
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	
// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
