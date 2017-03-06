#ifndef _Cylinder_H
#define _Cylinder_H

#include <GL/glu.h>
#include "DrawObject.h"

namespace SceneGraph
{
  /** \brief Noeud graphique représentant un cylindre. 
      
  Le cylindre est décrit par les rayons de lsa base et de son sommet, ainsi que par sa hauteur. 
  \warning : La hauteur se situe sur l'axe des Z.
  */
class Cylinder : public DrawObject
{
private:
  GLdouble m_base ;
  GLdouble m_top ;
  GLdouble m_height ;
  GLint    m_slices ;
  GLint    m_stacks ;
              

public:
  /** Constructeur de cylindre
      \param base : le rayon de la base du cylindre
      \param top : le rayon du sommet du cylindre
      \param height : la hauteur du cylindre 
   */
  Cylinder(GLdouble base, GLdouble top, GLdouble height)
  {
    m_base = base ;
    m_top = top ;
    m_height = height ;
    m_slices = 10 ;
    m_stacks = 1 ;
  }

  /** \brief Gestion de l'affichage openGL */
  virtual void draw()
  {
    glPushMatrix() ;
    GLUquadric * quadric = gluNewQuadric() ;
    gluQuadricDrawStyle(quadric, GLU_FILL) ;
    glColor3f(1.0, 1.0, 0.0) ;
    glRotatef(-90.0, 1.0, 0.0, 0.0) ;
    gluCylinder(quadric, m_base, m_top, m_height, m_slices, m_stacks) ;
    gluDeleteQuadric(quadric) ;

    glPushMatrix() ;
    quadric = gluNewQuadric() ;
    glRotatef(180.0, 0.0, 1.0, 0.0) ;
    gluDisk(quadric, 0.0, m_base, m_slices, 1) ;
    gluDeleteQuadric(quadric) ;
    glPopMatrix() ;

    glTranslatef(0.0, 0.0, m_height) ;

    quadric = gluNewQuadric() ;
    gluDisk(quadric, 0.0, m_top, m_slices, 1) ;
    gluDeleteQuadric(quadric) ;
	    
    glPopMatrix() ;
  }

} ;

}

#endif
