#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include<iostream>
using namespace std;

int rasterSize[] = { 800, 600 };
float canvasSize[] = { 10.f, 10.f };
float mousePosition[2];
float color[3];

void init(){

	color[0] = color[1] = color[2] = 0.0f;
}

//Function to draw a Cursor Point (Purely Aesthetic)
void drawCursor() {

	glColor3f(0.0f, 1.0f, 1.0f); //Cyan cursor color
	glPointSize(10.0f);
	glBegin(GL_POINTS); //Using a Point Primitive to set the cursor
		glVertex2fv(mousePosition);
	glEnd();
	glPointSize(1.0f);
}

//Callback Function - Display
void display(void){

	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3fv(color);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	drawCursor();
	glutSwapBuffers();
}

//Callback Function - Reshape
void reshape(int w, int h){

	rasterSize[0] = w;
	rasterSize[1] = h;
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0.0, canvasSize[0], 0.0, canvasSize[1]);
	glViewport(0, 0, rasterSize[0], rasterSize[1]);

	glutPostRedisplay();
	
}

//Callback Function - Keyboard
void keyboard(unsigned char key, int x, int y){

	switch (key){
		
		case 27: exit(0); break; //27 is ASCII for Esc key, in this case it is used to exit the program.
	}
}

//Callback Function - Mouse
void mouse(int button, int state, int x, int y){

	mousePosition[0] = (float)x / rasterSize[0] * canvasSize[0];
	mousePosition[1] = (float)(rasterSize[1] - y) / rasterSize[1] * canvasSize[1];

	glutPostRedisplay();
}

//Callback Function - Is called when the mouse is in motion
void motion(int x, int y){

	mousePosition[0] = (float)x / rasterSize[0] * canvasSize[0];
	mousePosition[1] = (float)(rasterSize[1] - y) / rasterSize[1] * canvasSize[1];

	glutPostRedisplay();
}


int main(int argc, char* argv[]) {

	init();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(rasterSize[0], rasterSize[1]);
	glutCreateWindow("ScrapPad");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutPassiveMotionFunc(motion);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);

	return 0;
}