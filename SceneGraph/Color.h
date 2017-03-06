#ifndef _Color_H
#define _Color_H

#include <SceneGraph/DrawObject.h>

namespace SceneGraph
{

  /** \brief Noeud du graphe de scène permettant de donner une couleur aux objets. */
class Color : public DrawObject
{
private:
  float m_red, m_green, m_blue ;

public:
  /** Constructeur d'une couleur
      \param red : composante rouge dans [0,1]
      \param green : composante verte dans [0,1]
      \param blue : composante bleue dans [0,1]
   */
  Color(float red, float green, float blue)
    : m_red(red), m_green(green), m_blue(blue)
  {}

  /** \brief Gestion de l'affichage OpenGL */
  virtual void draw()
  {
    glColor3f(m_red, m_green, m_blue) ;
  }
} ;

}

#endif
