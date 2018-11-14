#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <glut.h>

#define GLUT_KEY_ESCAPE 27
#define DEG2RAD(a) (a * 0.0174532925)

class Vector3f {
public:
	float x, y, z;

	Vector3f(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) {
		x = _x;
		y = _y;
		z = _z;
	}

	Vector3f operator+(Vector3f &v) {
		return Vector3f(x + v.x, y + v.y, z + v.z);
	}

	Vector3f operator-(Vector3f &v) {
		return Vector3f(x - v.x, y - v.y, z - v.z);
	}

	Vector3f operator*(float n) {
		return Vector3f(x * n, y * n, z * n);
	}

	Vector3f operator/(float n) {
		return Vector3f(x / n, y / n, z / n);
	}

	Vector3f unit() {
		return *this / sqrt(x * x + y * y + z * z);
	}

	Vector3f cross(Vector3f v) {
		return Vector3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}
};

class Camera {
public:
	Vector3f eye, center, up;

	Camera(float eyeX = -1.0f, float eyeY = 1.0f, float eyeZ = 3.0f, float centerX = 0.0f, float centerY = 0.0f, float centerZ = 0.0f, float upX = 0.0f, float upY = 1.0f, float upZ = 0.0f) {
		eye = Vector3f(eyeX, eyeY, eyeZ);
		center = Vector3f(centerX, centerY, centerZ);
		up = Vector3f(upX, upY, upZ);
	}

	void moveX(float d) {
		Vector3f right = up.cross(center - eye).unit();
		eye = eye + right * d;
		center = center + right * d;
	}

	void moveY(float d) {
		eye = eye + up.unit() * d;
		center = center + up.unit() * d;
	}

	void moveZ(float d) {
		Vector3f view = (center - eye).unit();
		eye = eye + view * d;
		center = center + view * d;
	}

	void rotateX(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + up * sin(DEG2RAD(a));
		up = view.cross(right);
		center = eye + view;
	}

	void rotateY(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + right * sin(DEG2RAD(a));
		right = view.cross(up);
		center = eye + view;
	}

	void look() {
		gluLookAt(
			eye.x, eye.y, eye.z,
			center.x, center.y, center.z,
			up.x, up.y, up.z
			);
	}
};

Camera camera;

void setupCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 2000/ 1000, 0.001, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera.look();
}

void setupLights() {
	GLfloat ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat diffuse[] = { 0.6f, 0.6f, 0.6, 1.0f };
	GLfloat specular[] = { 1.0f, 1.0f, 1.0, 1.0f };
	GLfloat shininess[] = { 50 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

	GLfloat lightIntensity[] = { 0.7f, 0.7f, 1, 1.0f };
	GLfloat lightPosition[] = { -7.0f, 6.0f, 3.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightIntensity);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
}

void drawWall(double thickness) {
	glPushMatrix();
	glTranslated(1, 0.5* thickness, 1);
	glScaled(2, thickness, 2);
	glutSolidCube(1);
	glPopMatrix();
}
void drawRoom(Vector3f left,Vector3f right, Vector3f front ,Vector3f floor){
	glPushMatrix();
	//glTranslated(-0.5, 0, 0.5);
	//glRotated(45, 0, 1, 0);
	//glRotated(-7, 1, 0, 0);
	glColor3f(floor.x, floor.y, floor.z);
	drawWall(0.02);

	glColor3f(left.x, left.y, left.z);
	glPushMatrix();
	glRotated(90, 0, 0, 1.0);
	drawWall(0.02);
	glPopMatrix();

	//glColor3f(0, 0, 0);
	glColor3f(front.x, front.y, front.z);
	glPushMatrix();
	glRotated(-90, 1.0, 0.0, 0.0);
	drawWall(0.02);
	glPopMatrix();

	glColor3f(right.x, right.y, right.z);
	glPushMatrix();
	glTranslated(2, 0, 0);
	glRotated(90, 0, 0, 1.0);
	drawWall(0.02);
	glPopMatrix();

	glPopMatrix();
}

void drawCouch(){
	glPushMatrix();
	//glRotated(-90, 0, 1, 0);
	//back
	glColor3f(0, 0, 0);
	glPushMatrix();
	//glTranslated(0.6, 0.2, 0.025);
	glTranslated(0, 0.2, 0.025);
	glScaled(1.2, 0.4, 0.05);
	glutSolidCube(1);
	glPopMatrix();

	//base
	glColor3f(0, 0, 0);
	glPushMatrix();
	//glTranslated(0.6, 0.06, 0.125);
	glTranslated(0, 0.06, 0.125);
	glScaled(1.1, 0.12, 0.25);
	glutSolidCube(1);
	glPopMatrix();

	//cusions
	glColor3f(0.7, 0.4, 0);
	glPushMatrix();
	//glTranslated(0.325, 0.145, 0.125);
	glTranslated(-0.275, 0.145, 0.125);
	glScaled(0.55, 0.05, 0.25);
	glutSolidCube(1);
	glPopMatrix();

	glColor3f(0.7, 0.42, 0);
	glPushMatrix();
	//glTranslated(0.875, 0.145, 0.125);
	glTranslated(0.275, 0.145, 0.125);
	glScaled(0.55, 0.05, 0.25);
	glutSolidCube(1);
	glPopMatrix();

	//rests
	glColor3f(0, 0, 0);
	glPushMatrix();
	glTranslated(0.575, 0.095, 0.125);
	glScaled(0.05, 0.19, 0.25);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.575, 0.095, 0.125);
	glScaled(0.05, 0.19, 0.25);
	glutSolidCube(1);
	glPopMatrix();

	glPopMatrix();
}

