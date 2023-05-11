#include <windows.h>
#include <math.h>
#include <GL/glut.h>

static double tswim = 0;
static double tfly = 0;

static double move_x;
static double move_y;
static double move_z;

static double rotate_x;
static double rotate_y;
static double rotate_z;

static double L_foot_y;
static double R_foot_y;

static bool fly = false;
static bool dive = false;

static char key;

GLfloat L_Wing_x = 0;
GLfloat R_Wing_x = 0;
GLfloat L_Leg_x = 0;
GLfloat L_Foot_y = 0;
GLfloat R_Leg_x = 0;
GLfloat R_Foot_y = 0;

GLUquadricObj* sh1;

static int flag = 0;

void glInit() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	GLfloat ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat position[] = { 400.0, 300.0, -700.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMateriali(GL_FRONT, GL_SHININESS, 128);

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-20.0, 20.0, -20.0, 20.0, -20.0, 20.0);
}

void Chanege_Wire_Or_Solid(int i) {
	if (flag == 1)
		gluQuadricDrawStyle(sh1, GLU_LINE);
}

//*/*/*/*그리기 작업*/*/*/*/

void Draw_Poly(double x, double y, double z) {
	glBegin(GL_QUADS);

	glVertex3f(-x, y, z);
	glVertex3f(-x, -y, z);
	glVertex3f(x, -y, z);
	glVertex3f(x, y, z);

	glVertex3f(x, y, z);
	glVertex3f(x, -y, z);
	glVertex3f(x, -y, -z);
	glVertex3f(x, y, -z);

	glVertex3f(x, y, -z);
	glVertex3f(x, -y, -z);
	glVertex3f(-x, -y, -z);
	glVertex3f(-x, y, -z);

	glVertex3f(-x, y, -z);
	glVertex3f(-x, -y, -z);
	glVertex3f(-x, -y, z);
	glVertex3f(-x, y, z);

	glVertex3f(-x, y, z);
	glVertex3f(x, y, z);
	glVertex3f(x, y, -z);
	glVertex3f(-x, y, -z);

	glVertex3f(x, -y, z);
	glVertex3f(-x, -y, z);
	glVertex3f(-x, -y, -z);
	glVertex3f(x, -y, -z);
	glEnd();
}

void DrawL_Wing(int x, int a, int b, int c) {
	glPushMatrix();
	glColor3f(1, 1, 0);
	sh1 = gluNewQuadric();
	glRotatef(x, a, b, c);
	if (fly) {
		glTranslatef(0.3, 0.1, 0.1);
	}
	else {
		glRotatef(-75.0, 1.0, 0.0, 0.0);
		glRotatef(-15.0, 0.0, 1.0, 0.0);
		glRotatef(90, 0.0, 0.0, 1.0);
		glTranslatef(-0.2, -0.17, 0.0);
	}

	Chanege_Wire_Or_Solid(flag);
	Draw_Poly(0.2, 0.01, 0.1);
	glPopMatrix();
}

void DrawR_Wing(int x, int a, int b, int c) {
	glPushMatrix();
	glColor3f(1, 1, 0);
	sh1 = gluNewQuadric();
	glRotatef(x, a, b, c);
	if (fly) {
		glTranslatef(-0.3, 0.1, 0.1);
	}
	else {
		glRotatef(-75.0, 1.0, 0.0, 0.0);
		glRotatef(15.0, 0.0, 1.0, 0.0);
		glRotatef(90, 0.0, 0.0, 1.0);
		glTranslatef(-0.2, 0.17, 0.0);
	}

	Chanege_Wire_Or_Solid(flag);
	Draw_Poly(0.2, 0.01, 0.1);
	glPopMatrix();
}

void DrawBody(int x, int a, int b, int c) {
	glPushMatrix();
	glColor3f(0, 0, 1);
	sh1 = gluNewQuadric();

	glRotatef(x, a, b, c);
	Chanege_Wire_Or_Solid(flag);
	gluCylinder(sh1, 0.15, 0.15, 0.5, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 1);
	glRotatef(180, 0, 0, 1);
	glTranslatef(0.0, 0.0, 0.0);
	glutSolidCone(0.15, 0.25, 15, 15);
	glPopMatrix();
}

void DrawTail() {
	glPushMatrix();
	glColor3f(0, 1, 0);
	glTranslatef(0.0, 0.0, 0.5);
	glutSolidCone(0.15, 0.25, 15, 15);
	glPopMatrix();
}

void DrawL_Legs(int x, int a, int b, int c) {
	glPushMatrix();
	glColor3f(1, 1, 0);
	sh1 = gluNewQuadric();
	glRotatef(x, a, b, c);
	if (dive) {
		glTranslatef(0.05, -0.15, 0.25);
	}
	else {
		glRotatef(90.0, 1.0, 0.0, 0.0);
		glTranslatef(0.05, 0.25, 0.07);
	}

	Chanege_Wire_Or_Solid(flag);
	gluCylinder(sh1, 0.02, 0.02, 0.2, 15, 15);
	glPopMatrix();
}

