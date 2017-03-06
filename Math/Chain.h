#ifndef _Chain_H
#define _Chain_H

#include <vector>
#include <iostream>
#include <Math/Object.h>
#include <Math/Quaternion.h>
#include <Math/Vector3.h>

namespace Math
{
	/** \brief Gestion d'une chaine articulaire

	Cette classe permet d'accumuler les transformations associées à une chaine articulaire linéraire.
	Elle offre une fonctionnalité de dérivation en fonction de la variation de l'angle associé à un quaternion.
	*/
	class Chain
	{
	private:
		// La liste des transformations
		std::vector<Object*> m_transforms ;

		// Recherche d'un quaternion
		int find(Quaternion * q)
		{
			for(unsigned int cpt=0 ; cpt<m_transforms.size() ; cpt++)
			{
				if(q==m_transforms[cpt])
				{
					return cpt ;
				}
			}
			return -1 ;
		}

	public:
		/** \brief Constructeur par defaut */
		Chain()
		{}

		/** \brief Ajoute une transformation (Vector3 = translation / Quaternion = rotation) */
		void add(Object * object)
		{
			m_transforms.push_back(object) ;
		}

		/** \brief Calcule la position de l'extrémité de la chaine articulaire. */
		Vector3 compute()
		{
			Quaternion result(Vector3(0.0, 0.0, 0.0), 0.0) ;
			for(int cpt=(int)m_transforms.size()-1 ; cpt>=0 ; cpt--)
			{
				if(dynamic_cast<Vector3*>(m_transforms[cpt]))
				{
					result = result+(*(Vector3*)m_transforms[cpt]) ;
				}
				if(dynamic_cast<Quaternion*>(m_transforms[cpt]))
				{
					result = (*(Quaternion*)m_transforms[cpt]).rotate(result) ;
				}
			}
			return result.v() ;
		}

		/** Dérivation de l'extrémité de la chaine articulaire en fonction de l'angle d'un quaternion
		epsilon : précision utilisée pour la dérivation
		quat : pointeur sur le quaternion correspondant à l'angle par rapport auquel dériver.
		\warning Si le pointeur sur le quaternion est invalide (i.e. non référencé), le programme 
		s'arrête en affichant une erreur.
		*/
		Vector3 derivate(float epsilon, Quaternion * quat)
		{
			int index = find(quat) ;
			if(index==-1)
			{
				std::cerr<<"Chain::derivate Quaternion does not exists"<<std::endl ;
				exit(-1) ;
			}
			float angle = quat->getAngle() ;
			quat->setAxisAngle(quat->getAxis(), angle-epsilon) ;
			Vector3 minusEpsilon = compute() ;
			quat->setAxisAngle(quat->getAxis(), angle+epsilon) ;
			Vector3 plusEpsilon = compute() ;
			quat->setAxisAngle(quat->getAxis(), angle) ;
			return (plusEpsilon-minusEpsilon)/(2.0*epsilon) ;
		}
	} ;

}

#endif
