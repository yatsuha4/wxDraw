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
  Transform(const Transform& src) = default;
  ~Transform() = default;
};
}
