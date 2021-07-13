#include "wxdraw/gui/Renderer.hpp"

namespace wxdraw::gui {
/**
   コンストラクタ
   @param dc デバイスコンテキスト
*/
Renderer::Renderer(wxDC& dc, const glm::dmat3& viewMatrix)
  : context_(wxGraphicsContext::CreateFromUnknownDC(dc)), 
    viewMatrix_(viewMatrix)
{
}
/**
   行列をセットする
   @param matrix 行列
*/
void Renderer::setMatrix(const glm::dmat3& matrix) {
  auto m = viewMatrix_ * matrix;
  context_->SetTransform(context_->CreateMatrix(m[0][0], m[0][1], 
                                                m[1][0], m[1][1], 
                                                m[2][0], m[2][1]));
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
}
