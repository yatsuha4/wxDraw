#include "wxdraw/container/Rect.hpp"
#include "wxdraw/gui/Renderer.hpp"
#include "wxdraw/palette/Brush.hpp"
#include "wxdraw/palette/Color.hpp"
#include "wxdraw/palette/Gradient.hpp"
#include "wxdraw/palette/Pen.hpp"
#include "wxdraw/property/Choice.hpp"

namespace wxdraw::gui {
/**
   コンストラクタ
   @param dc デバイスコンテキスト
   @param viewMatrix ビュー行列
*/
Renderer::Renderer(wxDC& dc, const glm::dmat3& viewMatrix)
  : Renderer(wxGraphicsContext::CreateFromUnknownDC(dc), viewMatrix)
{
  pushPen(*wxBLACK_PEN);
  pushBrush(*wxWHITE_BRUSH);
}
/**
   コンストラクタ
   @param image 画像
   @param viewMatrix ビュー行列
*/
Renderer::Renderer(wxImage& image, const glm::dmat3& viewMatrix)
  : Renderer(wxGraphicsContext::Create(image), viewMatrix)
{
}
/**
   行列をセットする
   @param matrix 行列
*/
void Renderer::setMatrix(const glm::dmat3& matrix) {
  matrix_ = viewMatrix_ * matrix;
  context_->SetTransform(createMatrix(matrix_));
}
/**
 */
glm::dvec2 Renderer::getScale() const {
  return glm::dvec2(glm::length(matrix_[0]), glm::length(matrix_[1]));
}
/**
 */
void Renderer::pushBrush(const Brush& brush, const Rect& rect) {
  if(auto color = std::dynamic_pointer_cast<Color>(brush.getColor())) {
    pushBrush(wxBrush(color->getColor()));
  }
  else if(auto gradient = std::dynamic_pointer_cast<Gradient>(brush.getColor())) {
    switch(gradient->getGradientType().getIndex()) {
    case Choice::GradientType::RADIAL:
      pushBrush(context_->CreateRadialGradientBrush(rect.pos.x, 
                                                    rect.pos.y, 
                                                    rect.pos.x + rect.size.x, 
                                                    rect.pos.y + rect.size.y, 
                                                    gradient->getRadius(), 
                                                    *gradient));
      break;
    default:
      pushBrush(context_->CreateLinearGradientBrush(rect.pos.x, 
                                                    rect.pos.y, 
                                                    rect.pos.x + rect.size.x, 
                                                    rect.pos.y + rect.size.y, 
                                                    *gradient));
      break;
    }
  }
  else {
    pushBrush(*wxTRANSPARENT_BRUSH);
  }
}
/**
 */
void Renderer::popBrush() {
  brushes_.pop();
  context_->SetBrush(brushes_.top());
}
/**
 */
void Renderer::pushPen(const Pen& pen, const Rect& rect) {
  wxGraphicsPenInfo info;
  if(auto color = std::dynamic_pointer_cast<Color>(pen.getColor())) {
    info.Colour(color->getColor());
  }
  else if(auto gradient = std::dynamic_pointer_cast<Gradient>(pen.getColor())) {
  }
  else {
    info.Colour(wxTransparentColor);
  }
  info.Width(pen.getWidth());
  switch(pen.getStyle().getIndex()) {
  case Choice::PenStyle::SOLID:
    info.Style(wxPENSTYLE_SOLID);
    break;
  case Choice::PenStyle::DOT:
    info.Style(wxPENSTYLE_DOT);
    break;
  case Choice::PenStyle::LONG_DASH:
    info.Style(wxPENSTYLE_LONG_DASH);
    break;
  case Choice::PenStyle::SHORT_DASH:
    info.Style(wxPENSTYLE_SHORT_DASH);
    break;
  case Choice::PenStyle::DOT_DASH:
    info.Style(wxPENSTYLE_DOT_DASH);
    break;
  case Choice::PenStyle::BDIAGONAL_HATCH:
    info.Style(wxPENSTYLE_BDIAGONAL_HATCH);
    break;
  case Choice::PenStyle::CROSSDIAG_HATCH:
    info.Style(wxPENSTYLE_CROSSDIAG_HATCH);
    break;
  case Choice::PenStyle::FDIAGONAL_HATCH:
    info.Style(wxPENSTYLE_FDIAGONAL_HATCH);
    break;
  case Choice::PenStyle::CROSS_HATCH:
    info.Style(wxPENSTYLE_CROSS_HATCH);
    break;
  case Choice::PenStyle::HORIZONTAL_HATCH:
    info.Style(wxPENSTYLE_HORIZONTAL_HATCH);
    break;
  case Choice::PenStyle::VERTICAL_HATCH:
    info.Style(wxPENSTYLE_VERTICAL_HATCH);
    break;
  default:
    break;
  }
  pushPen(context_->CreatePen(info));
}
/**
 */
void Renderer::pushPen(const wxPen& pen) {
  pushPen(context_->CreatePen(pen));
}
/**
 */
void Renderer::popPen() {
  pens_.pop();
  context_->SetPen(pens_.top());
}
/**
   コンストラクタ
   @param context コンテキスト
   @param viewMatrix ビュー行列
*/
Renderer::Renderer(wxGraphicsContext* context, const glm::dmat3& viewMatrix)
  : context_(context), 
    viewMatrix_(viewMatrix)
{
}
/**
 */
wxGraphicsMatrix Renderer::createMatrix(const glm::dmat3& matrix) const {
  return context_->CreateMatrix(matrix_[0][0], matrix_[0][1], 
                                matrix_[1][0], matrix_[1][1], 
                                matrix_[2][0], matrix_[2][1]);
}
/**
 */
void Renderer::pushBrush(const wxBrush& brush) {
  pushBrush(context_->CreateBrush(brush));
}
/**
 */
void Renderer::pushBrush(const wxGraphicsBrush& brush) {
  brushes_.push(brush);
  context_->SetBrush(brush);
}
/**
 */
void Renderer::pushPen(const wxGraphicsPen& pen) {
  pens_.push(pen);
  context_->SetPen(pen);
}
}
