#include <iostream>
#include <vector>
#include <random>
#include "Shape3D.h"
#include "ShapeGenerator.h"

#define M_PI 3.14159265358979323846

using PCircle = std::shared_ptr<Circle3D>;  // псевдоним типа - умный указатель на Circle3D

bool condition( PCircle const& lhs, PCircle const& rhs ) { return lhs->GetRadius() < rhs->GetRadius(); }

int main()
{
  std::cout << "Enter count of shapes :";
  size_t nShapes;
  std::cin >> nShapes;

  std::cout << "Enter min and max range for random numbers :";
  double minRange, maxRange;
  std::cin >> minRange >> maxRange;

  //STEP 2 - Populate a container (e.g. vector or list) of objects of these types created in random manner with
  //random parameters
  ShapeGenerator gen;
  auto res = gen.generate( nShapes, minRange, maxRange ); // start the generator
  if ( !res )
  {
    std::cout << "\nInput data error " << std::endl;
    system( "pause" );
    return 0;
  }

  auto vShapes = gen.GetShapes();

  std::vector<PCircle> circle_vec;
  auto radius_sum = 0.;
  auto t = M_PI / 4.;

  for ( auto& ps : vShapes )
  {
    const std::type_info& ti = typeid( *ps );

    //STEP 3 - Print coordinates of points and derivatives of all curves in the container at t=PI/4
    std::cout << ti.name() << ' ' << ps->GetPoint( t ) << ' ' << ps->GetVector( t ) << std::endl;

    if ( ti == typeid( Circle3D ) ) // if the current object is ptr to Circle3D
    {
      circle_vec.emplace_back( std::dynamic_pointer_cast< Circle3D >( ps ) );
      radius_sum += circle_vec.back()->GetRadius();  // summ radius
      std::cout << "R = " << circle_vec.back()->GetRadius(); //output circle radius
    }
    std::cout << std::endl;
  }

  //STEP 5 - Sort the second container in the ascending order of circlesТ radii.
  std::sort( circle_vec.begin(), circle_vec.end(), condition );

  std::cout << "Sort radius from the smallest to the largest : ";

  for ( auto& pc : circle_vec )
    std::cout << pc->GetRadius() << "  ";

  //STEP 6 - Compute the total sum of radii of all curves in the second container
  std::cout << "\nRadius sum = " << radius_sum << std::endl; //sum all radii

  system( "pause" );
}
