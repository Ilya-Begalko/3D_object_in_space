#include <stdlib.h>
#include <math.h>
#include <glut.h>

// ���� �������� ������
float angle = 0.0;
// ���������� ������� ����������� �������� ������
float lx = 0.0f, lz = -1.0f;
// XZ ������� ������
float x = 0.0f, z = 5.0f;

void print(char* text, float x, float y, float z) {
	char* c;
	glRasterPos2f(x, y);
	for (c = text; *c != '\0'; c++)glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c);
}

//��� ��������� ������� ���� ������� ���������� �����������
void changeSize(int w, int h) {
	// �������������� ������� �� ����
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;
	// ���������� ������� ��������
	glMatrixMode(GL_PROJECTION);
	// �������� �������
	glLoadIdentity();
	// ���������� ��������� ��������
	glViewport(0, 0, w, h);
	// ���������� ���������� �����������
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);
	// ��������� � ������� ��������
	glMatrixMode(GL_MODELVIEW);
}

void drawSnowMan()
{

	glColor3f(1.0f, 1.0f, 1.0f);
	// ���� ���������
	glTranslatef(0.0f, 0.75f, 0.0f);
	glutSolidSphere(0.75f, 20, 20);
	// ������ ���������
	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.25f, 20, 20);
	// ����� ���������
	glPushMatrix(); // ��������� ���������� ������� ������� ��� ����������� �������������
	glColor3f(0.0f, 0.0f, 0.0f);
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.05f, 10, 10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f, 10, 10);
	glPopMatrix();
	// ��� ���������
	glColor3f(1.0f, 0.5f, 0.5f);
	glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
	glutSolidCone(0.10f, 0.5f, 10, 2);
}


void renderScene(void) {
	char c[18] = "Happy Christmas!!";
	//�������� ����� ����� � �������
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// �������� �������������
	glLoadIdentity();
	// ���������� ������
	gluLookAt(x, 1.0f, z, x + lx, 1.0f, z + lz, 0.0f, 1.0f, 0.0f);
	// �������� "�����"
	glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_QUADS);
	glVertex3f(-100.0f, 0.0f, -100.0f);
	glVertex3f(-100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, -100.0f);
	glEnd();
	drawSnowMan();
	print(c, 0.25, 1.0, 1.0);
	glutSwapBuffers();//������� 2 ������� , � ���� �� ����� �� ��������� ��������� ���� �� ��� , ������ �������� ��������� �� ������ , � �� ���������� ��������� ������ �� ������
}

void processNormalKeys(unsigned char key, int x, int y) {
	if (key == 27)
		exit(0);
}

void processSpecialKeys(int key, int xx, int yy)
{
	float fraction = 0.2f;
	switch (key) {
	case GLUT_KEY_LEFT:
		angle -= 0.01f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	case GLUT_KEY_RIGHT:
		angle += 0.01f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	case GLUT_KEY_UP:
		x += lx * fraction;
		z += lz * fraction;
		break;
	case GLUT_KEY_DOWN:
		x -= lx * fraction;
		z -= lz * fraction;
		break;
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(750, 750);
	glutCreateWindow("lab#5");
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	glDisable(GL_DEPTH_TEST);
}