#pragma once

#ifdef SHAPE3D_EXPORTS
#define SHAPE3D_API __declspec(dllexport)
#else
#define SHAPE3D_API __declspec(dllimport)
#endif

#include <iostream>

constexpr double eps = 1e-6;

// points in 3D-space
  class Point3D
  {
  public:
    double x{}, y{}, z{};

    friend std::ostream& operator<<( std::ostream& out, const Point3D& p )
    {
      return out << "P{ " << p.x << ", " << p.y << ", " << p.z << " }";
    }
  };

//vector in 3D-space
  class Vector3D
  {
  public:
    double x{}, y{}, z{};

    friend std::ostream& operator<<( std::ostream& out, const Vector3D& p )
    {
      return out << "V{ " << p.x << ", " << p.y << ", " << p.z << " }";
    }
  };

/* Interface class */
  class Shape3D
  {
  public:
    Shape3D( const Point3D& center ) : c( center ) {}
    virtual ~Shape3D() {}

    virtual Point3D GetPoint( const double& t ) const = 0;
    virtual Vector3D GetVector( const double& t ) const = 0;

  protected:
    Point3D c; //center of the shape
  };


  class Circle3D : public Shape3D
  {
  public:

    /**
    This class calculates circle parameters (P, V) in X0Y-flat
    \param
    center - 3d-point of the center shape
    radius - radius of the circle
     */
    Circle3D( const Point3D& center, const double& radius ) : Shape3D( center ), radius( radius ) {}

    virtual ~Circle3D() {}

    /** \details
    \returns
    radius value
     */
    inline double GetRadius() const { return radius; }

    /** \details
    \returns
    3D - point value of the circle at a given parameter t
    \param
    constant reference to the pàrametric value
     */
    SHAPE3D_API virtual Point3D GetPoint( const double& t ) const override;

    /** \details
    \returns
    3D - vector(first derivative) value of the circle at a given parameter t
    \param
    constant reference to the  pàrametric value
     */
    SHAPE3D_API virtual Vector3D GetVector( const double& t ) const override;

  private:
    const double radius;
  };

  class Ellipse3D : public Shape3D
  {
  public:

    /**
    This class calculates ellipse parameters (P, V) in X0Y-flat
    \param
    center - 3d-point of the center shape
    radius_x - X-axis radius
    radius_y - Y-axis radius
     */
    Ellipse3D( const Point3D& center, const double& radius_x, const double& radius_y )
      : Shape3D( center ), radiusX( radius_x ), radiusY( radius_y ) {}

    virtual ~Ellipse3D() {}

    /** \details
    \returns
    3D - point value of the ellipse at a given parameter t
    \param
    constant reference to the pàrametric value
    */
    SHAPE3D_API virtual Point3D GetPoint( const double& t ) const override;

    /** \details
    \returns
    3D - vector(first derivative) value of the ellipse at a given parameter t
    \param
    constant reference to the  pàrametric value
     */
    SHAPE3D_API virtual Vector3D GetVector( const double& t ) const override;

  private:
    const double radiusX;
    const double radiusY;
  };

  class Helix3D : public Shape3D
  {
  public:

    /**
    This class calculates helix parameters (P, V) in X0Y-flat
    \param
    center - 3d-point of the center shape
    radius - radius of the shape
    step_z - Z-axis value
     */
    Helix3D( const Point3D& center, const double& radius, const double& step_z )
      : Shape3D( center ), radius( radius ), step( step_z ) {}

    virtual ~Helix3D() {}

    /** \details
    \returns
    3D - point value of the helix at a given parameter t
    \param
    constant reference to the pàrametric value
     */
    SHAPE3D_API virtual Point3D GetPoint( const double& t ) const override;

    /** \details
    \returns
    3D - vector(first derivative) value of the ellipse at a given parameter t
    \param
    constant reference to the  pàrametric value
     */
    SHAPE3D_API virtual Vector3D GetVector( const double& t ) const override;

  private:
    const double radius;
    const double step;
  };
