#include "wxdraw/container/Transform.hpp"

namespace wxdraw::container {
/**
   コンストラクタ
*/
Transform::Transform(const glm::dvec2& size, const glm::dvec2& offset, double zoom)
  : matrix(glm::scale(glm::translate(glm::dmat3(1.0), size * 0.5 + offset), 
                      glm::dvec2(zoom))), 
    rect(size / zoom), 
    scale(1.0)
{}
}
