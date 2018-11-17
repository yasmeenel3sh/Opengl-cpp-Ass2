#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <glut.h>

#include <string>

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

bool animateBedRoom = false;
bool animateLivingRoom = false;
bool changeColor = false;
bool showGhost = false;
int ghostanimno = 0;
double ghostPosX = 0;
double ghostanimpos = 0.5;
double ghostanimval = 0;
double ghostPosZ = 0;
double animghostRot = 0;
double animghostVal = 0.5;

double ghostShowDuration = 3;
double ghostHideDuration = 4;
//colors

int redD = 1;
int greenD = 1;
int blueD = 1;
//___________________________//
//living room animation values
double animLivingRoomval = 0.05;
double animLivingRoompos = 0;
 //large couch
double LargeCouchanimpos = 0;
double LargeCouchanimval = 0;
 //small couch
double SmallCouchanimpos = 0;
double SmallCouchanimval = 0;
 //chair
double livingchairanimpos = 0;
double livingchairanimval = 0;
//table
double tableanimpos = 0;
double tableanimval = 0;
//tv table
double tvtableanimpos = 0;
double tvtableanimval = 0;
//Tv
double TVanimpos = 0;
double TVanimval = 0;
//TVStorage
double TVStorageanimpos = 0;
double TVStorageanimval = 0;
//__________________________//
//bedroom animation values
double animBedRoomVal = 0.05;
double animBedRoomRot = 0;
int maxheight = 1;
 //desk
double deskanimpos = 0;
double deskanimval = 0.01;
 //bed
double bedanimpos = 0;
double bedanimval = 0.01;
 //lamp
double lampanimpos = 0;
double lampanimval = 0.01;
 //comode
double comodeanimpos = 0;
double comodeanimval = 0.01;
 //cupboard
double cupboardanimpos = 0;
double cupboardanimval = 0.01;

//____________________________//
//living room chaning colors

//TV
Vector3f tvcolor = Vector3f(0, 0, 0);
//Tvstorge
Vector3f tvstoragecolor = Vector3f(0, 0, 0);
//tvtable
Vector3f tvtablecolor = Vector3f(0, 0, 0);
//large couch
Vector3f largecouchcolor = Vector3f(0, 0, 0);
//small couch
Vector3f smallcouchcolor = Vector3f(0, 0, 0);
//livingchair
Vector3f livingchaircolor = Vector3f(0, 0, 0);
//table
Vector3f tablecolor = Vector3f(0, 0, 0);
//___________________________//
//bed room changing colors
//cupboard
Vector3f cupboardcolor = Vector3f(0, 0, 0);
//bed
Vector3f bedcolor = Vector3f(0, 0, 0);
//comode
Vector3f comodecolor = Vector3f(0, 0, 0);
//lamp
Vector3f lampcolor = Vector3f(0, 0, 0);
//desk
Vector3f deskcolor = Vector3f(0, 0, 0);


class Camera {
public:
	Vector3f eye, center, up;

