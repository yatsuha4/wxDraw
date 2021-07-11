#include "wxdraw/gui/Canvas.hpp"
#include "wxdraw/gui/MainFrame.hpp"
#include "wxdraw/gui/Renderer.hpp"
#include "wxdraw/node/ProjectNode.hpp"

namespace wxdraw::gui {
/**
   コンストラクタ
   @param parent 親
   @param mainFrame メインフレーム
*/
Canvas::Canvas(wxWindow* parent, MainFrame* mainFrame)
  : super(parent), 
    mainFrame_(mainFrame), 
    offset_(0.0), 
    zoom_(1.0)
{
  SetDoubleBuffered(true);
  Bind(wxEVT_RIGHT_DOWN, &Canvas::onRightDown, this);
  Bind(wxEVT_MOTION, &Canvas::onMotion, this);
  Bind(wxEVT_MOUSEWHEEL, &Canvas::onMouseWheel, this);
}
/**
   描画
*/
void Canvas::OnDraw(wxDC& dc) {
  super::OnDraw(dc);
  if(auto project = Node::GetParent<ProjectNode>(mainFrame_->getSelectNode())) {
    auto size = GetSize();
    glm::dmat3 m(1.0);
    m = glm::translate(m, glm::dvec2(size.x * 0.5, size.y * 0.5) + offset_);
    m = glm::scale(m, glm::dvec2(zoom_));
    Renderer renderer(dc, m);
    project->render(renderer);
  }
  /*
  std::unique_ptr<wxGraphicsContext> gc(wxGraphicsContext::CreateFromUnknownDC(dc));
  if(gc) {
    gc->SetPen(*wxRED_PEN);
    auto path = gc->CreatePath();
    path.AddCircle(50.0, 50.0, 50.0);
    gc->StrokePath(path);
  }
  */
}
/**
 */
void Canvas::onRightDown(wxMouseEvent& event) {
  mousePos_ = event.GetPosition();
}
/**
 */
void Canvas::onMotion(wxMouseEvent& event) {
  auto pos = event.GetPosition();
  if(event.RightIsDown()) {
    offset_ += glm::dvec2(pos.x - mousePos_.x, pos.y - mousePos_.y);
    Refresh();
  }
  mousePos_ = pos;
}
/**
 */
void Canvas::onMouseWheel(wxMouseEvent& event) {
  if(event.GetWheelRotation() < 0) {
    zoom_ *= 0.9;
  }
  else if(event.GetWheelRotation() > 0) {
    zoom_ *= 1.1;
  }
  Refresh();
}
}
