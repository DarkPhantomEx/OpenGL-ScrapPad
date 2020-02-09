#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include<iostream>
#include<vector>
#include<iterator>
using namespace std;


//Global Variables
int rasterSize[] = { 800, 600 };
float canvasSize[] = { 10.f, 10.f };
float mousePos[2];
float color[3];
float pointSize;
float lineWidth;


//Structure to hold points
struct Points {
	float vertex[2]; //contains x,y
	float Scolor[3];
	float size, width;
}Temp,Temp1;

vector<Points>::iterator It;

//Enumerator that contains the type of Shape to be drawn.
enum shapeType { Point, Line, Triangle, Quad, Poly };
shapeType current;

class ShapeShifter {
public:
	vector<Points> PointsList;	
	int pointsNo;
	shapeType Type;

	ShapeShifter(){
		pointsNo = 0;
		Type = Point;
	}
}S[5]; //0-4 => Same order as enum

void init(){
	S[0].Type = Point;
	S[1].Type = Line;
	S[2].Type = Triangle;
	S[3].Type = Quad;
	S[4].Type = Poly;

	pointSize = 5.0f;
	mousePos[0] = mousePos[1] = 0.0f;
	color[0] = color[1] = color[2] = 0.0f;
}

//Function to draw a Cursor Point (Purely Aesthetic)
void drawCursor() {

	glColor3f(0.0f, 1.0f, 1.0f); //Cyan cursor color
	glPointSize(10.0f);
	glBegin(GL_POINTS); //Using a Point Primitive to set the cursor
		glVertex2fv(mousePos);
	glEnd();
	glPointSize(1.0f);
}

//Callback Function - Display
void display(void){

	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	
	glColor3fv(color);
	glPointSize(pointSize);
	glLineWidth(lineWidth);

		
		for (It = S[0].PointsList.begin(); It != S[0].PointsList.end(); It++) {
			Temp1 = *It;
			glColor3fv(Temp1.Scolor);
			glPointSize(Temp1.size);
			glLineWidth(Temp1.width);
			glBegin(GL_POINTS);			
			glVertex2fv(Temp1.vertex);		
			glEnd();
		}
	

		glBegin(GL_LINE_STRIP);
		for (It = S[1].PointsList.begin(); It != S[1].PointsList.end(); It++) {
			Temp1 = *It;	
			glVertex2fv(Temp1.vertex);			
		}
		glEnd();

		glBegin(GL_TRIANGLES);
		for (It = S[2].PointsList.begin(); It != S[2].PointsList.end(); It++) {
			Temp1 = *It;
			glVertex2fv(Temp1.vertex);
		}
		glEnd();

		glBegin(GL_QUADS);
		for (It = S[3].PointsList.begin(); It != S[3].PointsList.end(); It++) {
			Temp1 = *It;
			glVertex2fv(Temp1.vertex);
		}
		glEnd();

		glBegin(GL_POLYGON);
		for (It = S[4].PointsList.begin(); It != S[4].PointsList.end(); It++) {
			Temp1 = *It;
			glVertex2fv(Temp1.vertex);
		}
		glEnd();

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
	
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		
		mousePos[0] = (float)x / rasterSize[0] * canvasSize[0];
		mousePos[1] = (float)(rasterSize[1] - y) / rasterSize[1] * canvasSize[1];
		Temp.vertex[0] = mousePos[0];
		Temp.vertex[1] = mousePos[1];
		for(int i=0; i<3;i++)
			Temp.Scolor[i] = color[i];
		Temp.size = pointSize;
		Temp.width = lineWidth;
		switch (current)
		{
		case Point: 
			S[0].PointsList.push_back(Temp);
			S[0].pointsNo++;
			glutPostRedisplay();
			break;
		case Line: 
			S[1].PointsList.push_back(Temp);
			S[1].pointsNo++;
			glutPostRedisplay();
			break;
		case Triangle:
			S[2].PointsList.push_back(Temp);
			S[2].pointsNo++;
			glutPostRedisplay();
			break;
		case Quad:
			S[3].PointsList.push_back(Temp);
			S[3].pointsNo++;
			glutPostRedisplay();
			break;
		}
	}
}

