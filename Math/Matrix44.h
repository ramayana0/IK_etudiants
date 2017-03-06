#ifndef _Matrix44_h
#define _Matrix44_h

#include <Math/Vector4.h>
using namespace std;

//*************************************************************************************
/*! \class Math::Matrix44
		\brief Cette classe définit une matrice de dimension 4x4.

*/ //**********************************************************************************

namespace Math
{
	class Matrix44
	{
		public:
		//************************************************************
		//! @name Constructeurs et Destructeur
		//************************************************************
		//@{
		//------------------------------------------------------------
		//! Constructeur par défaut
		//------------------------------------------------------------
		Matrix44() {}

		//------------------------------------------------------------
		//! Constructeur à partir de 9 éléments (matrice 3x3)
		/*! \param f00 élément [0,0]
				\param f01 élément [0,1]
				...
		*/ //---------------------------------------------------------
		Matrix44(const float& f00,const float& f01,const float& f02,const float& f03,
						const float& f10,const float& f11,const float& f12,const float& f13,
						const float& f20,const float& f21,const float& f22,const float& f23,
						const float& f30,const float& f31,const float& f32,const float& f33)
		{
			m[0].set(f00,f01,f02,f03);
			m[1].set(f10,f11,f12,f13);
			m[2].set(f20,f21,f22,f23);
			m[3].set(f30,f31,f32,f33);
		}

		//------------------------------------------------------------
		//! Constructeur à partir d'une matrice
		/*! \param mat Matrice à copier
		*/ //---------------------------------------------------------
		Matrix44(const Matrix44& mat)
		{
			// On stocke les éléments de la matrice
			for (unsigned int i=0;i<4;i++)
				m[i]=mat[i];
		}

		//------------------------------------------------------------
		//! Constructeur à partir d'un tableau continu des valeurs de la matrice
		/*! Attention ! Aucun contrôle sur le tableau fourni en paramètre !
				Le tableau contient les valeurs de la matrice ligne par ligne
				\param elements Elements de la matrice
		*/ //---------------------------------------------------------
		Matrix44(const float* elements)
		{
			// On stocke les éléments de la matrice
			for (unsigned int k=0, i=0;i<4;i++)
				for (unsigned int j=0;j<4;j++)
					m[i][j]=elements[k++];
		}

		//------------------------------------------------------------
		//! Destructeur
		//------------------------------------------------------------
		virtual ~Matrix44() {}
		//@}

		//************************************************************
		//! @name Accesseurs
		//************************************************************
		//@{
		//------------------------------------------------------------
		//! Permet de lire un élément de la matrice
		/*! \param line Indice de la ligne
				\param col Indice de la colonne
				\return Element (line,col) correspondant
		*/ //---------------------------------------------------------
		float const & element(unsigned int line, unsigned int col) const
		{
			if ((line>=4)&&(col>=4)) 
			{
				cout << "Matrix44::element(line,col) indice hors limites" << endl;
				exit(-1);
			}
			return m[line][col];
		}

		//------------------------------------------------------------
		//! Permet de lire un élément de la matrice
		/*! \param i Indice de la ligne
				\param j Indice de la colonne
				\return Element (i,j) correspondant
		*/ //---------------------------------------------------------
		float& element(unsigned int line, unsigned int col)
		{
			if ((line>=4)&&(col>=4)) 
			{
				cout << "Matrix44::element(line,col) indice hors limites" << endl;
				exit(-1);
			}
			return m[line][col];
		}

		//------------------------------------------------------------
		//! Permet de lire un vecteur ligne
		/*! \param i Indice de la ligne
				\return Vecteur ligne
		*/ //---------------------------------------------------------
		Vector4 const & operator [] (const unsigned int line) const
		{
			if (line>=4)
			{
				cout << "Matrix44::operator [](line) indice hors limites" << endl;
				exit(-1);
			}
			return m[line];
		}

		//------------------------------------------------------------
		//! Permet de lire un vecteur ligne
		/*! \param line Indice de la ligne
				\return Vecteur ligne
		*/ //---------------------------------------------------------
		Vector4 const & row(const unsigned int line) const
		{
			if (line>=4)
			{
				cout << "Matrix44::row(line) indice hors limites" << endl;
				exit(-1);
			}
			return m[line];
		}

		//------------------------------------------------------------
		//! Permet de lire un vecteur colonne
		/*! \param col Indice de la colonne
				\return Vecteur colonne
		*/ //---------------------------------------------------------
		Vector4 column(const unsigned int col) const
		{
			if (col>=4)
			{
				cout << "Matrix44::column(col) indice hors limites" << endl;
				exit(-1);
			}
			Vector4 result;
			for (unsigned int i=0;i<4;i++) result[i]=m[i][col];
			return result;
		}
		//@}

		//************************************************************
		//! @name Assignements
		//************************************************************
		//@{
		//------------------------------------------------------------
		//! Assigne à partir d'une même classe
		/*! \param mat Une référence à une même classe
				\return La classe copiée
		*/ //---------------------------------------------------------
    Matrix44 & operator = (const Matrix44& mat)
		{
			for (unsigned int i=0;i<4;i++)
				m[i]=mat.m[i];
			return (*this);
		}

