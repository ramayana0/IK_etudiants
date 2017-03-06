#ifndef _Math_Vector_H
#define _Math_Vector_H

#include <math.h>
#include <iostream>
#include <Math/Object.h>

namespace Math
{
  /** \brief Classe de gestion de Vecteurs en 3D */
  class Vector3 : public Object
  {
  protected:
    /* \brief Data representing the vector */
    float m_vector[3] ;

  public:
    Vector3(const float x, const float y, const float z)
    {
      m_vector[0] = x ;
      m_vector[1] = y ;
      m_vector[2] = z ;
    }

    /** \brief Default constructor */
    Vector3() {}

    /** \brief Copy constructor */
    Vector3(Vector3 const & v)
    {
      for(int cpt=0 ; cpt<3 ; cpt++)
			{
				m_vector[cpt] = v.m_vector[cpt] ; 
			}
    }

    /** \brief Coordinate accessor */
    const float & operator[] (int index) const
    { 
			return m_vector[index] ; 
		}

    /** \brief Coordinate accessor */
    float & operator[] (int index) 
    {
			return m_vector[index] ; 
		}

    /** \brief Vector addition */
    Vector3 operator+ (Vector3 const & v) const
    {
      Vector3 result ;
      for(int cpt=0 ; cpt<3 ; cpt++)
	{ result[cpt] = m_vector[cpt]+v.m_vector[cpt] ;	}
      return result ;
    }

    /** \brief Vector soustraction */
    Vector3 operator- (Vector3 const & v) const
    {
      Vector3 result ;
      for(int cpt=0 ; cpt<3 ; cpt++)
			{ 
				result[cpt] = m_vector[cpt]-v.m_vector[cpt] ;	
			}
      return result ;
    }

    /** \brief Negation */
    Vector3 operator- () const
    {
      Vector3 result ;
      for(int cpt=0 ; cpt<3 ; cpt++)
			{
				result[cpt] = -m_vector[cpt] ;	
			}
      return result ;
    }

    /** \brief Scalar product */
    float operator * (Vector3 const & v) const
    {
      float result ;
      result = m_vector[0]*v.m_vector[0] ;
      for(int cpt=1 ; cpt<3 ; cpt++)
			{
				result = result + m_vector[cpt]*v.m_vector[cpt] ; 
			}
      return result ;
    }

    /** \brief Scalar multiplication */
    Vector3 operator* (float const & v) const
    {
      Vector3 result ;
      for(int cpt=0 ; cpt<3 ; cpt++)
			{
				result[cpt] = m_vector[cpt]*v ;	
			}
      return result ;			
    }


    /** \brief Scalar division */
    Vector3 operator/ (float const & v) const
    {
      Vector3 result ;
      for(int cpt=0 ; cpt<3 ; cpt++)
			{
				result[cpt] = m_vector[cpt]/v ;	
			}
      return result ;			
    }

    /** \brief Cross product */
    Vector3 operator^(Vector3 const & v) const
    {
      Vector3 result ;
      result[0] = m_vector[1]*v[2]-m_vector[2]*v[1] ;
      result[1] = m_vector[2]*v[0]-m_vector[0]*v[2] ;
      result[2] = m_vector[0]*v[1]-m_vector[1]*v[0] ;
      return result ;
    }

    /** \brief Vector norm^2 */
    float norm2() const
    {
      return (*this)*(*this) ;
    }

    /** \brief Vector norm */
    float norm() const
    { 
			return pow(this->norm2(),0.5f) ; 
		}

    /** \brief Affectation */
    Vector3 & operator= (Vector3 const & v) 
    {
      for(int cpt=0 ; cpt<3 ; cpt++)
			{
			  m_vector[cpt]=v.m_vector[cpt] ;
			}
      return (*this) ;
    }

    /** \brief Fills the vector with a scalar */
    Vector3 & operator= (float const & s)
    {
      for(int cpt=0 ; cpt<3 ; cpt++)
			{
				m_vector[cpt] = s ; 
			}
      return *this ;
    }

    /** \brief Vector pseudo inverse for solving equations. */ 
    Vector3 inv() const
    { 
			return (*this)/norm2() ; 
		}

    int size() const
    { 
			return 3 ; 
		}
  } ;

  /** \brief Output operator */
	inline std::ostream & operator<< (std::ostream & out, Vector3 const & v)
	{
		for(int cpt=0 ; cpt<3 ; cpt++)
		{
			out<<v[cpt] ;
			if(cpt!=2)
			{
				out<<", " ;
			}
		}
		return out ;
	}
}

#endif
