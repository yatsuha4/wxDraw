#pragma once

#include "wxdraw/container/Rect.hpp"

namespace wxdraw::container {
/**
 */
class Transform {
 public:
  glm::dmat3 matrix;
  Rect rect;

 public:
  Transform() = default;
  Transform(const glm::dvec2& size, 
            const glm::dvec2& offset = glm::dvec2(0.0), 
            double zoom = 1.0);
  Transform(const Transform& src) = default;
  ~Transform() = default;
};
}
