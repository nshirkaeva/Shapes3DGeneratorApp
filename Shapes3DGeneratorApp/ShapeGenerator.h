#pragma once
#include <random>
#include <memory>
#include "Shape3D.h"

  using PShape = std::shared_ptr<Shape3D>; // псевдоним типа - умный указатель на базовый класс

  /**
  This class generate 3d-objects - derived Shape3D
   */
  class ShapeGenerator 
  {
  public:

    /** \details
    \returns
    true if generation is success otherwise false
    \param
    nShapes- count of the shapes
    minRange - the minimum values of the parameters of the shapes
    maxRange - the maximum values of the parameters of the shapes
     */
    bool generate( const size_t& nShapes, const double& minRange, const double& maxRange );

    /** \details
    \returns
    vector of pointers to objects of the base Shape3D-class
    */
    std::vector<PShape> GetShapes() { return vShapes; }

  private:
    enum shape_t  // типы генерируемых объектов
    {
      circle_t,
      ellipse_t,
      helix_t
    };

    PShape circle();
    PShape ellipse();
    PShape helix();
    PShape random_shape();

    std::random_device rd{};
    std::vector<PShape> vShapes{};
    std::uniform_real_distribution<double> udd{ -1, 1 };    // генератор случайных вещественных чисел(ГСВЧ)
  std::uniform_int_distribution<> usd{ circle_t, helix_t };   // генератор случайных типов объектов
};