		//------------------------------------------------------------
		//! Permet de modifier un élément de la matrice
		/*! \param line Indice de la ligne
				\param col Indice de la colonne
				\param val Nouvelle valeur de l'élément
		*/ //---------------------------------------------------------
		void element(unsigned int line, unsigned int col, const float& val)
		{
			if ((line>=4)&&(col>=4)) 
			{
				cout << "Matrix44::element(line,col) indice hors limites" << endl;
				exit(-1);
			}
			m[line][col] = val;
		}

		//------------------------------------------------------------
		//! Permet de modifier un vecteur ligne
		/*! \param line Indice de la ligne
				\return Vecteur ligne
		*/ //---------------------------------------------------------
		Vector4 & operator [] (const unsigned int line)
		{
			if (line>=4)
			{
				cout << "Matrix44::operator [](line) indice hors limites" << endl;
				exit(-1);
			}
			return m[line];
		}

		//------------------------------------------------------------
		//! Permet de modifier un vecteur ligne
		/*! \param line Indice de la ligne
				\param vec Nouveau vecteur ligne
		*/ //---------------------------------------------------------
		void row(const unsigned int line, const Vector4& vec)
		{
			if (line>=4)
			{
				cout << "Matrix44::row(line) indice hors limites" << endl;
				exit(-1);
			}
			m[line]=vec;
		}

		//------------------------------------------------------------
		//! Permet de modifier un vecteur colonne
		/*! \param col Indice de la colonne
				\param vec Nouveau vecteur colonne
		*/ //---------------------------------------------------------
		void column(const unsigned int col,const Vector4& vec)
		{
			if (col>=4)
			{
				cout << "Matrix44::column(line) indice hors limites" << endl;
				exit(-1);
			}
			for (unsigned int i=0;i<4;i++) m[i][col]=vec[i];
		}
		//@}

		//************************************************************
		//! @name Opérateurs de comparaison
		//************************************************************
		//@{
		//-------------------------------------------------------------
		//! Comparaison (élément à élément) avec une même classe
		/*! \param mat Une référence sur une classe de même type
				\return Réponse booléenne sur l'égalité
		*/ //----------------------------------------------------------
		//bool operator == (const Matrix44& mat) const
		//{
		//	for (unsigned int i=0;i<4;i++)
		//		if (m[i]!=mat[i])
		//			return false;
		//	return true;
		//}

		//-----------------------------------------------------------------
		//! Différence (élément à élément) avec une même classe
		/*! \param mat Une référence sur une classe de même type
				\return Réponse booléenne sur la différence
		*/ //--------------------------------------------------------------
		//bool operator != (const Matrix44& mat) const
		//{
		//	for (unsigned int i=0;i<4;i++)
		//		if (m[i]!=mat[i])
		//			return true;
		//	return false;
		//}

		//@}

		//************************************************************
		//! @name Opérations arithmétiques sur la matrice courante
		//************************************************************
		//@{
		//-----------------------------------------------------------------
		//! Permet d'ajouter (élément à élément) à cette matrice une autre
		/*! \param mat Matrice
				\return Une référence sur cette matrice
		*/ //--------------------------------------------------------------
		//Matrix44& operator += (const Matrix44& mat)
		//{
		//	for (unsigned int i=0;i<4;i++)
		//		m[i]+=mat[i];
		//	return *this;
		//}

		//------------------------------------------------------------------------
		//! Permet de soustraire (élément à élément) une autre matrice à celle-ci
		/*! \param mat Matrice
				\return Une référence sur cette matrice
		*/ //---------------------------------------------------------------------
		//Matrix44& operator -= (const Matrix44& mat)
		//{
		//	for (unsigned int i=0;i<4;i++)
		//		m[i]-=mat[i];
		//	return *this;
		//}

		//------------------------------------------------------------------------
		//! Permet de multiplier (élément à élément) une autre matrice à celle-ci
		/*! \param mat Matrice
				\return Une référence sur cette matrice
		*/ //---------------------------------------------------------------------
		//Matrix44& operator *= (const Matrix44& mat)
		//{
		//	for (unsigned int i=0;i<4;i++)
		//		m[i]*=mat[i];
		//	return *this;
		//}

		//---------------------------------------------------------------------
		//! Permet de diviser (élément à élément) une autre matrice à celle-ci
		/*! \param mat Matrice
				\return Une référence sur cette matrice
		*/ //------------------------------------------------------------------
		//Matrix44& operator /= (const Matrix44& mat)
		//{
		//	for (unsigned int i=0;i<4;i++)
		//		m[i]/=mat[i];
		//	return *this;
		//}

		//----------------------------------------------------------------
		//! Permet d'ajouter une valeur à chaque élément de cette matrice
		/*! \param val Valeur
				\return Une référence sur cette matrice
		*/ //-------------------------------------------------------------
		//Matrix44& operator += (const float& val)
		//{
		//	for (unsigned int i=0;i<4;i++)
		//		m[i]+=val;
		//	return *this;
		//}