//Callback Function - Is called when the mouse is in motion
void motion(int x, int y){

	mousePos[0] = (float)x / rasterSize[0] * canvasSize[0];
	mousePos[1] = (float)(rasterSize[1] - y) / rasterSize[1] * canvasSize[1];

	glutPostRedisplay();
}

//Menu function - Defines what each menu entry does
void menu(int entry){

	switch(entry){
	
		//Clears Display
	case 0: 
		S[0].PointsList.clear();
		S[1].PointsList.clear();
		S[2].PointsList.clear();
		S[3].PointsList.clear();
		S[4].PointsList.clear();
		glutPostRedisplay();
		break;
	case 1: current = Point; break;

	case 2:	current = Line; break;

	case 3: current = Triangle; break;

	case 4: current = Quad; break;

	case 5: current = Poly; break;

	case 6: //Set color to RED 
		color[0] = 1.0f; color[1] = color[2] = 0.0f; break;
	case 7: //Set color to BLUE
		color[2] = 1.0f; color[1] = color[0] = 0.0f; break;
	case 8: //Set color to GREEN
		color[1] = 1.0f; color[0] = color[2] = 0.0f; break;
	case 9: //Set color to BLACK
		color[0] = color[1] = color[2] = 0.0f; break;
	case 10: pointSize = 3.0f; break;
	case 11: pointSize = 5.0f; break;
	case 12: pointSize = 9.0f; break;
	case 14: lineWidth = 1.0f; break;
	case 15: lineWidth = 3.0f; break;
	case 16: lineWidth = 7.0f; break;
	case 13: exit(0);
	}
}

//InitMenu function - Creates the Menu, as well as Sub Menus, and attaches them to RightClick.
void InitMenu()
{
	//Shape SubMenu
	int shapeMenu = glutCreateMenu(menu);
	glutAddMenuEntry("Point", 1);
	glutAddMenuEntry("Line", 2);
	glutAddMenuEntry("Triangle", 3);
	glutAddMenuEntry("Quad", 4);
	glutAddMenuEntry("Polygon", 5);

	//Color SubMenu
	int colorMenu = glutCreateMenu(menu);
	glutAddMenuEntry("Red", 6);
	glutAddMenuEntry("Blue", 7);
	glutAddMenuEntry("Green", 8);
	glutAddMenuEntry("Black", 9);

	//PointSize SubMenu
	int sizeMenu = glutCreateMenu(menu);
	glutAddMenuEntry("Smol", 10);
	glutAddMenuEntry("NotSmol", 11);
	glutAddMenuEntry("VeryNotSmol", 12);
	
	//LineWidth SubMenu
	int widthMenu = glutCreateMenu(menu);
	glutAddMenuEntry("NotThicc", 14);
	glutAddMenuEntry("Thicc", 15);
	glutAddMenuEntry("VeryThicc", 16);



	//Main Menu
	glutCreateMenu(menu);
	glutAddMenuEntry("Clear", 0);
	glutAddSubMenu("Shapes", shapeMenu);
	glutAddSubMenu("Colors", colorMenu);
	glutAddSubMenu("Point Size", sizeMenu);
	glutAddSubMenu("Line Width", widthMenu);
	glutAddMenuEntry("Exit", 13);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

}
int main(int argc, char* argv[]) {

	//Initialization stuff
	init();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(rasterSize[0], rasterSize[1]);
	glutCreateWindow("ScrapPad");

	//Setting Callback functions
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutPassiveMotionFunc(motion);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	
	//Initializes Menu
	InitMenu();

	//MainLoop, program won't really run without this.
	glutMainLoop(); 

	return 0;
}