#pragma once

namespace wxdraw::gui {
/**
   レンダラー
*/
class Renderer {
 private:
  std::unique_ptr<wxGraphicsContext> context_;
  glm::dmat3 viewMatrix_;
  glm::dmat3 matrix_;
  std::stack<wxGraphicsBrush> brushes_;
  std::stack<wxGraphicsPen> pens_;

 public:
  Renderer(wxDC& dc, const glm::dmat3& viewMatrix);
  Renderer(wxImage& image, const glm::dmat3& viewMatrix);
  ~Renderer() = default;

  wxGraphicsContext& getContext() const {
    return *context_;
  }

  WXDRAW_GETTER(ViewMatrix, viewMatrix_);
  WXDRAW_GETTER(Matrix, matrix_);
  void setMatrix(const glm::dmat3& matrix);
  glm::dvec2 getScale() const;

  void pushBrush(const Brush& brush);
  void popBrush();

  void pushPen(const wxGraphicsPenInfo& info);
  void popPen();

 protected:
  Renderer(wxGraphicsContext* context, const glm::dmat3& viewMatrix);

 private:
  wxGraphicsMatrix createMatrix(const glm::dmat3& matrix) const;

  void pushBrush(const wxBrush& brush);
  void pushBrush(const wxGraphicsBrush& brush);
};
}
