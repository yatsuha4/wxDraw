#pragma once

namespace wxdraw::gui {
/**
   レンダラー
*/
class Renderer {
 private:
  std::shared_ptr<wxGraphicsContext> context_;
  glm::dmat3 matrix_;

 public:
  Renderer(wxDC& dc);
  Renderer(const Renderer& renderer) = default;
  ~Renderer() = default;

  wxGraphicsContext& getContext() const {
    return *context_;
  }

  Renderer& setMatrix(const glm::dmat3& matrix);
  glm::dmat3 pushMatrix(const glm::dmat3& matrix);
};
}
