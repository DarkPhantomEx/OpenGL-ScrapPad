#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include<iostream>
using namespace std;

int rasterSize[] = { 800, 600 };

void init(){}
void display(){}
void reshape(int x, int y){}

void keyboard(unsigned char key, int x, int y){}
void mouse(int button, int state, int x, int){}
void motion(int x, int y){}


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