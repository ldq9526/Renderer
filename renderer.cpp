#include <GL/glut.h>

GLint angle = 0;
/* light parameters */
GLfloat light_ambient[] = { 0.5f,0.5f,0.5f,1.f };
GLfloat light_diffuse[] = { 1.f,1.f,1.f,1.f };
GLfloat light_specular[] = { 1.f,1.f,1.f,1.f };
GLfloat light_position[] = { 1.f,1.f,1.f,0.f };
/* material parameters */
GLfloat material_ambient[] = { 0.5f,0.5f,0.5f,1.f };
GLfloat material_diffuse[] = { 0.5f,0.5f,0.5f,1.f };
GLfloat material_specular[] = { 0.2f,0.2f,0.2f,1.f };

void initialize()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_POLYGON_SMOOTH);
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLdouble)w / h, 1.0, 20.0);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.f, 1.f, 0.f);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, -1.0, 1.0, -1.0);
	glRotatef((GLfloat)angle, 0.f, 1.f, 0.f);
	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 1.f);
	glutSolidTeapot(3);
	glPopMatrix();
	glutSwapBuffers();
}

void keyboard(unsigned char key,int x,int y)
{
	if (key == 't')
	{
		angle = (angle + 5) % 360;
		glutPostRedisplay();
	}
	else if (key == 'T')
	{
		angle = (angle - 5) % 360;
		glutPostRedisplay();
	}
	else if (key == 'r' || key == 'R')
	{
		angle = 0;
		glutPostRedisplay();
	}
}

int main(int argc,char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 480);
	glutCreateWindow("OpenGL");
	initialize();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}