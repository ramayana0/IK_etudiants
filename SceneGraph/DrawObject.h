#ifndef _DrawObject_H
#define _DrawObject_H

namespace SceneGraph
{

  /** \brief Classe m�re de tous les noeuds du graphe de sc�ne. */
class DrawObject
{
public :
  /** Gestion de l'affichage OpenGL */
  virtual void draw() = 0 ;

  virtual ~DrawObject()
  {}
} ;

}

#endif 
