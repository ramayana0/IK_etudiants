#ifndef _Sphere_H
#define _Sphere_H

#include <GL/glu.h>
#include "DrawObject.h"

namespace SceneGraph
{

  /** \brief Noeud de géométrie représentant une sphère.
   */
class Sphere : public DrawObject
{
private:
  float m_radius ;

public:
  /** \brief Constructeur de sphère 
      \param radius : le rayon de la sphère
   */
  Sphere(float radius)
  {
    m_radius = radius ;
  }

  /** \brief Gestion de l'affichage OpenGL */
  virtual void draw()
  {
    GLUquadric * quadric=gluNewQuadric() ;
    gluQuadricOrientation(quadric, GLU_OUTSIDE) ;
    glColor3f(1.0, 0.0, 0.0) ;
    gluSphere(quadric, m_radius, 10, 10) ;
    gluDeleteQuadric(quadric) ;
  }
} ;

}

#endif
