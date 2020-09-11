#include <stdlib.h>
#include <math.h>
#include <glut.h>

// угол поворота камеры
float angle = 0.0;
// координаты вектора направления движения камеры
float lx = 0.0f, lz = -1.0f;
// XZ позиция камеры
float x = 0.0f, z = 5.0f;

void print(char* text, float x, float y, float z) {
	char* c;
	glRasterPos2f(x, y);
	for (c = text; *c != '\0'; c++)glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c);
}

//при изменении размера окна находит приемлимую перспективу
void changeSize(int w, int h) {
	// предотвращение деления на ноль
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;
	// используем матрицу проекции
	glMatrixMode(GL_PROJECTION);
	// обнуляем матрицу
	glLoadIdentity();
	// установить параметры вьюпорта
	glViewport(0, 0, w, h);
	// установить корректную перспективу
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);
	// вернуться к матрице проекции
	glMatrixMode(GL_MODELVIEW);
}

void drawSnowMan()
{

	glColor3f(1.0f, 1.0f, 1.0f);
	// тело снеговика
	glTranslatef(0.0f, 0.75f, 0.0f);
	glutSolidSphere(0.75f, 20, 20);
	// голова снеговика
	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.25f, 20, 20);
	// глаза снеговика
	glPushMatrix(); // сохранить содержимое текущей матрицы для дальнейшего использования
	glColor3f(0.0f, 0.0f, 0.0f);
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.05f, 10, 10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f, 10, 10);
	glPopMatrix();
	// нос снеговика
	glColor3f(1.0f, 0.5f, 0.5f);
	glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
	glutSolidCone(0.10f, 0.5f, 10, 2);
}


void renderScene(void) {
	char c[18] = "Happy Christmas!!";
	//очистить буфер цвета и глубины
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// обнулить трансформацию
	glLoadIdentity();
	// установить камеру
	gluLookAt(x, 1.0f, z, x + lx, 1.0f, z + lz, 0.0f, 1.0f, 0.0f);
	// нарисуем "землю"
	glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_QUADS);
	glVertex3f(-100.0f, 0.0f, -100.0f);
	glVertex3f(-100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, -100.0f);
	glEnd();
	drawSnowMan();
	print(c, 0.25, 1.0, 1.0);
	glutSwapBuffers();//Имеется 2 буффера , и пока на экран не выводится полностью один из них , второй остается полностью за кадром , и не произойдет наложения одного на другой
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