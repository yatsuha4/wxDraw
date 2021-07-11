#include "wxdraw/gui/Canvas.hpp"
#include "wxdraw/gui/MainFrame.hpp"
#include "wxdraw/gui/Renderer.hpp"
#include "wxdraw/node/Project.hpp"

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
}
/**
   描画
*/
void Canvas::OnDraw(wxDC& dc) {
  super::OnDraw(dc);
  if(auto project = Node::GetParent<Project>(mainFrame_->getSelectNode())) {
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
}
