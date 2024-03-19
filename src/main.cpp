#include <iostream>
#include <fstream>
#include <GL/glut.h>
#include <map>
#include <set>
#include "../inc/TriangleMesh.hpp"
#include "../inc/Bone.hpp"

GLdouble bodyWidth = 1.0;

GLfloat angle = -150;   /* in degrees */
GLfloat xloc = 0, yloc = 0, zloc = 0;
static int moving = 0;
static int beg = 0;
static int newModel = 1;


/* ARGSUSED3 */
void
mouse(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    moving = 1;
    beg = x;
  }
  if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
    moving = 0;
  }
}

/* ARGSUSED1 */
void motion(int x, int y)
{
  if (moving) {
    angle = angle + (x - beg);
    beg = x;
    newModel = 1;
    glutPostRedisplay();
  }
}

void
tablet(int x, int y)
{
  xloc = ((GLfloat) x) / 500 - 4;
  yloc = ((GLfloat) y) / 1000 - 2;
  newModel = 1;
  glutPostRedisplay();
}

int xt = 1, yt = 1, zt = 1, xr = 1;

void
translate(int x, int y, int z)
{
  GLfloat newz;

  if (xt)
    xloc += ((GLfloat) x) / 100;
  if (yt)
    yloc += ((GLfloat) y) / 100;
  if (zt) {
    newz = zloc - ((GLfloat) z) / 100;
    if (newz > -60.0 && newz < 13.0)
      zloc = newz;
  }
  newModel = 1;
  glutPostRedisplay();
}

/* ARGSUSED1 */
void
rotate(int x, int y, int z)
{
  if (xr) {
    angle += x / 2.0;
    newModel = 1;
    glutPostRedisplay();
  }
}

void
button(int button, int state)
{
  if (state == GLUT_DOWN) {
    switch (button) {
    case 1:
      xt = yt = zt = xr = 1;
      break;
    case 5:
      xt = 1;
      yt = zt = xr = 0;
      break;
    case 6:
      yt = 1;
      xt = zt = xr = 0;
      break;
    case 7:
      zt = 1;
      xt = yt = xr = 0;
      break;
    case 8:
      xr = 1;
      xt = yt = zt = 0;
      break;
    case 9:
      xloc = yloc = zloc = 0;
      newModel = 1;
      glutPostRedisplay();
      break;
    }
  }
}

int nRows = 480;
int nCols = 480; 
float degree = 10.0;
 
GLfloat light_ambient[] = {0.5, 0.5, 0.5, 1.0};  /* Red diffuse light. */
GLfloat light_diffuse[] = {0.8, 0.8, 0.8, 1.0};  /* Red diffuse light. */
GLfloat light_specular[] = {0.8, 0.8, 0.8, 1.0};  /* Red diffuse light. */
GLfloat light_position[] = {0.0, 0.0, 1.0, 0.0};  /* Infinite light location. */

static float modelAmb[4] = {0.2, 0.2, 0.2, 1.0};
static float matAmb[4] = {0.2, 0.2, 0.2, 1.0};
static float matDiff[4] = {0.8, 0.8, 0.8, 1.0};
static float matSpec[4] = {0.4, 0.4, 0.4, 1.0};
static float matEmission[4] = {0.0, 0.0, 0.0, 1.0};

static float modelAmb2[4] = {0.5, 0.5, 0.5, 1.0};
static float matAmb2[4] = {0.5, 0.5, 0.5, 1.0};
static float matDiff2[4] = {0.8, 0., 0., 1.0};
static float matSpec2[4] = {0.4, 0., 0., 1.0};
static float matEmission2[4] = {0.0, 0.0, 0.0, 1.0};

GLUquadricObj *qobj;
View::TriangleMesh trig{};
View::Bone B{};
/*
bool contain(Edge & e, map < pair <int, int> , Edge > & list) 
{

	pair <int, int> key;

	key.first = e.v1;
	key.second = e.v2;

	if (list.find(key) == list.end()) return false;
	else return true;
}
*/




/*
int edgeID(Edge & e, map < pair <int, int> , Edge > & list) 
{
	pair <int, int> key;

	key.first = e.v1;
	key.second = e.v2;

	if (list.find(key) == list.end()) return -1;
	else return list[key].id();   
}
*/

