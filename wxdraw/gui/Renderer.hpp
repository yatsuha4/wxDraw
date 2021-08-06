﻿#pragma once

namespace wxdraw::gui {
/**
   レンダラー
*/
class Renderer {
 public:
  enum Composition {
    CLEAR, 
    SOURCE, 
    OVER, 
    IN, 
    OUT, 
    ATOP, 
    DEST, 
    DEST_OVER, 
    DEST_IN, 
    DEST_OUT, 
    DEST_ATOP, 
    XOR, 
    ADD
  };

 private:
  std::unique_ptr<wxGraphicsContext> context_;
  std::stack<wxGraphicsBrush> brushes_;
  std::stack<wxGraphicsPen> pens_;
  std::stack<wxCompositionMode> compositionStack_;

 public:
  Renderer(wxDC& dc);
  Renderer(wxImage& image);
  ~Renderer() = default;

  wxGraphicsContext& getContext() const {
    return *context_;
  }

  void setMatrix(const glm::dmat3& matrix);

  void pushBrush(const Brush& brush, const Rect& rect);
  void popBrush();

  void pushPen(const Pen& pen, const Rect& rect);
  void pushPen(const wxPen& pen);
  void popPen();

  void pushComposition(Composition composition);
  void popComposition();

 protected:
  Renderer(wxGraphicsContext* context);

 private:
  wxGraphicsMatrix createMatrix(const glm::dmat3& matrix) const;

  void pushBrush(const wxBrush& brush);
  void pushBrush(const wxGraphicsBrush& brush);

  void pushPen(const wxGraphicsPen& pen);

  void pushComposition(wxCompositionMode composition);
};
}
