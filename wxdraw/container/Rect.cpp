#include "wxdraw/container/Rect.hpp"

namespace wxdraw::container {
/**
 */
bool Rect::isContain(const glm::dvec2& pos) const {
  return (this->pos.x <= pos.x && pos.x < this->pos.x + this->size.x && 
          this->pos.y <= pos.y && pos.y < this->pos.y + this->size.y);
}
}
