#include "wxdraw/gui/Renderer.hpp"

namespace wxdraw::gui {
/**
   コンストラクタ
   @param dc デバイスコンテキスト
*/
Renderer::Renderer(wxDC& dc)
  : context_(wxGraphicsContext::CreateFromUnknownDC(dc)), 
    matrix_(1.0)
{
}
/**
   行列をセットする
   @param matrix 行列
   @return 自分自身
*/
Renderer& Renderer::setMatrix(const glm::dmat3& matrix) {
  context_->SetTransform(context_->CreateMatrix(matrix[0][0], matrix[0][1], 
                                                matrix[1][0], matrix[1][1], 
                                                matrix[2][0], matrix[2][1]));
  matrix_ = matrix;
  return *this;
}
/**
   行列を積む
   @param matrix 行列
   @return 元の行列
*/
glm::dmat3 Renderer::pushMatrix(const glm::dmat3& matrix) {
  auto m = matrix_;
  setMatrix(matrix * matrix_);
  return m;
}
/**
 */
void Renderer::pushBrush(const wxBrush& brush) {
  auto graphicsBrush = context_->CreateBrush(brush);
  brushes_.push(graphicsBrush);
  context_->SetBrush(graphicsBrush);
}
/**
 */
void Renderer::popBrush() {
  context_->SetBrush(brushes_.top());
  brushes_.pop();
}
}
