#ifndef _Group_H
#define _Group_H

#include "DrawObject.h"
#include <vector>

namespace SceneGraph
{

  /** \brief Noeud représentant un groupe d'objets */
class Group : public DrawObject
{
private:
  std::vector<DrawObject*> m_objects ;
  
public:
  Group()
  {}

  ~Group()
  {
    for(unsigned int cpt=0 ; cpt<m_objects.size() ; cpt++)
      {
				delete m_objects[cpt];
      }
  }

  /** \brief Ajout d'un fils au groupe d'objets. */
  void addChild(DrawObject * object)
  {
    m_objects.push_back(object) ;
  }

  /** \brief Gestion de l'affichage OpenGL */
  virtual void draw()
  {
    for(unsigned int cpt=0 ; cpt<m_objects.size() ; cpt++)
      {
	m_objects[cpt]->draw() ;
      }
  }
} ;

}

#endif