void drawChair(){
	glPushMatrix();
	drawCouch();
	glPopMatrix();
}

void drawTableLeg(double thick, double len) {
	glPushMatrix();
	glTranslated(0, len / 2, 0);
	glScaled(thick, len, thick);
	glutSolidCube(1.0);
	glPopMatrix();
}
void drawTable(double topWid, double topThick, double legThick, double legLen){
	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslated(0, legLen, 0);
	glScaled(topWid, topThick, topWid);
	glutSolidCube(1.0);
	glPopMatrix();

	glColor3f(0, 0, 0);
	double dist = 0.95*topWid / 2.0 - legThick / 2.0;
	glPushMatrix();
	glTranslated(dist, 0, dist);
	drawTableLeg(legThick, legLen);
	glTranslated(0, 0, -2 * dist);
	drawTableLeg(legThick, legLen);
	glTranslated(-2 * dist, 0, 2 * dist);
	drawTableLeg(legThick, legLen);
	glTranslated(0, 0, -2 * dist);
	drawTableLeg(legThick, legLen);
	glPopMatrix();
}
void drawTVTable(){
	glPushMatrix();
	//Sekeleton
	glPushMatrix();
	glScaled(0.8, 0.3, 0.30);
	glutSolidCube(1);
	glPopMatrix();

	//drawers
	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslated(-0.20, 0, 0);
	glScaled(0.3, 0.15, 0.31);
	glutSolidCube(1);
	glPopMatrix();

	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslated(0.20, 0, 0);
	glScaled(0.3, 0.15, 0.31);
	glutSolidCube(1);
	glPopMatrix();

	glPopMatrix();
}

void drawTVStorage(){
	glPushMatrix();

	glColor3f(0, 0, 0);
	glPushMatrix();
	glScaled(0.11, 0.11, 0.05);
	glutSolidCube(1);
	glPopMatrix();

	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslated(0, 0, 0.01);
	glScaled(0.1, 0.1, 0.05);
	glutSolidCube(1);
	glPopMatrix();

	glColor3f(0, 0, 0);
	glPushMatrix();
	glTranslated(-0.040, 0.005,0.035);
	glScaled(0.005, 0.005, 0.005);
	glutSolidSphere(1,15,15);
	glPopMatrix();

	glPopMatrix();
}

void drawTV(){
	glPushMatrix();

	glColor3f(0.1, 0.1, 0.1);
	glPushMatrix();
	glTranslated(0.16, 0.4, 1);
	glScaled(0.2, 0.2, 0.2);
	glutSolidCube(1);
	glPopMatrix();

	glColor3f(0.4, 0.4, 0.4);
	glPushMatrix();
	glTranslated(0.18, 0.4, 1);
	glScaled(0.17, 0.17, 0.17);
	glutSolidCube(1);
	glPopMatrix();

	glPopMatrix();
}
void drawLivingRoom(){
	Vector3f left = Vector3f(0.54, 0.27, 0.07);
	Vector3f right = Vector3f(1, 0.9, 0.6);
	Vector3f front = Vector3f(1, 0.9,0.6);
	Vector3f floor = Vector3f(0.7, 0.4, 0.2);
	drawRoom(left,right,front,floor);
	//large couch
	glPushMatrix();
	glTranslated(0.9, 0,0);
	drawCouch();
	glPopMatrix();

	//small couch
	glPushMatrix();
	glTranslated(1.975, 0, 0.8);
	glRotated(-90, 0, 1, 0);
	glScaled(0.55, 1, 1);
	drawChair();
	glPopMatrix();

	//chair
	glPushMatrix();
	glTranslated(1.975, 0, 1.7);
	glRotated(-90, 0, 1, 0);
	glScaled(0.25, 1, 1);
	drawChair();
	glPopMatrix();

	//table
	glPushMatrix();
	glTranslated(1.85, 0.0, 1.325);
	glRotated(90, 0, 1, 0);
	drawTable(0.2, 0.02, 0.02, 0.1);
	glPopMatrix();

	//tvtable
	glPushMatrix();
	glTranslated(0.15, 0.15, 1.2);
	glRotated(90, 0, 1, 0);
	drawTVTable();
	glPopMatrix();

	//tvstorage
	glPushMatrix();
	glTranslated(0.025, 0.75, 1);
	glRotated(90, 0, 1, 0);
	drawTVStorage();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.025, 0.64, 1.11);
	glRotated(90, 0, 1, 0);
	drawTVStorage();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.025, 0.53, 1.22);
	glRotated(90, 0, 1, 0);
	drawTVStorage();
	glPopMatrix();

	//TV
	drawTV();
}

