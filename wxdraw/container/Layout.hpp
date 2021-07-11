#pragma once

namespace wxdraw::container {
/**
   レイアウト
*/
class Layout {
 public:
  glm::dvec2 relative;
  glm::dvec2 absolute;

 public:
  Layout() = default;
  Layout(const glm::dvec2& relative, const glm::dvec2& absolute)
    : relative(relative), 
      absolute(absolute)
  {}
  Layout(const Layout& src) = default;
  ~Layout() = default;
};
}
