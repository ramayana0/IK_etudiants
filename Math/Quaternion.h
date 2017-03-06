#ifndef _Math_Quaternion_H
#define _Math_Quaternion_H

#include <Math/Vector3.h>
#include <Math/Object.h>

namespace Math
{
  /** \brief Quaternion handling */
  class Quaternion : public Object
  {
  protected:
    float   m_s ;
    Vector3 m_v ;

    float m_angle ;
    Vector3 m_axis ;

  public:
    /** \brief Default constructor (DO NOT initialize explicitly the members) */
    Quaternion()
    {}

    /** \brief Constructor with vector/angle arguments */
    Quaternion(Vector3 const & v, float const & angle)
      : m_s(cos(angle/2.0)), m_v(v*sin(angle/2.0)), m_angle(angle), m_axis(v)
    {}
	
    /** \brief Constructor with a point */
    Quaternion(Vector3 const & v)
      : m_s(0.0), m_v(v), m_angle(0.0), m_axis(v) 
    {}

    /** \brief Copy constructor */
    Quaternion(Quaternion const & q)
      : m_s(q.m_s), m_v(q.m_v), m_angle(q.m_angle), m_axis(q.m_axis)
    {}

    /** \brief Constructor with quaternion data arguments */
    Quaternion(float const & s, Vector3 const & v)
      : m_s(s), m_v(v)
    {}

    /** \brief Returns the rotation angle */
    float getAngle() const
    { return m_angle ; }

    /** \brief Returns the axis of rotation. */
    Vector3 const & getAxis() const
    { return m_axis ; }

    /** \brief Modifies the quaternion
	\param v : rotation axis
	\param angle : rotation angle
    */
    void setAxisAngle(Vector3 const & v, float angle)
    {
      m_s = cos(angle/2.0) ;
      m_v = v*sin(angle/2.0) ;
      m_angle = angle ;
      m_axis  = v ;
    }

   /** \brief Modifies the quaternion
	\param angle : rotation angle
    */
    void setAngle(float angle)
    {
      m_s = cos(angle/2.0) ;
      m_v = m_axis*sin(angle/2.0) ;
      m_angle = angle ;
    }

    float & s()
    { return m_s ; }

    float s() const
    { return m_s ; }

    Vector3 v() const
    { return m_v ; }

    Vector3 & v()
    { return m_v ; }

    Quaternion operator+ (Quaternion const & q) const
    {	return Quaternion(m_s+q.m_s, m_v+q.m_v) ; }

    Quaternion operator- (Quaternion const & q) const
    {	return Quaternion(m_s+q.m_s, m_v+q.m_v) ; }
 
    Quaternion operator* (Quaternion const & q) const
    {
      return Quaternion(m_s*q.m_s-m_v*q.m_v, q.m_v*m_s+m_v*q.m_s+(m_v^q.m_v)) ; 
    }

    Quaternion operator* (float const & v) const
    {	return Quaternion(m_s*v, m_v*v) ; }

    Quaternion operator/ (float const & v) const
    {	return Quaternion(m_s/v, m_v/v) ; }

    Quaternion operator- () const
    {   return Quaternion(-m_s, -m_v) ; }

    /** \brief Inverse of the quaternion */
    Quaternion inv() const
    {   return Quaternion(m_s, -m_v) ; }

    /** \brief Square of the quaternion norm */
    float norm2() const
    {   return m_s*m_s+m_v.norm2() ; }

    /** \brief Norm of the quaternion */
    float norm() const
    {	return sqrt(this->norm2()) ; }

    Quaternion & operator= (Quaternion const & q)
    {
      m_s = q.m_s ;
      m_v = q.m_v ;
      return (*this) ;
    }

    /** \brief Normalize the current quaternion */
    Quaternion & normalize() 
    {
      (*this) = (*this)/this->norm() ;
      return *this ;
    }

    /** \brief Computes rotation of the quaternion vector */
    Quaternion rotate(Quaternion const & q)
    {
      return (*this)*q*this->inv() ;
    }
  };
} 

#endif