void drawBed(){
	glPushMatrix();

	//base
	glPushMatrix();
	glScaled(0.9, 0.15, 1);
	glutSolidCube(1);
	glPopMatrix();

	//matress
	glColor3f(0, 0, 0);
	glPushMatrix();
	glTranslated(0, 0.125, 0);
	glScaled(0.8, 0.10, 0.95);
	glutSolidCube(1);
	glPopMatrix();

	//cushion9s
	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslated(-0.20, 0.19, -0.35);
	glScaled(0.3, 0.05, 0.12);
	glutSolidCube(1);
	glPopMatrix();

	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslated(0.20, 0.19, -0.35);
	glScaled(0.3, 0.05, 0.12);
	glutSolidCube(1);
	glPopMatrix();

	glPopMatrix();
}

void drawCupBoard(){
	glPushMatrix();

	//skeleton
	glPushMatrix();
	glScaled(0.2, 0.9, 0.9);
	glutSolidCube(1);
	glPopMatrix();

	//firstlayer
	glColor3f(0, 0, 0);
	glPushMatrix();
	glTranslated(0.01, 0, 0.3);
	glScaled(0.2, 0.8, 0.25);
	glutSolidCube(1);
	glPopMatrix();

	glColor3f(0, 0, 0);
	glPushMatrix();
	glTranslated(0.01, 0, 0);
	glScaled(0.2, 0.8, 0.25);
	glutSolidCube(1);
	glPopMatrix();

	glColor3f(0, 0, 0);
	glPushMatrix();
	glTranslated(0.01, 0, -0.3);
	glScaled(0.2, 0.8, 0.25);
	glutSolidCube(1);
	glPopMatrix();

	glPopMatrix();
}



void drawComode(){
	glPushMatrix();

	//sekelton
	glPushMatrix();
	glScaled(0.25, 0.25, 0.25);
	glutSolidCube(1);
	glPopMatrix();

	//drawer
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslated(0, 0.095, 0.02);
	glScaled(0.20, 0.05, 0.24);
	glutSolidCube(1);
	glPopMatrix();

	//door
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslated(0, -0.0125, 0.02);
	glScaled(0.20, 0.12, 0.24);
	glutSolidCube(1);

	glPopMatrix();

	glPopMatrix();
}

void drawLamp(){
	glPushMatrix();
	//base
	glPushMatrix();
	glScaled(0.025, 0.0125, 0.025);
	glRotated(90, 1, 0, 0);
	glutSolidTorus(1,1,15,15);
	glPopMatrix();

	//stand
	glPushMatrix();
	glTranslated(0, 0.1, 0);
	glScaled(0.01, 0.2, 0.01);
	glutSolidCube(1);
	glPopMatrix();

	//head
	glPushMatrix();
	glTranslated(0, 0.155, 0);
	glRotated(-90, 1, 0, 0);
	glutSolidCone(0.1, 0.05, 15, 15);
	glPopMatrix();

	glPopMatrix();

}

void drawChairBedRoom(){
	glPushMatrix();
	//base
	glPushMatrix();
	drawTable(0.15, 0.01, 0.01, 0.1);
	glPopMatrix();

	//back
	glPushMatrix();
	glTranslated(0, 0.18, -0.07);
	glScaled(0.15, 0.15, 0.01);
	glutSolidCube(1);
	glPopMatrix();

	glPopMatrix();
}

