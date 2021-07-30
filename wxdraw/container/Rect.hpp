#pragma once

namespace wxdraw::container {
/**
   矩形範囲
*/
class Rect {
 public:
  glm::dvec2 pos;
  glm::dvec2 size;

 public:
  Rect() = default;
  Rect(const glm::dvec2& pos, const glm::dvec2& size) : pos(pos), size(size) {}
  ~Rect() = default;

  bool isContain(const glm::dvec2& pos) const;
};
}
