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

void drawPlane (float units, int divisions) {

	float halfx = 0, halfz = 0, halfx_temp = 0, halfz_temp = 0, aux_x1 = 0, aux_z1 = 0, aux_x2 = 0, aux_z2 = 0;
    halfx = halfz = units / 2;
    halfx_temp = halfz_temp = units / divisions;

    for (int i = 0; -halfx + i * halfx_temp < halfx; i++) {
        for (int j = 0; -halfz + j * halfz_temp < halfz; j++) {
	    	glBegin(GL_TRIANGLES);

            aux_x1 = -halfx + (i * halfx_temp);
            aux_z1 = -halfz + (j * halfz_temp);
            aux_x2 = -halfx + ((i + 1) * halfx_temp);
            aux_z2 = -halfz + ((j + 1) * halfz_temp);

			// T1
			glVertex3f(aux_x1, 0 , aux_z1); //v1
            glVertex3f(aux_x1, 0, aux_z2); //v2
            glVertex3f(aux_x2, 0 , aux_z2); //v3

			// T2
			glVertex3f(aux_x2, 0 , aux_z2); //v3
            glVertex3f(aux_x2, 0 ,aux_z1); //v4
			glVertex3f(aux_x1, 0 , aux_z1); //v1

    		glEnd();
			
        }


	}

/*
	for(int division = 1; division <= divisions; division++) {
    	glBegin(GL_TRIANGLES);

		// Triangulo 1
		glColor3f(0.0f,0.5f,1.0f);

		glVertex3f(0.0f, 0.0f, 0.0f); // P1
		glVertex3f(1.0f, 0.0f, 0.0f); // P2
		glVertex3f(1.0f, 0.0f, 1.0f); // P3

		//Triangulo 2
		glColor3f(0.0f,0.3f,1.0f);
		
		glVertex3f(0.0f, 0.0f, 0.0f); // P1
		glVertex3f(-1.0f, 1.0f, 0.0f); //P3
		glVertex3f(-1.0f, -1.0f, 0.0f); //P
    	glEnd();
	}
    */
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
		glVertex3f(radius*sin(angle*(side+1)),0,radius*cos(angle*(side+1))); // P1

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

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(5.0,5.0,5.0, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

	//draw_axis();
    drawPlane(5,10);
	drawCylinder(1,2,20);
	//drawCone(1,2,20);

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