void drawDesk(){
	glPushMatrix();

	//top
	glColor3f(0, 0, 0);
	glPushMatrix();
	glScaled(0.3, 0.1, 0.4);
	glutSolidCube(1);
	glPopMatrix();

	//bigdrawer
	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslated(-0.01, 0, -0.07);
	glScaled(0.3, 0.08, 0.25 );
	glutSolidCube(1);
	glPopMatrix();

	//small drawer
	glPushMatrix();
	glTranslated(-0.01, 0, 0.127);
	glScaled(0.3, 0.08, 0.12);
	glutSolidCube(1);
	glPopMatrix();
	
	//right leg
	glColor3f(0, 0,1);
	glPushMatrix();
	glTranslated(0, -0.125, 0.122);
	glScaled(0.3, 0.25, 0.15);
	glutSolidCube(1);
	glPopMatrix();

	//small drawer
	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslated(-0.01, -0.1, 0.127);
	glScaled(0.3, 0.08, 0.12);
	glutSolidCube(1);
	glPopMatrix();

	//small drawer
	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslated(-0.01, -0.2, 0.127);
	glScaled(0.3, 0.08, 0.12);
	glutSolidCube(1);
	glPopMatrix();

	//leftleg
     glPushMatrix();
	 glTranslated(0, -0.125, -0.2);
	 glScaled(0.3, 0.25, 0.02);
	glutSolidCube(1);
	glPopMatrix();

	glPopMatrix();

	//


}
void drawBedRoom(){
	Vector3f left = Vector3f(1, 0.9, 0.5);
	Vector3f right = Vector3f(1, 0.9, 0.5);
	Vector3f front = Vector3f(0.8, 0, 0.1);
	Vector3f floor = Vector3f(1, 0.9, 0.5);
	glPushMatrix();

	glPushMatrix();
	glTranslated(-2.02, 0, 0);
	drawRoom(left,right,front,floor);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.5, 0.075, 0.5);
	drawBed();
	glPopMatrix();
	
	glPushMatrix();
	glTranslated(-1.92, 0.45, 0.55);
	drawCupBoard();
	glPopMatrix();
	//draw chair
	glPushMatrix();
	glTranslated(-0.4, 0.025, 1.4);
	glRotated(90, 0, 1, 0);
	drawChairBedRoom();
	glPopMatrix();

	

	//comode
	glPushMatrix();
	glTranslated(-1.1, 0.125, 0.125);
	drawComode();
	glPopMatrix();
	
	//drawLamp
	glPushMatrix();
	glTranslated(-1.1, 0.25, 0.125);
	drawLamp();
	glPopMatrix();


	//desk
	glPushMatrix();
	glTranslated(-0.155, 0.27, 1.5);
	//glTranslated(-1, 1, 1);
	drawDesk();
	glPopMatrix();
	glPopMatrix();

	
}

void drawGhost(){
	glPushMatrix();
	//body
	glPushMatrix();
	glutSolidSphere(0.15, 15, 15);
	glPopMatrix();

	//head 
	glPushMatrix();
	glTranslated(0, 0.19, 0);
	glutSolidSphere(0.07,15,15);
	glPopMatrix();

	//nose
	glColor3f(1, 0.5, 0.2);
	glPushMatrix();
	glTranslated(0, 0.2, 0.05);
	glutSolidCone(0.015, 0.1, 15,15);
	glPopMatrix();

	glPopMatrix();
}

void Display(){
	setupLights();
	setupCamera();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawLivingRoom();
	drawBedRoom();
	glPushMatrix();
	glTranslated(-1, 0.5, 0.5);
	drawGhost();
	glPopMatrix();
	glFlush();

}
void Keyboard(unsigned char key, int x, int y) {
	float d = 0.01;

	switch (key) {
	case 'w':
		camera.moveY(d);
		break;
	case 's':
		camera.moveY(-d);
		break;
	case 'a':
		camera.moveX(d);
		break;
	case 'd':
		camera.moveX(-d);
		break;
	case 'q':
		camera.moveZ(d);
		break;
	case 'e':
		camera.moveZ(-d);
		break;

	case GLUT_KEY_ESCAPE:
		exit(EXIT_SUCCESS);
	}

	glutPostRedisplay();
}

void Special(int key, int x, int y) {
	float a = 1.0;

	switch (key) {
	case GLUT_KEY_UP:
		camera.rotateX(a);
		break;
	case GLUT_KEY_DOWN:
		camera.rotateX(-a);
		break;
	case GLUT_KEY_LEFT:
		camera.rotateY(a);
		break;
	case GLUT_KEY_RIGHT:
		camera.rotateY(-a);
		break;
	}

	glutPostRedisplay();

}

void main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitWindowSize(2000, 1000);
	glutInitWindowPosition(0, 0);

	glutCreateWindow("Assignment 2");
	glutDisplayFunc(Display);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(Special);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);

	glutMainLoop();
}
