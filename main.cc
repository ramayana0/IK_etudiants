#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>       /* for cos(), sin(), and sqrt() */
#include <GL/glut.h>
#include <Animation.h>
#include <SceneGraph/Nodes.h>
#include <Math/Chain.h>

// Nombre de segments de la chaîne cinématique
static const int nbSegments=6;

// Dimensions de la fenêtre
static int Width = 600, Height = 600;
static float width = (float)Width, height = (float)Height;
static int beginx, beginy;
static float heightInMeter = 3.6;

// Modes pour la gestion de la camera
static bool modeTranslationXY = false ;
static bool modeTranslationZ = false ;
static bool modeRotationXY = false ;

// Position de la camera
static float cameraX = 0.0 ;
static float cameraY = heightInMeter;
static float cameraZ = -10.0 ;

// Rotations de la camera
static float cameraAngleX = 0.0 ;
static float cameraAngleY = 0.0 ;

// Les lumieres
static GLfloat lightZeroPosition[] = {10.0, 4.0, 10.0, 1.0};
static GLfloat lightZeroColor[] = {0.8, 1.0, 0.8, 1.0}; /* green-tinted */
static GLfloat lightOnePosition[] = {-1.0, -2.0, 1.0, 0.0};
static GLfloat lightOneColor[] = {0.6, 0.3, 0.2, 1.0}; /* red-tinted */

static Animation animation(nbSegments); 
static Math::Vector3 target(0,nbSegments,0);
static bool newTarget(true);

// Transformation associee a la camera
void cameraTransform()
{
  // Supprime la derniere matrice
  glPopMatrix() ;
  // Nouvelle transformation
  glPushMatrix() ;
  // Mise à jour des transformations de la camera
  glTranslatef(-cameraX, -cameraY, -cameraZ) ;
  glRotatef(-cameraAngleX, 1.0, 0.0, 0.0) ;
  glRotatef(-cameraAngleY, 0.0, 1.0, 0.0) ;
}

void redraw(void)
{
  animation.computeAnimation(newTarget, target) ;
  newTarget = false;
  // ICI : calcul de l'animation
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // Transformations de la camera
  cameraTransform() ;
  // CREATE THE DISPLAY LIST FOR AN AXIS WITH ARROWS POINTING IN
  // THE POSITIVE DIRECTION Red = X, Green = Y, Blue = Z
  glNewList(0,GL_COMPILE);
  glPushMatrix();
  glScalef(2.0,2.0,2.0);
  glTranslatef(1,0,0);
  glBegin(GL_LINES);
  glColor3f(1.0f, 0.0f, 0.0f);	// X AXIS STARTS - COLOR RED
  glVertex3f(-0.2f,  0.0f, 0.0f);
  glVertex3f( 0.2f,  0.0f, 0.0f);
  glVertex3f( 0.2f,  0.0f, 0.0f);	// TOP PIECE OF ARROWHEAD
  glVertex3f( 0.15f,  0.04f, 0.0f);
  glVertex3f( 0.2f,  0.0f, 0.0f);	// BOTTOM PIECE OF ARROWHEAD
  glVertex3f( 0.15f, -0.04f, 0.0f);
  glColor3f(0.0f, 1.0f, 0.0f);	// Y AXIS STARTS - COLOR GREEN
  glVertex3f( 0.0f,  0.2f, 0.0f);
  glVertex3f( 0.0f, -0.2f, 0.0f);			
  glVertex3f( 0.0f,  0.2f, 0.0f);	// TOP PIECE OF ARROWHEAD
  glVertex3f( 0.04f,  0.15f, 0.0f);
  glVertex3f( 0.0f,  0.2f, 0.0f);	// BOTTOM PIECE OF ARROWHEAD
  glVertex3f( -0.04f,  0.15f, 0.0f);
  glColor3f(0.0f, 0.0f, 1.0f);	// Z AXIS STARTS - COLOR BLUE
  glVertex3f( 0.0f,  0.0f,  0.2f);
  glVertex3f( 0.0f,  0.0f, -0.2f);
  glVertex3f( 0.0f,  0.0f, 0.2f);	// TOP PIECE OF ARROWHEAD
  glVertex3f( 0.0f,  0.04f, 0.15f);
  glVertex3f( 0.0f, 0.0f, 0.2f);	// BOTTOM PIECE OF ARROWHEAD
  glVertex3f( 0.0f, -0.04f, 0.15f);
  glEnd();
  glPopMatrix();
  glEndList();
  // ICI : affichage de la geometrie
  animation.drawScene() ;
  // Fin d'affichage de la geometrie
  glutSwapBuffers();
}

