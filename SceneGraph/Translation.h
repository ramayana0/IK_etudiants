#ifndef _Translation_H
#define _Translation_H

#include <Math/Vector3.h>

namespace SceneGraph
{

  /** \brief Noeud translation
      
  Le noeud translation est une spécialisation d'un Group permettant 
  de décrire des translations répercutées sur les fils de ce noeud.
   */
class Translation : public Group
{
private:
  float m_x, m_y, m_z ;
public:
  /** \brief Contructeur d'une translation : translation nulle par defaut. */
  Translation()
  {
    m_x=0.0 ; m_y=0.0 ; m_z=0.0 ;
  }

  /** \brief Contructeur d'une translation : translation nulle par defaut. */
  Translation(const float x, const float y, const float z)
  {
    setVector(x,y,z);
  }

  /** \brief Contructeur d'une translation : translation nulle par defaut. */
	Translation(const Math::Vector3& v)
  {
    setVector(v);
  }

  /** \brief Changement du vecteur de translation */
  void setVector(const float x, const float y, const float z)
  {
    m_x = x ; m_y = y ; m_z = z ;
  }

  /** \brief Contructeur d'une translation : translation nulle par defaut. */
	void setVector(const Math::Vector3& v)
  {
    m_x = v[0] ; m_y = v[1] ; m_z = v[2] ;
  }

  /** \brief Gestion de l'affichage OpenGL */
  virtual void draw()
  {
    glPushMatrix() ;
    glTranslatef(m_x, m_y, m_z) ;
    Group::draw() ;
    glPopMatrix() ;
  }
} ;

}

#endif
