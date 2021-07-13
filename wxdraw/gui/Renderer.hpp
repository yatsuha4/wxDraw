#pragma once

namespace wxdraw::gui {
/**
   レンダラー
*/
class Renderer {
 private:
  std::shared_ptr<wxGraphicsContext> context_;
  glm::dmat3 viewMatrix_;
  std::stack<wxGraphicsBrush> brushes_;
  std::stack<wxGraphicsPen> pens_;

 public:
  Renderer(wxDC& dc, const glm::dmat3& viewMatrix);
  ~Renderer() = default;

  wxGraphicsContext& getContext() const {
    return *context_;
  }

  WXDRAW_GETTER(ViewMatrix, viewMatrix_);
  void setMatrix(const glm::dmat3& matrix);

  void pushBrush(const wxBrush& brush);
  void popBrush();

  void pushPen(const wxGraphicsPenInfo& info);
  void popPen();
};
}
