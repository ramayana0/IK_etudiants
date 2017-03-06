#ifndef _Animation_H
#define _Animation_H

#include "SceneGraph/Nodes.h"
#include <Math/Quaternion.h>
#include <Math/Vector3.h>
#include <Math/Vector4.h>
#include <Math/Matrix44.h>
#include <Math/Chain.h>
#include <vector>
#include <time.h>
using namespace std;

/** \brief Classe de gestion de l'affichage et de l'animation de la chaine polyarticulée
 */
class Animation
{
protected:
  /** \brief Noeud Group représentant la racine du graphe de scène. */
	Math::Chain *chain;
	std::vector<Math::Vector3*> vectors;
	std::vector<Math::Quaternion*> quaternions;
	std::vector<SceneGraph::Rotation*> rotations;
	std::vector<SceneGraph::Translation*> translations;
	SceneGraph::Group* m_root;
	float S_radius = 0.08;
	GLdouble C_radius = 0.05;
	GLdouble C_height = 1;

  /** \brief Nombre de segments composant la chaîne cinématique. */
	int nbSegments;

public:
  /** \brief constructeur */
  Animation(const int nbSeg)
		: nbSegments(nbSeg)
  {
		m_root = new SceneGraph::Group;
		chain = new Math::Chain();
		createChain();
  }

  /** \brief Méthode appelée pour le calcul de l'animation.

  Dans cette méthode, vous devrez implémenter tous vos calculs d'animation.
   */
  void computeAnimation(const bool newTarget, const Math::Vector3& target)
  {
	  //if (newTarget) {
		  computeOneIteration(target);
	  //{
  }

  /** Méthode de creation d'une chaine polyarticulee */
  void createChain()
  {
	  SceneGraph::Group* m_current = m_root;

	  for (int i = 0; i < nbSegments; i++) {
		  Math::Vector3* transVector = new Math::Vector3(0, 1, 0);
		  Math::Vector3* quatVector = new Math::Vector3(0, 0, 1);
		  Math::Quaternion* rotateQuaternion = new Math::Quaternion(*quatVector, 0);

		  SceneGraph::Cylinder* c1 = new SceneGraph::Cylinder(C_radius, C_radius, C_height);
		  SceneGraph::Rotation* r1 = new SceneGraph::Rotation(0, 0, 1, 0);
		  SceneGraph::Sphere* s1 = new SceneGraph::Sphere(S_radius);
		  SceneGraph::Translation* t1 = new SceneGraph::Translation(0, 1, 0);

		  m_current->addChild(r1);
		  r1->addChild(t1);
		  r1->addChild(c1);
		  t1->addChild(s1);

		  vectors.push_back(transVector);
		  quaternions.push_back(rotateQuaternion);

		  m_current = t1;

		  rotations.push_back(r1);
		  translations.push_back(t1);
		  chain->add(rotateQuaternion);
		  chain->add(transVector);
	  }
	  SceneGraph::Sphere* s_chain = new SceneGraph::Sphere(0.12);
	  SceneGraph::Translation* t_chain = new SceneGraph::Translation(chain->compute());
	  m_root->addChild(t_chain);
	  t_chain->addChild(s_chain);
  }
  void computeOneIteration(const Math::Vector3 target) 
  {
	  Math::Vector3 dp = target;
	  cout << dp.norm();
	  SceneGraph::Rotation* rotate;
	  Math::Quaternion* quat;
	  Math::Vector3 deriv;
	  do {
		  
		  for (int i = 0; i < nbSegments; i++)
		  {
			  rotate = rotations[i];
			  quat = quaternions[i];
			  deriv = chain->derivate(0.001, quat);
			  dp = target - chain->compute();

			  float deltaTheta = deriv.inv() * dp;
			  if (deltaTheta > 0.05) {
				  deltaTheta = 0.05f;
			  }
			  else if (deltaTheta < -0.05) {
				  deltaTheta = -0.05;
			  }
			  quat->setAngle(quat->getAngle() + deltaTheta);
			  rotate->setAngle(rotate->getAngle() + deltaTheta);
		  }
		  dp = target - chain->compute();
		  cout << dp.norm();
	  } while (dp.norm()>1 && dp.norm()<0.001);
  }

  /** \brief Méthode appelée pour le rendu de la scène.
      \warning : normalement vous ne devriez pas avoir à modifier cette méthode. 
   */
  void drawScene()
  {
    m_root->draw();
  }
} ; 

#endif