void recalcModelView(void)
{
	glPopMatrix();
	glPushMatrix();
	glTranslatef(xloc, yloc, zloc);
	glRotatef(angle, 0.0, 1.0, 0.0);
	glTranslatef(0, 0, .0);
	newModel = 0;
}

void myDisplay()
{
	if (newModel)
		recalcModelView();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear OpenGL Window
	int trignum = trig.trigNum();
	Vector3f v1,v2,v3,n1,n2,n3;
	B.BodyMotion(degree);
	
	trig.loadweight();
	glColor3f(1.0,0.0,0.0);
     


	for (int i = 0 ; i < trignum; i++)  
	{

		float m1,m2,m3,min,max;//before drawing we should make sure the 
		trig.getTriangleVertices(i,v1,v2,v3);
		//get vertices,then find the correspond vertices in attachment.
		trig.Weight_Calculation(i,B,v1,v2,v3);
                
		trig.getTriangleNormals(i,n1,n2,n3);
		trig.getMorseValue(i, m1, m2, m3);

		m1 = m2 = m3 = trig.color(i);

		GLfloat skinColor[] = {0.1, 1., 0.1, 1.0};
                
		if (max >= 0) {
			glBegin(GL_TRIANGLES);

				skinColor[1] = m1; skinColor[0] = 1-m1;
				glMaterialfv(GL_FRONT, GL_DIFFUSE, skinColor); 
				glNormal3f(-n1[0],-n1[1],-n1[2]);
				glVertex3f(v1[0],v1[1],v1[2]);

				skinColor[1] = m2; skinColor[0] = 1-m2;
				glMaterialfv(GL_FRONT, GL_DIFFUSE, skinColor); 
				glNormal3f(-n2[0],-n2[1],-n2[2]);
				glVertex3f(v2[0],v2[1],v2[2]);

				skinColor[1] = m3; skinColor[0] = 1-m3;
				glMaterialfv(GL_FRONT, GL_DIFFUSE, skinColor); 
				glNormal3f(-n3[0],-n3[1],-n3[2]);
				glVertex3f(v3[0],v3[1],v3[2]);

				skinColor[1] = m1; skinColor[0] = 1-m1;
				glMaterialfv(GL_FRONT, GL_DIFFUSE, skinColor); 
				glNormal3f(-n1[0],-n1[1],-n1[2]);
				glVertex3f(v1[0],v1[1],v1[2]);

			glEnd();
		}
	}

	 glutSwapBuffers();
}


void timerFunc(int value)
{
     
    degree+=2.0;

    if(degree>360.f)
    {

     degree-=360;

    }
    glutPostRedisplay();
    glutTimerFunc(30, timerFunc, 0);
}



int main(int argc, char **argv)
{
	if (argc >  1)  {
		trig.loadFile(argv[1]);
	}
	else {
		std::cerr << argv[0] << " <filename> " << std::endl;
		exit(1);
	}

	int width, height;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	glutInitWindowSize(nRows, nCols);
	glutCreateWindow("Toy");

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);


	/* Use depth buffering for hidden surface elimination. */
	glEnable(GL_DEPTH_TEST);

	/* Setup the view of the cube. */
	glMatrixMode(GL_PROJECTION);
	gluPerspective( /* field of view in degree */ 40.0, 
	/* aspect ratio */ 1., /* Z near */ 1.0, /* Z far */ 1000.0);

	glMatrixMode(GL_MODELVIEW);

	gluLookAt(0.0, 0.0, 7.0,  /* eye is at (0,0,5) */
		  0.0, 0.0, 0.0,      /* center is at (0,0,0) */
		  0.0, 1.0, 0.0);      /* up is in positive Y direction */
	glPushMatrix();       /* dummy push so we can pop on model recalc */


	glutDisplayFunc(myDisplay);// Callback function
        glutTimerFunc(30,timerFunc, 0);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutTabletMotionFunc(tablet);
	glutSpaceballMotionFunc(translate);
	glutSpaceballRotateFunc(rotate);
	glutSpaceballButtonFunc(button);

	glutMainLoop();// Display everything and wait
}
