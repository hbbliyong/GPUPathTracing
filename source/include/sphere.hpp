#pragma once

#include "shape.hpp"


struct Sphere:public Shape
{
  glm::vec3 center; // Sphere center
  float radius;     // Sphere radius
  
  Sphere(const glm::vec3& cen, float r) : center(cen), radius(r) {}
  virtual std::optional<HitInfo> intersect(const Ray &ray,float t_min,float t_max) const override;
};
