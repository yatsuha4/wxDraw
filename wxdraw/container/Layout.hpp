#pragma once

namespace wxdraw::container {
/**
   レイアウト
*/
class Layout {
 public:
  glm::dvec2 alignment;
  glm::dvec2 offset;

 public:
  Layout() = default;
  Layout(const glm::dvec2& alignment, const glm::dvec2& offset)
    : alignment(alignment), 
      offset(offset)
  {}
  Layout(const Layout& src) = default;
  ~Layout() = default;
};
}
