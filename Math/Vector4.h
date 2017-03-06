#ifndef _Math_Vector4_H
#define _Math_Vector4_H

#include <math.h>
#include <iostream>
#include <Math/Object.h>

namespace Math
{
  /** \brief Classe de gestion de Vecteurs en 3D */
  class Vector4 : public Object
  {
  protected:
    /* \brief Data representing the vector */
    float m_vector[4];

  public:
    Vector4(float x, float y, float z, float w)
    {
      m_vector[0] = x ;
      m_vector[1] = y ;
      m_vector[2] = z ;
      m_vector[3] = w ;
    }

    /** \brief Default constructor */
    Vector4() {}

    /** \brief Copy constructor */
    Vector4(Vector4 const & v)
    {
      for(int cpt=0 ; cpt<4 ; cpt++)
			{
				m_vector[cpt] = v.m_vector[cpt] ; 
			}
    }

		void set(const float& f0,const float& f1,const float& f2,const float& f3)
		{
      m_vector[0] = f0;
      m_vector[1] = f1;
      m_vector[2] = f2;
      m_vector[3] = f3;
		}

    /** \brief Coordinate accessor */
    const float & operator[] (int index) const
    { return m_vector[index] ; }

    /** \brief Coordinate accessor */
    float & operator[] (int index) 
    { return m_vector[index] ; }

    /** \brief Vector addition */
    Vector4 operator+ (Vector4 const & v) const
    {
      Vector4 result ;
      for(int cpt=0 ; cpt<4 ; cpt++)
			{
				result[cpt] = m_vector[cpt]+v.m_vector[cpt] ;	
			}
      return result ;
    }

    /** \brief Vector soustraction */
    Vector4 operator- (Vector4 const & v) const
    {
      Vector4 result ;
      for(int cpt=0 ; cpt<4 ; cpt++)
			{
				result[cpt] = m_vector[cpt]-v.m_vector[cpt] ;	
			}
      return result ;
    }

    /** \brief Negation */
    Vector4 operator- () const
    {
      Vector4 result ;
      for(int cpt=0 ; cpt<4 ; cpt++)
			{
				result[cpt] = -m_vector[cpt] ;	
			}
      return result ;
    }

    /** \brief Scalar product */
    float operator * (Vector4 const & v) const
    {
      float result ;
      result = m_vector[0]*v.m_vector[0] ;
      for(int cpt=1 ; cpt<4 ; cpt++)
			{
				result = result + m_vector[cpt]*v.m_vector[cpt] ; 
			}
      return result ;
    }

    /** \brief Scalar multiplication */
    Vector4 operator* (float const & v) const
    {
      Vector4 result ;
      for(int cpt=0 ; cpt<4 ; cpt++)
			{
				result[cpt] = m_vector[cpt]*v ;	
			}
      return result ;			
    }


    /** \brief Scalar division */
    Vector4 operator/ (float const & v) const
    {
      Vector4 result ;
      for(int cpt=0 ; cpt<4 ; cpt++)
			{
				result[cpt] = m_vector[cpt]/v ;	
			}
      return result ;			
    }

    /** \brief Vector norm^2 */
    float norm2() const
    {
      return (*this)*(*this) ;
    }

    /** \brief Vector norm */
    float norm() const
    { return pow(this->norm2(),0.5f) ; }

    /** \brief Affectation */
    Vector4 & operator= (Vector4 const & v) 
    {
      for(int cpt=0 ; cpt<4 ; cpt++)
			{
				m_vector[cpt]=v.m_vector[cpt] ;
			}
      return (*this) ;
    }

    /** \brief Fills the vector with a scalar */
    Vector4 & operator= (float const & s)
    {
      for(int cpt=0 ; cpt<4 ; cpt++)
			{
				m_vector[cpt] = s ; 
			}
				return *this ;
		}

    /** \brief Vector pseudo inverse for solving equations. */ 
    Vector4 inv() const
    {
			return (*this)/norm2() ; 
		}

    int size() const
    {
			return 4 ; 
		}
  } ;

  /** \brief Output operator */
  inline std::ostream & operator<< (std::ostream & out, Vector4 const & v)
  {
    for(int cpt=0 ; cpt<4 ; cpt++)
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