void DrawL_foot(int y, int a, int b, int c) {
	glPushMatrix();
	glColor3f(0, 0, 0);
	Chanege_Wire_Or_Solid(flag);
	if (dive) {
		glTranslatef(0.05, -0.23, 0.45);
		glRotatef(90, 1, 0, 0);
		glRotatef(y, a, b, c);
	}
	else {
		glTranslatef(0.05, -0.26, 0.18);
		glRotatef(y, a, b, c);
	}
	Draw_Poly(0.05, 0.01, 0.1);
	glPopMatrix();
}

void DrawR_Legs(int x, int a, int b, int c) {
	glPushMatrix();
	glColor3f(1, 1, 0);
	sh1 = gluNewQuadric();
	glRotatef(x, a, b, c);
	if (dive) {
		glTranslatef(-0.05, -0.15, 0.25);
	}
	else {
		glRotatef(90.0, 1.0, 0.0, 0.0);
		glTranslatef(-0.05, 0.25, 0.07);
	}
	Chanege_Wire_Or_Solid(flag);
	gluCylinder(sh1, 0.02, 0.02, 0.2, 15, 15);
	glPopMatrix();
}

void DrawR_foot(int y, int a, int b, int c) {
	glPushMatrix();
	glColor3f(0, 0, 0);
	Chanege_Wire_Or_Solid(flag);
	if (dive) {
		glTranslatef(-0.05, -0.23, 0.45);
		glRotatef(90, 1, 0, 0);
		glRotatef(y, a, b, c);
	}
	else {
		glTranslatef(-0.05, -0.26, 0.18);
		glRotatef(y, a, b, c);
	}
	Draw_Poly(0.05, 0.01, 0.1);
	glPopMatrix();
}

void DrawNeck() {
	glPushMatrix();
	glColor3f(0, 0, 0);
	sh1 = gluNewQuadric();
	if (dive) {
		glRotatef(30.0, 1.0, 0.0, 0.0);
		glTranslatef(0.0, 0.1, -0.2);
	}
	else {
		glRotatef(70.0, 1.0, 0.0, 0.0);
		glTranslatef(0.0, 0.1, -0.3);
	}
	Chanege_Wire_Or_Solid(flag);
	gluCylinder(sh1, 0.05, 0.05, 0.2, 15, 15);
	glPopMatrix();
}

