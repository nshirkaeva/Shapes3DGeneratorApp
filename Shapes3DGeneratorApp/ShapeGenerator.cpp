#include "ShapeGenerator.h"

bool ShapeGenerator::generate( const size_t& nShapes, const double& minRange, const double& maxRange )
{
  if ( ( minRange < 0. || maxRange < eps ) || minRange >= maxRange )  // ���� �������� ��������� ������ ����
    return false; // ������ �� ������

  udd = decltype( udd ){ minRange, maxRange }; // ������ ��������� ����

  for ( size_t i = 0; i < nShapes; ++i )
    vShapes.emplace_back( random_shape() );

  return true;
}

PShape ShapeGenerator::circle()
{   // ����� ���������� � ��������� � ������������ ������ ������ ������ Circle3D
    // � ���������� ����� ��������� �� ������� �����
  double radius{};
  while ( radius < eps )    // ���������, ��� �� ������ ��� �� ������� ���������
    radius = std::abs( udd( rd ) ); // � > 0

  return std::make_shared<Circle3D>( Point3D{ udd( rd ), udd( rd ) }, radius );
}

PShape ShapeGenerator::ellipse()
{   // ����� ���������� � ��������� � ������������ ������ ������ ������ Ellipse3D
    // � ���������� ����� ��������� �� ������� �����
  double radius_x = 0.;
  while ( radius_x < eps )  // ���������, ��� �� ������ ������ ��� �� ������� ���������
    radius_x = std::abs( udd( rd ) );   // � > 0

  double radius_y = 0;
  while ( radius_y < eps )  // ���������, ��� �� ������ ������ ��� �� ������� ���������
    radius_y = std::abs( udd( rd ) );   // � > 0

  return std::make_shared<Ellipse3D>( Point3D{ udd( rd ), udd( rd ) }, radius_x, radius_y );
}

PShape ShapeGenerator::helix()
{   // ����� ���������� � ��������� � ������������ ������ ������ ������ Helix3D
    // � ���������� ����� ��������� �� ������� �����
  double radius = 0.;
  while ( radius < eps )    // ���������, ��� �� ������ ��� �� ������� ���������
    radius = std::abs( udd( rd ) ); // � > 0

  double step = 0.;
  while ( std::abs( step ) < eps )    // ���������, ��� �� ��� ��� �� ������� ���������
    step = udd( rd );

  return std::make_shared<Helix3D>( Point3D{ udd( rd ), udd( rd ), udd( rd ) }, radius, step );
}

PShape ShapeGenerator::random_shape()
{   // ����� ���������� ��������� ������ �� ���������� ������
  return usd( rd ) == circle_t ? circle() : usd( rd ) == ellipse_t ? ellipse() : helix();
}

