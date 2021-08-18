#include "wxdraw/container/Transform.hpp"

namespace wxdraw::container {
/**
   コンストラクタ
*/
Transform::Transform(const glm::dvec2& size, 
                     const glm::dvec2& scale, 
                     const glm::dvec2& offset)
  : matrix(glm::translate(glm::dmat3(1.0), size * 0.5 + offset)), 
    rect(size), 
    scale(scale)
{}
}
