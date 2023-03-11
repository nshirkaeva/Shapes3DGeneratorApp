#include "ShapeGenerator.h"

bool ShapeGenerator::generate( const size_t& nShapes, const double& minRange, const double& maxRange )
{
  if ( ( minRange < 0. || maxRange < eps ) || minRange >= maxRange )  // если значения диапазона меньше нуля
    return false; // ничего не меняем

  udd = decltype( udd ){ minRange, maxRange }; // меняем параметры ГСВЧ

  for ( size_t i = 0; i < nShapes; ++i )
    vShapes.emplace_back( random_shape() );

  return true;
}

PShape ShapeGenerator::circle()
{   // метод генерирует и размещает в динамической памяти объект класса Circle3D
    // и возвращает умный указатель на базовый класс
  double radius{};
  while ( radius < eps )    // проверяем, что бы радиус был не слишком маленьким
    radius = std::abs( udd( rd ) ); // и > 0

  return std::make_shared<Circle3D>( Point3D{ udd( rd ), udd( rd ) }, radius );
}

PShape ShapeGenerator::ellipse()
{   // метод генерирует и размещает в динамической памяти объект класса Ellipse3D
    // и возвращает умный указатель на базовый класс
  double radius_x = 0.;
  while ( radius_x < eps )  // проверяем, что бы первый радиус был не слишком маленьким
    radius_x = std::abs( udd( rd ) );   // и > 0

  double radius_y = 0;
  while ( radius_y < eps )  // проверяем, что бы второй радиус был не слишком маленьким
    radius_y = std::abs( udd( rd ) );   // и > 0

  return std::make_shared<Ellipse3D>( Point3D{ udd( rd ), udd( rd ) }, radius_x, radius_y );
}

PShape ShapeGenerator::helix()
{   // метод генерирует и размещает в динамической памяти объект класса Helix3D
    // и возвращает умный указатель на базовый класс
  double radius = 0.;
  while ( radius < eps )    // проверяем, что бы радиус был не слишком маленьким
    radius = std::abs( udd( rd ) ); // и > 0

  double step = 0.;
  while ( std::abs( step ) < eps )    // проверяем, что бы шаг был не слишком маленьким
    step = udd( rd );

  return std::make_shared<Helix3D>( Point3D{ udd( rd ), udd( rd ), udd( rd ) }, radius, step );
}

PShape ShapeGenerator::random_shape()
{   // метод генерирует случайную фигуру из доступного набора
  return usd( rd ) == circle_t ? circle() : usd( rd ) == ellipse_t ? ellipse() : helix();
}