void myReshape(int w, int h)
{
  glViewport(0, 0, w, h);
  Width = w ;
  Height = h ;
}

void mouse(int button, int state, int x, int y)
{
  beginx = x ;
  beginy = y ;

//   modeTranslationZ = false ;
//   modeTranslationXY = false ;
//   modeRotationXY = false ;
  
//   if(button==GLUT_LEFT_BUTTON && (glutGetModifiers()&GLUT_ACTIVE_SHIFT))
//     {
//       modeTranslationZ = state==GLUT_DOWN ;
//     }
//   else if(button==GLUT_LEFT_BUTTON)
//     {
//       modeTranslationXY = state==GLUT_DOWN ;
//     }

//   if(button==GLUT_RIGHT_BUTTON)
//     {
//       modeRotationXY = state==GLUT_DOWN ;
//     }
  if(button==GLUT_LEFT_BUTTON && state == GLUT_UP)
  {
    target = Math::Vector3(-((float)x-height/2.f)/height*heightInMeter*2.f,-((float)y-height)/(float)height*heightInMeter*2.f,0);
    newTarget = true;
  }


//   if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
//     if(glutGetModifiers()&GLUT_ACTIVE_SHIFT)
//     		scaling=1;
//     else	moving = 1;
//     beginx = x;
//     beginy = y;
//   }
//   if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
//     moving = 0;
//     scaling = 0;
//   }
}

void mouseMotion(int x, int y)
{
  if(modeTranslationXY)
    {
      cameraX -= (float)(x-beginx)/10.0 ;
      cameraY -= (float)(y-beginy)/10.0 ;
    }
  else if(modeTranslationZ)
    {
      cameraZ += (y-beginy) ;
    }
  else if(modeRotationXY)
    {
      cameraAngleY += (x-beginx) ;
      cameraAngleX += (y-beginy) ;
    }

  beginx = x ;
  beginy = y ;

  // Force le nouvel affichage
  glutPostRedisplay() ;
}

void menu(int value)
{
  switch (value) {
  case 1:
    exit(0);
    break;
  }
  glutPostRedisplay();
}

static void key(unsigned char key, int x, int y)
{
  switch (key) {
  case 27: /* escape */
    exit(0);
  }
}

void _cdecl display()
{
	glutPostRedisplay();
}


int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
  glutCreateWindow("FastIK");
  glutReshapeWindow(Width,Height);
  glutDisplayFunc(redraw);
  glutReshapeFunc(myReshape);
  glutMouseFunc(mouse);
  glutMotionFunc(mouseMotion);
  glutCreateMenu(menu);
  glutKeyboardFunc(key);
  glutAddMenuEntry("Quit", 1);
  glutAttachMenu(GLUT_MIDDLE_BUTTON);
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glDisable(GL_LIGHTING);
  glMatrixMode(GL_PROJECTION);
  glutIdleFunc(display) ;
  gluPerspective( /* field of view in degree */ 40.0,
  /* aspect ratio */ 1.0,
    /* Z near */ 1.0, /* Z far */ 400.0);
  glPushMatrix();       /* dummy push so we can pop on model
                           recalc */
  glMatrixMode(GL_MODELVIEW);
  gluLookAt(0.0, 0.0, 00.0,  /* eye is at (0,0,30) */
    0.0, 0.0, 1.0,      /* center is at (0,0,0) */
    0.0, 1.0, 0.);      /* up is in positive Y direction */
  glPushMatrix();       /* dummy push so we can pop on model
                           recalc */
  glPushMatrix() ;
  GLfloat color[] = {255.0, 255.0, 255.0, 255.0} ;
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, color) ;
  //glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
//   glLightfv(GL_LIGHT0, GL_POSITION, lightZeroPosition);
//   glLightfv(GL_LIGHT0, GL_DIFFUSE, lightZeroColor);
//   glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.1);
//   glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.05);
//   glLightfv(GL_LIGHT1, GL_POSITION, lightOnePosition);
//   glLightfv(GL_LIGHT1, GL_DIFFUSE, lightOneColor);
//   glEnable(GL_LIGHT0);
//   glEnable(GL_LIGHT1);
  glLineWidth(2.0);
  glutPostRedisplay() ;
  glutMainLoop();
  return 0;             /* ANSI C requires main to return int. */
}