void DrawHead() {
	glPushMatrix();

	sh1 = gluNewQuadric();
	Chanege_Wire_Or_Solid(flag);
	if (dive) {
		glTranslatef(0.0, 0.2, -0.2);
	}
	else {
		glTranslatef(0.0, 0.35, -0.05);
	}
	glColor3f(1, 0, 0);
	gluSphere(sh1, 0.15, 30, 10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	if (dive) {
		glTranslatef(-0.1, 0.25, -0.3);
	}
	else {
		glTranslatef(-0.1, 0.4, -0.15);
	}
	gluSphere(sh1, 0.01, 30, 10);
	glPopMatrix();

	glPushMatrix();
	if (dive) {
		glTranslatef(0.1, 0.25, -0.3);
	}
	else {
		glTranslatef(0.1, 0.4, -0.15);
	}
	gluSphere(sh1, 0.01, 30, 10);
	glPopMatrix();

	glPushMatrix();
	if (dive) {
		glRotatef(-10, 1, 0, 0);
		glTranslatef(0.0, 0.2, -0.3);
	}
	else {
		glRotatef(-10, 1, 0, 0);
		glTranslatef(0.0, 0.35, -0.15);
	}
	glColor3f(1, 1, 0);
	Draw_Poly(0.05, 0.01, 0.1);
	glPopMatrix();

	glPushMatrix();
	if (dive) {
		glRotatef(-10, 1, 0, 0);
		glTranslatef(0.0, 0.19, -0.3);
	}
	else {
		glRotatef(-10, 1, 0, 0);
		glTranslatef(0.0, 0.34, -0.15);
	}
	Draw_Poly(0.05, 0.01, 0.1);
	glPopMatrix();
}

void DrawDuck() {
	glPushMatrix();

	glRotatef(rotate_x, 1, 0, 0);
	glRotatef(rotate_y, 0, 1, 0);
	glRotatef(rotate_z, 0, 0, 1);

	DrawBody(0, 0, 0, 0);
	DrawTail();
	DrawHead();
	DrawNeck();
	DrawR_Wing(R_Wing_x, 0, 0, 1);
	DrawL_Wing(L_Wing_x, 0, 0, 1);
	DrawL_Legs(L_Leg_x, 1, 0, 0);
	DrawL_foot(L_Foot_y, 1, 0, 0);
	DrawR_Legs(R_Leg_x, 1, 0, 0);
	DrawR_foot(R_Foot_y, 1, 0, 0);
	glPopMatrix();
}

void DrawGround() {			// 지면 그리기
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glTranslatef(0.0, -0.15 - move_y, 0.0);
	glColor3f(0.0, 0.0, 1.0);
	Draw_Poly(1.0, 0.01, 1.0);
	glPopMatrix();
	DrawDuck();
}

void Swim(unsigned char key) {								// Swim
	fly = false;
	dive = false;
	glLoadIdentity();
	L_Foot_y = 0;
	R_Foot_y = 0;

	if (key == 'n') {
		move_y += 0.01;
		return;
	}
	else if (key == 'm') {
		move_y -= 0.01;
		return;
	}
	else if (key == 'w') {
		L_Foot_y = sin(tswim) * 40;
		R_Foot_y = -L_Foot_y;
		L_foot_y = sin(tswim) * 0.05;
		R_foot_y = -L_foot_y;
	}
	else if (key == 'a') {
		R_Foot_y = sin(tswim) * 40;
		R_foot_y = sin(tswim) * 0.05;
		rotate_y -= 2;
	}
	else if (key == 'd') {
		L_Foot_y = sin(tswim) * 40;
		L_foot_y = sin(tswim) * 0.05;
		rotate_y += 2;
	}
	DrawGround();
	glutSwapBuffers();
}

void Fly(unsigned char key) {
	fly = true;
	dive = true;
	L_Wing_x = 0;
	R_Wing_x = 0;

	if (key == 'j') {
		L_Wing_x = sin(tfly) * 30;
		R_Wing_x = -L_Wing_x;
		move_y += 0.01;
	}
	else if (key == 'k') {
		if (rotate_z > 0)
			rotate_z--;
		else if (rotate_z < 0)
			rotate_z++;
		move_y -= 0.01;
		if (move_y <= 0) {
			rotate_z = 0;
			L_Wing_x = R_Wing_x = 0;
			move_y = 0;
		}
	}
	else if (key == 'w') {
		L_Wing_x = sin(tfly) * 30;
		R_Wing_x = -L_Wing_x;
		if (rotate_z > 0)
			rotate_z--;
		if (rotate_z < 0)
			rotate_z++;
	}
	else if (key == 'a') {
		if (rotate_z > -15)
			rotate_z--;
		rotate_y -= 2;
	}
	else if (key == 'd') {
		if (rotate_z < 15)
			rotate_z++;
		rotate_y += 2;
	}
	DrawGround();
	glutSwapBuffers();
}

void Dive(unsigned char key) {
	dive = true;
	L_Foot_y = 0;
	R_Foot_y = 0;
	if (key == 'j') {
		L_Foot_y = sin(tswim) * 40;
		R_Foot_y = -L_Foot_y;
		L_foot_y = sin(tswim) * 0.05;
		R_foot_y = -L_foot_y;
		move_y += 0.01;
		if (move_y >= 0) {
			move_y = 0;
		}
	}
	else if (key == 'k') {
		L_Foot_y = sin(tswim) * 40;
		R_Foot_y = -L_Foot_y;
		L_foot_y = sin(tswim) * 0.05;
		R_foot_y = -L_foot_y;
		move_y -= 0.01;
	}
	else if (key == 'w') {
		L_Foot_y = sin(tswim) * 40;
		R_Foot_y = -L_Foot_y;
		L_foot_y = sin(tswim) * 0.05;
		R_foot_y = -L_foot_y;
	}
	else if (key == 'a') {
		R_Foot_y = sin(tswim) * 40;
		R_foot_y = sin(tswim) * 0.05;
		rotate_y -= 2;
	}
	else if (key == 'd') {
		L_Foot_y = sin(tswim) * 40;
		L_foot_y = sin(tswim) * 0.05;
		rotate_y += 2;
	}
	DrawGround();
	glutSwapBuffers();
}

void MyDisplay() {
	if (move_y == 0) {
		Swim(key);
	}
	else if (move_y > 0) {
		Fly(key);
	}
	else if (move_y < 0) {
		Dive(key);
	}
	key = NULL;
}

void MyKeyboard(unsigned char KeyPressed, int x, int y) {
	key = KeyPressed;
}

void MyTimer(int Value) {
	tswim += 0.5;
	tfly += 6;

	glutPostRedisplay();
	glutTimerFunc(40, MyTimer, 1);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Moving Duck!");
	glInit();
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glutKeyboardFunc(MyKeyboard);
	glutTimerFunc(40, MyTimer, 1);
	glutDisplayFunc(MyDisplay);
	glutMainLoop();
	return 0;
}