	Camera(float eyeX = -0.5f, float eyeY = 1.0f, float eyeZ = 4.0f, float centerX = 0.0f, float centerY = 0.0f, float centerZ = 0.0f, float upX = 0.0f, float upY = 1.0f, float upZ = 0.0f) {
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
void topView(){
	camera.eye.y = 5;
	camera.eye.x = 0;
	camera.eye.z = 2;
	
}
void leftsideview(){
	camera.eye.y = 1;
	camera.eye.x = -5;
	camera.eye.z = 1;
	
}
void rightsideview(){
	camera.eye.y = 1;
	camera.eye.x = 4;
	camera.eye.z = 1;
}
void frontview(){
	camera.eye.y = 1;
	camera.eye.x = -0.5;
	camera.eye.z = 4;
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
void drawRoom(Vector3f left,Vector3f right, Vector3f front ,Vector3f floor,bool leftwall,bool rightwall){
	glPushMatrix();
	//glTranslated(-0.5, 0, 0.5);
	//glRotated(45, 0, 1, 0);
	//glRotated(-7, 1, 0, 0);
	//floor
	glColor3f(floor.x, floor.y, floor.z);
	drawWall(0.02);

	//left
	if (leftwall){
		glColor3f(left.x, left.y, left.z);
		glPushMatrix();
		glRotated(90, 0, 0, 1.0);
		drawWall(0.02);
		glPopMatrix();
	}

	//glColor3f(0, 0, 0);
	glColor3f(front.x, front.y, front.z);
	glPushMatrix();
	glRotated(-90, 1.0, 0.0, 0.0);
	drawWall(0.02);
	glPopMatrix();

	if (rightwall){
		glColor3f(right.x, right.y, right.z);
		glPushMatrix();
		glTranslated(2, 0, 0);
		glRotated(90, 0, 0, 1.0);
		drawWall(0.02);
		glPopMatrix();
	}
	glPopMatrix();
}

void drawCouch(){
	glPushMatrix();

	//back
	glColor3f(0 + largecouchcolor.x, 0 + largecouchcolor.y, 0 + largecouchcolor.z);
	glPushMatrix();

	glTranslated(0, 0.2, 0.025);
	glScaled(1.2, 0.4, 0.05);
	glutSolidCube(1);
	glPopMatrix();

	//base
	glColor3f(0 + largecouchcolor.x, 0 + largecouchcolor.y, 0 + largecouchcolor.z);
	glPushMatrix();

	glTranslated(0, 0.06, 0.125);
	glScaled(1.1, 0.12, 0.25);
	glutSolidCube(1);
	glPopMatrix();

	//cusions
	glColor3f(0.7 - largecouchcolor.x, 0.4 + largecouchcolor.y, 0 + largecouchcolor.y);
	glPushMatrix();

	glTranslated(-0.275, 0.145, 0.125);
	glScaled(0.55, 0.05, 0.25);
	glutSolidCube(1);
	glPopMatrix();

	glColor3f(0.7 - largecouchcolor.x, 0.42 + largecouchcolor.y, 0 + largecouchcolor.z);
	glPushMatrix();

	glTranslated(0.275, 0.145, 0.125);
	glScaled(0.55, 0.05, 0.25);
	glutSolidCube(1);
	glPopMatrix();

	//rests
	glColor3f(0 + largecouchcolor.x, 0 + largecouchcolor.y, 0 + largecouchcolor.z);
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

	//back
	glColor3f(0+livingchaircolor.x, 0+livingchaircolor.y, 0+livingchaircolor.z);
	glPushMatrix();

	glTranslated(0, 0.2, 0.025);
	glScaled(1.2, 0.4, 0.05);
	glutSolidCube(1);
	glPopMatrix();

	//base
	glColor3f(0 + livingchaircolor.x, 0 + livingchaircolor.y, 0 + livingchaircolor.z);
	glPushMatrix();

	glTranslated(0, 0.06, 0.125);
	glScaled(1.1, 0.12, 0.25);
	glutSolidCube(1);
	glPopMatrix();

	//cusions
	glColor3f(0.7-livingchaircolor.x, 0.4+livingchaircolor.y, 0+livingchaircolor.y);
	glPushMatrix();

	glTranslated(-0.275, 0.145, 0.125);
	glScaled(0.55, 0.05, 0.25);
	glutSolidCube(1);
	glPopMatrix();

	glColor3f(0.7-livingchaircolor.x, 0.42+livingchaircolor.y, 0+livingchaircolor.z);
	glPushMatrix();

	glTranslated(0.275, 0.145, 0.125);
	glScaled(0.55, 0.05, 0.25);
	glutSolidCube(1);
	glPopMatrix();

	//rests
	glColor3f(0 + livingchaircolor.x, 0 + livingchaircolor.y, 0 + livingchaircolor.z);
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

void drawTableLeg(double thick, double len) {
	glPushMatrix();
	glTranslated(0, len / 2, 0);
	glScaled(thick, len, thick);
	glutSolidCube(1.0);
	glPopMatrix();
}
void drawTable(double topWid, double topThick, double legThick, double legLen){
	glPushMatrix();
	glColor3f(1-tablecolor.x, 1-tablecolor.y, 1-tablecolor.z);
	glPushMatrix();
	glTranslated(0, legLen, 0);
	glScaled(topWid, topThick, topWid);
	glutSolidCube(1.0);
	glPopMatrix();

	glColor3f(0+tablecolor.x, 0+tablecolor.y, 0+tablecolor.z);
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

	glPopMatrix();
}
void drawTVTable(){
	glPushMatrix();
	//Sekeleton
	glColor3f(0+tvtablecolor.x, 0+tvtablecolor.y, 0+tvtablecolor.z);
	glPushMatrix();
	glScaled(0.8, 0.3, 0.30);
	glutSolidCube(1);
	glPopMatrix();

	//drawers
	glColor3f(1-tvtablecolor.x, 1-tvtablecolor.y, 1-tvtablecolor.z);
	glPushMatrix();
	glTranslated(-0.20, 0, 0);
	glScaled(0.3, 0.15, 0.31);
	glutSolidCube(1);
	glPopMatrix();

	glColor3f(1-tvtablecolor.x, 1-tvtablecolor.y, 1-tvtablecolor.z);
	glPushMatrix();
	glTranslated(0.20, 0, 0);
	glScaled(0.3, 0.15, 0.31);
	glutSolidCube(1);
	glPopMatrix();

	glPopMatrix();
}

void drawTVStorage(){
	glPushMatrix();

	glColor3f(0+tvstoragecolor.x, 0+tvstoragecolor.y, 0+tvstoragecolor.z);
	glPushMatrix();
	glScaled(0.11, 0.11, 0.05);
	glutSolidCube(1);
	glPopMatrix();

	glColor3f(1-tvstoragecolor.x, 1-tvstoragecolor.y, 1-tvstoragecolor.z);
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
	//antenna
	glPushMatrix();
	glColor3f(1 - tvcolor.x, 1 - tvcolor.y, 1 - tvcolor.z);
	glTranslated(0.16, 0.55, 1.05);
	glRotated(25, 0, 0, 1);
	glScaled(0.01, 0.1, 0.01);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1 - tvcolor.x, 1 - tvcolor.y, 1 - tvcolor.z);
	glTranslated(0.17, 0.52, 1.0);
	glRotated(-25, 0, 0, 1);
	glScaled(0.01, 0.1, 0.01);
	glutSolidCube(1);
	glPopMatrix();
	//base
	glColor3f(0.1+tvcolor.x, 0.1+tvcolor.y, 0.1+tvcolor.z);
	glPushMatrix();
	glTranslated(0.16, 0.4, 1);
	glScaled(0.2, 0.2, 0.2);
	glutSolidCube(1);
	glPopMatrix();
	//screen
	glColor3f(0.4+tvcolor.x, 0.4+tvcolor.y, 0.4+tvcolor.z);
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
	glPushMatrix();
	glTranslated(0, animLivingRoompos, 0);
	drawRoom(left,right,front,floor,true,false);
	//large couch
	glPushMatrix();
	glTranslated(0, LargeCouchanimpos, 0);
	glTranslated(0.9, 0,0);
	drawCouch();
	glPopMatrix();

	//small couch
	glPushMatrix();
	glTranslated(SmallCouchanimpos, 0, 0);
	glTranslated(1.975, 0, 0.8);
	glRotated(-90, 0, 1, 0);
	glScaled(0.55, 1, 1);
	drawChair();
	glPopMatrix();

	//chair
	glPushMatrix();
	glTranslated(0, livingchairanimpos, 0);
	glTranslated(1.975, 0, 1.7);
	glRotated(-90, 0, 1, 0);
	glScaled(0.25, 1, 1);
	drawChair();
	glPopMatrix();

	//table
	glPushMatrix();
	glTranslated(0, tableanimpos ,0);
	glTranslated(1.85, 0.0, 1.325);
	glRotated(90, 0, 1, 0);
	drawTable(0.2, 0.02, 0.02, 0.1);
	glPopMatrix();

	//tvtable
	glPushMatrix();
	glTranslated(tvtableanimpos, 0, 0);
	glTranslated(0.15, 0.15, 1.2);
	glRotated(90, 0, 1, 0);
	drawTVTable();
	glPopMatrix();

	//tvstorage
	glPushMatrix();
	glTranslated(0, 0, TVStorageanimpos);
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
	glPopMatrix();
	//TV
	glPushMatrix();
	glTranslated(0, TVanimpos, 0);
	drawTV();
	glPopMatrix();

	glPopMatrix();
}

void drawBed(){
	glPushMatrix();

	//base
	glColor3f(0.47+bedcolor.x, 0.37+bedcolor.y, 0.30+bedcolor.z);
	glPushMatrix();
	glScaled(0.9, 0.15, 1);
	glutSolidCube(1);
	glPopMatrix();

	//matress
	glColor3f(1-bedcolor.x, 0.9-bedcolor.y, 0.6-bedcolor.z);
	glPushMatrix();
	glTranslated(0, 0.125, 0);
	glScaled(0.8, 0.10, 0.95);
	glutSolidCube(1);
	glPopMatrix();

	//cushion9s
	glColor3f(1-bedcolor.x, 1-bedcolor.y, 1-bedcolor.z);
	glPushMatrix();
	glTranslated(-0.20, 0.19, -0.35);
	glScaled(0.3, 0.05, 0.12);
	glutSolidCube(1);
	glPopMatrix();

	glColor3f(1 - bedcolor.x, 1 - bedcolor.y, 1 - bedcolor.z);
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
	glColor3f(0.47+cupboardcolor.x, 0.37+cupboardcolor.y, 0.30+cupboardcolor.z);
	glPushMatrix();
	glScaled(0.2, 0.9, 0.9);
	glutSolidCube(1);
	glPopMatrix();

	//firstlayer
	glColor3f(1-cupboardcolor.x, 1-cupboardcolor.y, 1-cupboardcolor.z);
	glPushMatrix();
	glTranslated(0.01, 0, 0.3);
	glScaled(0.2, 0.8, 0.25);
	glutSolidCube(1);
	glPopMatrix();

	glColor3f(1 - cupboardcolor.x, 1 - cupboardcolor.y, 1 - cupboardcolor.z);
	glPushMatrix();
	glTranslated(0.01, 0, 0);
	glScaled(0.2, 0.8, 0.25);
	glutSolidCube(1);
	glPopMatrix();

	glColor3f(1 - cupboardcolor.x, 1 - cupboardcolor.y, 1 - cupboardcolor.z);
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
	glColor3f(0.47+comodecolor.x, 0.37+comodecolor.y, 0.30+comodecolor.z);
	glPushMatrix();
	glScaled(0.25, 0.25, 0.25);
	glutSolidCube(1);
	glPopMatrix();

	//drawer
	glPushMatrix();
	glColor3f(1-comodecolor.x, 1-comodecolor.y, 1-comodecolor.z);
	glTranslated(0, 0.095, 0.02);
	glScaled(0.20, 0.05, 0.24);
	glutSolidCube(1);
	glPopMatrix();

	//door
	glPushMatrix();
	glColor3f(1 - comodecolor.x, 1 - comodecolor.y, 1 - comodecolor.z);
	glTranslated(0, -0.0125, 0.02);
	glScaled(0.20, 0.12, 0.24);
	glutSolidCube(1);

	glPopMatrix();

	glPopMatrix();
}

void drawLamp(){
	glPushMatrix();
	
	//base
	glColor3f(1-lampcolor.x, 1-lampcolor.y, 1-lampcolor.z);
	glPushMatrix();
	glScaled(0.025, 0.0125, 0.025);
	glRotated(90, 1, 0, 0);
	glutSolidTorus(1,1,15,15);
	glPopMatrix();

	//stand
	glColor3f(1 - lampcolor.x, 1 - lampcolor.y, 1 - lampcolor.z);
	glPushMatrix();
	glTranslated(0, 0.1, 0);
	glScaled(0.01, 0.2, 0.01);
	glutSolidCube(1);
	glPopMatrix();

	//head
	glColor3f(0.9-lampcolor.x, 0.8-lampcolor.y, 0.9-lampcolor.z);
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
	glColor3f(1, 1, 1);

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
	glColor3f(0.47+deskcolor.x, 0.37+deskcolor.y, 0.30+deskcolor.z);

	glPushMatrix();
	glScaled(0.3, 0.1, 0.4);
	glutSolidCube(1);
	glPopMatrix();

	//bigdrawer
	glColor3f(1-deskcolor.x, 1-deskcolor.y, 1-deskcolor.z);
	glPushMatrix();
	glTranslated(-0.01, 0, -0.07);
	glScaled(0.3, 0.08, 0.25 );
	glutSolidCube(1);
	glPopMatrix();

	//small drawer
	glPushMatrix();
	glColor3f(1 - deskcolor.y, 1 - deskcolor.x, 1 - deskcolor.z);
	glTranslated(-0.01, 0, 0.127);
	glScaled(0.3, 0.08, 0.12);
	glutSolidCube(1);
	glPopMatrix();
	
	//right leg
	glColor3f(0.47 + deskcolor.x, 0.37 + deskcolor.y, 0.30 + deskcolor.z);

	glPushMatrix();
	glTranslated(0, -0.125, 0.122);
	glScaled(0.3, 0.25, 0.15);
	glutSolidCube(1);
	glPopMatrix();

	//small drawer
	glColor3f(1 - deskcolor.y, 1 - deskcolor.z, 1 - deskcolor.x);
	glPushMatrix();
	glTranslated(-0.01, -0.1, 0.127);
	glScaled(0.3, 0.08, 0.12);
	glutSolidCube(1);
	glPopMatrix();

	//small drawer
	glColor3f(1 - deskcolor.z, 1 - deskcolor.x, 1 - deskcolor.z);
	glPushMatrix();
	glTranslated(-0.01, -0.2, 0.127);
	glScaled(0.3, 0.08, 0.12);
	glutSolidCube(1);
	glPopMatrix();

	//leftleg
	glColor3f(0.47 + deskcolor.x, 0.37 + deskcolor.y, 0.30 + deskcolor.z);

     glPushMatrix();
	 glTranslated(0, -0.125, -0.2);
	 glScaled(0.3, 0.25, 0.02);
	glutSolidCube(1);
	glPopMatrix();

	glPopMatrix();

	//


}
void drawBedRoom(){
	Vector3f left = Vector3f(1, 0.9, 0.6);
	Vector3f right = Vector3f(1, 0.9, 0.6);
	Vector3f front = Vector3f(0.54, 0.27, 0.07);
	Vector3f floor = Vector3f(0.7, 0.4, 0.2);
	
	glPushMatrix();
	
		
	glTranslated(-0.81, 0, 0);

	glPushMatrix();
	glTranslated(-2.02, 0, 0);
	drawRoom(left,right,front,floor,false,true);
	glPopMatrix();
	//bed
	glPushMatrix();
	glTranslated(0, bedanimpos, 0);
	glTranslated(-0.5, 0.075, 0.5);
	drawBed();
	glPopMatrix();
	
	//cardboard
	glPushMatrix();
	glTranslated( cupboardanimpos,0, 0);
	glTranslated(-1.92, 0.45, 0.55);
	drawCupBoard();
	glPopMatrix();
	
	//draw chair
	glPushMatrix();
	glTranslated(0, deskanimpos, 0);
	glTranslated(-0.4, 0.025, 1.4);
	glRotated(90, 0, 1, 0);
	drawChairBedRoom();
	glPopMatrix();

	

	//comode
	glPushMatrix();
	glTranslated(0, 0, comodeanimpos);
	glTranslated(-1.1, 0.125, 0.125);
	drawComode();
	glPopMatrix();
	
	//drawLamp
	glPushMatrix();
	glTranslated(0, lampanimpos, 0);
	glTranslated(-1.1, 0.25, 0.125);
	drawLamp();
	glPopMatrix();


	//desk
	glPushMatrix();
	glTranslated(0, deskanimpos, 0);
	glTranslated(-0.18, 0.27, 1.5);
	//glTranslated(-1, 1, 1);
	drawDesk();
	glPopMatrix();
	glPopMatrix();

	
}

void drawGhost(){
	glPushMatrix();
	//body
	glColor3f(1, 1, 1);
	glPushMatrix();
	glutSolidSphere(0.15, 15, 15);
	glPopMatrix();

	//head 
	glColor3f(1, 1, 1);
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

	//righteye
	glColor3f(0, 0, 0);
	glPushMatrix();
	glTranslated(0.02, 0.22, 0.052);
	glutSolidSphere(0.01,15,15);
	glPopMatrix();

	//lefteye
	glColor3f(0, 0, 0);
	glPushMatrix();
	glTranslated(-0.02, 0.22, 0.052);
	glutSolidSphere(0.01, 15, 15);
	glPopMatrix();

	glPopMatrix();
}

void Display(){
	setupLights();
	setupCamera();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawLivingRoom();
	
	glPushMatrix();
	glTranslated(-2.83, 0.01, 0);
	glRotated(animBedRoomRot, 0,  1,0);
	glTranslated(2.83, -0.01, 0);
	drawBedRoom();
	glPopMatrix();

	if (showGhost){
		glPushMatrix();
		glTranslated(ghostPosX, ghostanimpos, ghostPosZ);
		glRotated(animghostRot, 0, 1, 0);
		drawGhost();
		glPopMatrix();	
	}
	
	glFlush();

}
void resetColor(){
	//living room chaning colors

	//TV
	tvcolor = Vector3f(0, 0, 0);
	//Tvstorge
	tvstoragecolor = Vector3f(0, 0, 0);
	//tvtable
	tvtablecolor = Vector3f(0, 0, 0);
	//large couch
	largecouchcolor = Vector3f(0, 0, 0);
	//small couch
	smallcouchcolor = Vector3f(0, 0, 0);
	//livingchair
	livingchaircolor = Vector3f(0, 0, 0);
	//table
	tablecolor = Vector3f(0, 0, 0);
	//___________________________//
	//bed room changing colors
	//cupboard
	cupboardcolor = Vector3f(0, 0, 0);
	//bed
	bedcolor = Vector3f(0, 0, 0);
	//comode
	comodecolor = Vector3f(0, 0, 0);
	//lamp
	lampcolor = Vector3f(0, 0, 0);
	//desk
	deskcolor = Vector3f(0, 0, 0);
}
void resetLivingroomPostions(){
	//___________________________//
	//living room animation values

	animLivingRoompos = 0;
	//large couch
	LargeCouchanimpos = 0;

	//small couch
	SmallCouchanimpos = 0;

	//chair
	livingchairanimpos = 0;

	//table
	tableanimpos = 0;

	//tv table
	tvtableanimpos = 0;

	//Tv
	TVanimpos = 0;

	//TVStorage
	TVStorageanimpos = 0;

}
void resetBedroomPositions(){

	//__________________________//
	//bedroom animation values
	
	 animBedRoomRot = 0;
	
	//desk
	 deskanimpos = 0;
	
	//bed
	 bedanimpos = 0;
	
	//lamp
	 lampanimpos = 0;
	
	//comode
	 comodeanimpos = 0;
	
	//cupboard
	 cupboardanimpos = 0;
	

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
	case 'l':
		animateBedRoom = animateBedRoom ? false : true;
		if (!animateBedRoom)
			resetBedroomPositions();
		break;
	case 'r':
		animateLivingRoom = animateLivingRoom ? false : true;
		if (!animateLivingRoom)
			resetLivingroomPostions();
		break;
	case 'c':
		changeColor = true;
		break;
	case 'v':
		changeColor = false; resetColor();
		break;
	case 't':
		topView();
		break;
	case 'o':
		leftsideview();
		break;
	case 'p':
		rightsideview();
		break;
	case'f':
		frontview();
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

void animateDesk(){
	if (deskanimpos <= 0)
		deskanimval = 0.01;
	else if (deskanimpos >= maxheight)
		deskanimval =-0.01;
	deskanimpos += deskanimval;
}

void animateBed(){
	if (bedanimpos <= 0)
		bedanimval = 0.001;
	else if (bedanimpos >= maxheight)
		bedanimval = -0.001;
	bedanimpos += bedanimval;
}
void animateLamp(){
	if (lampanimpos <= 0)
		lampanimval = 0.07;
	else if (lampanimpos >= maxheight)
		lampanimval = -0.07;
	lampanimpos += lampanimval;
}
void animatecomode(){
	if (comodeanimpos <= 0)
		comodeanimval = 0.007;
	else if (comodeanimpos >= maxheight)
		comodeanimval = -0.005;
	comodeanimpos += comodeanimval;
}
void animateCupBoard(){
	if (cupboardanimpos <= 0)
		cupboardanimval = 0.0007;
	else if (cupboardanimpos >= maxheight-0.5)
		cupboardanimval = -0.0005;
	cupboardanimpos += cupboardanimval;
}
void animateBedRoomfunc(){
	if (animateBedRoom){
		//animate room
		if (animBedRoomRot >= 45)
			animBedRoomVal = -0.05;
		else
			if (animBedRoomRot <= -45)
				animBedRoomVal = 0.05;
		animBedRoomRot += animBedRoomVal;
        //animate desk
		animateDesk();
		//bed
		animateBed();
		//lamp
		animateLamp();
		//comode
		animatecomode();
		//cupboard
		animateCupBoard();
	}
}
void animateLargeCouch(){
	if (LargeCouchanimpos <= 0)
		LargeCouchanimval = 0.0007;
	else if (LargeCouchanimpos >= maxheight - 0.5)
		LargeCouchanimval = -0.0005;
	LargeCouchanimpos += LargeCouchanimval;
}
void animateSmallCouch(){
		if (SmallCouchanimpos >= 0)
		SmallCouchanimval = -0.0007;
	else if (SmallCouchanimpos <= - 0.5)
		SmallCouchanimval = 0.0005;
	SmallCouchanimpos += SmallCouchanimval;
}
void animateLivingChair(){
	if (livingchairanimpos <= 0)
		livingchairanimval = 0.007;
	else if (livingchairanimpos >= maxheight)
		livingchairanimval = -0.007;
	livingchairanimpos += livingchairanimval;
}
void animateLivingTable(){
	if (tableanimpos <= 0)
		tableanimval = 0.001;
	else if (tableanimpos >= maxheight)
		tableanimval = -0.0005;
	tableanimpos += tableanimval;
}

void animateTV(){
	if (TVanimpos <= 0)
		TVanimval = 0.07;
	else if (TVanimpos >= maxheight)
		TVanimval = -0.07;
	TVanimpos += TVanimval;
}
void animateTVStorage(){
	if (TVStorageanimpos <= 0)
		TVStorageanimval = 0.007;
	else if (TVStorageanimpos >= maxheight-0.5)
		TVStorageanimval = -0.007;
	TVStorageanimpos += TVStorageanimval;
}

void animateTVTable(){
	if (tvtableanimpos <= 0)
		tvtableanimval = 0.007;
	else if (tvtableanimpos >= maxheight-0.2)
		tvtableanimval = -0.007;
	tvtableanimpos += tvtableanimval;
}
void animateLivingRoomFunc(){
	if (animateLivingRoom){
		if (animLivingRoompos >= 0)
			animLivingRoomval = -0.001;
		else if (animLivingRoompos <= -maxheight)
			animLivingRoomval= 0.001;
		animLivingRoompos += animLivingRoomval;

		animateLargeCouch();

		animateSmallCouch();

		animateLivingChair();

		animateLivingTable();

		animateTV();

		animateTVStorage();

		animateTVTable();

	}
}
void animateGhost(){
	//1 translation
	if (ghostanimno){
		if (ghostanimpos <= 0)
			ghostanimval = 0.005;
		else if (ghostanimpos >= maxheight-0.5)
			ghostanimval = -0.005;
		ghostanimpos += ghostanimval;
	}
	//0 rotation
	else{
		if (animghostRot >= 45)
			animghostVal = -0.5;
		else
			if (animghostRot <= -45)
				animghostVal = 0.5;
		animghostRot += animghostVal;
	}
}
void changeTvColor(){
	tvcolor.x += 0.1*redD;							
	if (tvcolor.x <0 || tvcolor.x>1)					
		redD *= -1;								
	tvcolor.y += 0.1*greenD;						
	if (tvcolor.y<0 || tvcolor.y>0.5)						
		greenD *= -1;								
	tvcolor.z += 0.1*blueD;						
	if (tvcolor.z<0.5 || tvcolor.z>0.75)				
		blueD *= -1;
}
void changeTableColor(){
	tablecolor.x += 0.1*redD;
	if (tablecolor.x <0 || tablecolor.x>1)
		redD *= -1;
	tablecolor.y += 0.1*greenD;
	if (tablecolor.y<0 || tablecolor.y>0.5)
		greenD *= -1;
	tablecolor.z += 0.1*blueD;
	if (tablecolor.z<0.5 || tablecolor.z>0.75)
		blueD *= -1;
}
void changeTVTableColor(){
	tvtablecolor.x += 0.2*redD;
	if (tvtablecolor.x <0 || tvtablecolor.x>1)
		redD *= -1;
	tvtablecolor.y += 0.1*greenD;
	if (tvtablecolor.y<0 || tvtablecolor.y>0.5)
		greenD *= -1;
	tvtablecolor.z += 0.1*blueD;
	if (tvtablecolor.z<0.5 || tvtablecolor.z>0.75)
		blueD *= -1;
}
void changeTVStorageColor(){
	tvstoragecolor.x += 0.1*redD;
	if (tvstoragecolor.x <0 || tvstoragecolor.x>1)
		redD *= -1;
	tvstoragecolor.y += 0.15*greenD;
	if (tvstoragecolor.y<0 || tvstoragecolor.y>0.5)
		greenD *= -1;
	tvstoragecolor.z += 0.1*blueD;
	if (tvstoragecolor.z<0.5 || tvstoragecolor.z>0.75)
		blueD *= -1;
}
void changeLargeCouchColor(){
	largecouchcolor.x += 0.1*redD;
	if (largecouchcolor.x <0 || largecouchcolor.x>1)
		redD *= -1;
	largecouchcolor.y += 0.15*greenD;
	if (largecouchcolor.y<0 || largecouchcolor.y>0.5)
		greenD *= -1;
	largecouchcolor.z += 0.15*blueD;
	if (largecouchcolor.z<0.5 || largecouchcolor.z>0.75)
		blueD *= -1;
}
void changeLivingChairColor(){
	livingchaircolor.x += 0.15*redD;
	if (tvstoragecolor.x <0 || tvstoragecolor.x>1)
		redD *= -1;
	tvstoragecolor.y += 0.1*greenD;
	if (tvstoragecolor.y<0 || tvstoragecolor.y>0.5)
		greenD *= -1;
	tvstoragecolor.z += 0.1*blueD;
	if (tvstoragecolor.z<0.5 || tvstoragecolor.z>0.75)
		blueD *= -1;
}
void changeCupboardColor(){
	cupboardcolor.x += 0.15*redD;
	if (cupboardcolor.x <0 || cupboardcolor.x>1)
		redD *= -1;
	cupboardcolor.y += 0.15*greenD;
	if (cupboardcolor.y<0 || cupboardcolor.y>0.5)
		greenD *= -1;
	cupboardcolor.z += 0.1*blueD;
	if (cupboardcolor.z<0.5 || cupboardcolor.z>0.75)
		blueD *= -1;
}
void changeBedColor(){
	bedcolor.x += 0.1*redD;
	if (bedcolor.x <0 || bedcolor.x>1)
		redD *= -1;
	bedcolor.y += 0.1*greenD;
	if (bedcolor.y<0 || bedcolor.y>0.5)
		greenD *= -1;
	bedcolor.z += 0.1*blueD;
	if (bedcolor.z<0.5 || bedcolor.z>0.75)
		blueD *= -1;
}
void changeComodeColor(){
	comodecolor.x += 0.15*redD;
	if (comodecolor.x <0 || comodecolor.x>1)
		redD *= -1;
	comodecolor.y += 0.15*greenD;
	if (comodecolor.y<0 || comodecolor.y>0.5)
		greenD *= -1;
	comodecolor.z += 0.15*blueD;
	if (comodecolor.z<0.5 || comodecolor.z>0.75)
		blueD *= -1;
}
void changeLampColor(){
	lampcolor.x += 0.2*redD;
	if (lampcolor.x <0 || lampcolor.x>1)
		redD *= -1;
	lampcolor.y += 0.1*greenD;
	if (lampcolor.y<0 || lampcolor.y>0.5)
		greenD *= -1;
	lampcolor.z += 0.15*blueD;
	if (lampcolor.z<0.5 || lampcolor.z>0.75)
		blueD *= -1;
}
void changeDeskColor(){
	deskcolor.x += 0.1*redD;
	if (deskcolor.x <0 || deskcolor.x>1)
		redD *= -1;
	deskcolor.y += 0.15*greenD;
	if (deskcolor.y<0 || deskcolor.y>0.5)
		greenD *= -1;
	deskcolor.z += 0.2*blueD;
	if (deskcolor.z<0.5 || deskcolor.z>0.75)
		blueD *= -1;
}
void time(int val){
	if (changeColor){
	//living room
		//TV
		changeTvColor();
		//table
		changeTableColor();
		//tv table
		changeTVTableColor();
		//tvstorage
		changeTVStorageColor();
		//largecouch
		changeLargeCouchColor();
		//smallcouch+chair
		changeLivingChairColor();
	//bedroom
		//bed
		changeBedColor();
		//cupboard
		changeCupboardColor();
		//comode
		changeComodeColor();
		//lamp
		changeLampColor();
		//desk
		changeDeskColor();
	}

	glutPostRedisplay();								
	glutTimerFunc(1000, time, 0);
}
void ghostShow(int val){
	if (showGhost){
		ghostShowDuration--;
		if (ghostShowDuration <= 0){
			showGhost = false;
			ghostHideDuration = 4;
			animghostRot = 0;
			animghostVal = 0.5;
		}
	}
	glutPostRedisplay();								
	glutTimerFunc(1000, ghostShow, 0);
}
void ghostHide(int val){
	if (!showGhost){
		ghostHideDuration--;
		if (ghostHideDuration <= 0){
			ghostShowDuration = 3;
			ghostanimno = rand() % 2;;
			ghostPosX = -2.5 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 4));
			ghostanimpos = 0.5;
			ghostPosZ = 0+ static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 2));
			
			showGhost = true;
		}
	}
	glutPostRedisplay();							
	glutTimerFunc(1000, ghostHide, 0);
}

void Anim(){
	animateLivingRoomFunc();
	animateBedRoomfunc();
	if (showGhost){
		animateGhost();
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
	glutIdleFunc(Anim);
	glutTimerFunc(0, time, 0);
	glutTimerFunc(0, ghostShow, 0);
	glutTimerFunc(0, ghostHide, 0);
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
