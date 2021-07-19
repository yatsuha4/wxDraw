#include "wxdraw/container/Rect.hpp"
#include "wxdraw/gui/Renderer.hpp"
#include "wxdraw/palette/Brush.hpp"
#include "wxdraw/palette/Color.hpp"
#include "wxdraw/palette/Gradient.hpp"

namespace wxdraw::gui {
/**
   コンストラクタ
   @param dc デバイスコンテキスト
   @param viewMatrix ビュー行列
*/
Renderer::Renderer(wxDC& dc, const glm::dmat3& viewMatrix)
  : Renderer(wxGraphicsContext::CreateFromUnknownDC(dc), viewMatrix)
{
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
    pushBrush(context_->CreateLinearGradientBrush(rect.pos.x, 
                                                  rect.pos.y, 
                                                  rect.pos.x + rect.size.x, 
                                                  rect.pos.y + rect.size.y, 
                                                  *gradient));
  }
  else {
    pushBrush(*wxTRANSPARENT_BRUSH);
  }
}
/**
 */
void Renderer::popBrush() {
  context_->SetBrush(brushes_.top());
  brushes_.pop();
}
/**
 */
void Renderer::pushPen(const wxGraphicsPenInfo& info) {
  auto pen = context_->CreatePen(info);
  pens_.push(pen);
  context_->SetPen(pen);
}
/**
 */
void Renderer::popPen() {
  context_->SetPen(pens_.top());
  pens_.pop();
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
}
