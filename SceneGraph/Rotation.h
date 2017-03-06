#ifndef _Rotation_H
#define _Rotation_H

#include <GL/glut.h>
#include "Group.h"
#include <math.h>

#define M_PI        3.14159265358979323846

namespace SceneGraph
{
  /** \brief Noeud de rotation

  ce noeud est une spécialisation du noeud groupe, applicant une rotation à tous ses fils.
   */
class Rotation : public Group
{
protected:
  float m_x, m_y, m_z, m_angle ;

public:
  /** \brief Constructeur de rotation : identité par défaut */ 
  Rotation()
  {
    m_x = 1.0 ; m_y=0.0, m_z=0.0 ; m_angle=0.0 ;
  }

  /** \brief Constructeur de rotation : identité par défaut */ 
  Rotation(float x, float y, float z, float angle)
  {
    setVector(x,y,z);
    setAngle(angle);
  }

  /** \brief Changement de l'angle de rotation (en radians) */
  void setAngle(float angle)
  {
    m_angle = angle*180.0/M_PI ;
  }

  /** \brief Changement de l'angle de rotation (en radians) */
  float getAngle()
  {
    return m_angle*M_PI/180.0;//
  }

  /** \brief changement de l'axe de rotation */
  void setVector(float x, float y, float z)
  {
    m_x = x ; m_y = y ; m_z = z ;
  }

  /** \brief Gestion de l'affichage OpenGL */
  virtual void draw()
  {
    glPushMatrix() ;
    glRotatef(m_angle, m_x, m_y, m_z) ;
    Group::draw() ;
    glPopMatrix() ;
  }
} ;

}

#endif