		//--------------------------------------------------------------------
		//! Permet de soustraire une valeur à chaque élément de cette matrice
		/*! \param val Valeur
				\return Une référence sur cette matrice
		*/ //-----------------------------------------------------------------
		//Matrix44& operator -= (const float& val)
		//{
		//	for (unsigned int i=0;i<4;i++)
		//		m[i]-=val;
		//	return *this;
		//}

		//-------------------------------------------------------------
		//! Permet de multiplier une valeur à chaque élément de cette matrice
		/*! \param val Valeur
				\return Une référence sur cette matrice
		*/ //-----------------------------------------------------------------
		//Matrix44& operator *= (const float& val)
		//{
		//	for (unsigned int i=0;i<4;i++)
		//		m[i]*=val;
		//	return *this;
		//}

		//------------------------------------------------------------
		//! Permet de diviser une valeur à chaque élément de cette matrice
		/*! \param val Valeur
				\return Une référence sur cette matrice
		*/
		//------------------------------------------------------------
		//Matrix44& operator /= (const float& val)
		//{
		//	mkASSERT_DEBUG( (val!=0) , "Matrix44::/=(val) division par zéro" );
		//	for (unsigned int i=0;i<4;i++)
		//		m[i]/=val;
		//	return *this;
		//}
		//@}

		//************************************************************
		//! @name Opérations arithmétiques sur une troisième matrice
		//************************************************************
		//@{
		//------------------------------------------------------------
		//! Permet d'ajouter (élément à élément) cette matrice une autre
		/*! \param mat Matrice
				\return La matrice résultante
		*/ //---------------------------------------------------------
		Matrix44 operator + (const Matrix44& mat) const
		{
			Matrix44	result;
			for (unsigned int i=0;i<4;i++)
				result.m[i] = m[i]+mat.m[i];
			return result;
		}

		//------------------------------------------------------------
		//! Permet de soustraire (élément à élément) une autre matrice à celle-ci
		/*! \param mat Matrice
				\return La matrice résultante
		*/ //---------------------------------------------------------
		Matrix44 operator - (const Matrix44& mat) const
		{
			Matrix44	result;
			for (unsigned int i=0;i<4;i++)
				result.m[i] = m[i]-mat.m[i];
			return result;
		}

		//------------------------------------------------------------
		//! Permet de multiplier une valeur à cette matrice
		/*! \param val Valeur
				\return La matrice résultante
		*/ //---------------------------------------------------------
		Matrix44 operator * (const float& val) const
		{
			Matrix44	result;
			for (unsigned int i=0;i<4;i++)
				result.m[i] = m[i]*val;
			return result;
		}

		//------------------------------------------------------------
		//! Permet de diviser une valeur à cette matrice
		/*! \param val Valeur
				\return La matrice résultante
		*/ //---------------------------------------------------------
		Matrix44 operator / (const float& val) const
		{
			if (val == 0)
			{
				cout << "Matrix44::/(val) division par zéro" << endl;
				exit(-1);
			}
			Matrix44	result;
			for (unsigned int i=0;i<4;i++)
				result.m[i] = m[i]/val;
			return result;
		}

		//------------------------------------------------------------
		//! Permet de multiplier mathématiquement une autre matrice à celle-ci
		/*! \param mat Matrice
				\return La matrice résultante
		*/ //---------------------------------------------------------
		Matrix44 operator * (const Matrix44& mat) const
		{
			Matrix44	result;
			Vector4			matcol;
			for (unsigned int col=0;col<4;col++)
			{	
				matcol=mat.column(col);
				for (unsigned int line=0;line<4;line++)
					result.m[line][col] = m[line]*matcol;
			}
			return result;
		}

		//------------------------------------------------------------
		//! Permet de multiplier mathématiquement un vecteur à cette matrice
		/*! \param vec Vecteur
				\return La matrice résultante
		*/ //---------------------------------------------------------
		Vector4 operator * (const Vector4& vec) const
		{
			Vector4	result;
			for (unsigned int i=0;i<4;i++)
				result[i]=m[i]*vec;
			return result;
		}
		//@}

		//**************************************************************************************************
		//! Matrice représentée sous forme d'un tableau de vecteurs lignes (4 * lignes de 4 éléments)
		//**************************************************************************************************
		protected:
		Vector4 m[4];				//!< 4 vecteurs de dimension 4 (vecteurs ligne)

	};

	//*******************************************************************************************************
	// OPERATEURS EXTERNES A LA CLASSE //////////////////////////////////////////////////////////////////////
	//*******************************************************************************************************

	//------------------------------------------------------------
	//! Multiplication d'un vecteur par une matrice
	/*! \param vec Vecteur
			\param mat Matrice
			\return Résultat de la multiplication
	*/ //----------------------------------------------------------
	inline Vector4 operator * (const Vector4& vec,const Matrix44& mat)
	{
		Vector4	result;
		for (unsigned int i=0;i<4;i++)
			result[i]=vec*mat.column(i);
		return result;
	}


}

#endif
