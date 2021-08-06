#include "wxdraw/component/ContainerComponent.hpp"
#include "wxdraw/component/LayoutComponent.hpp"
#include "wxdraw/component/ViewComponent.hpp"
#include "wxdraw/gui/Canvas.hpp"
#include "wxdraw/gui/MainFrame.hpp"
#include "wxdraw/gui/Outliner.hpp"
#include "wxdraw/gui/Renderer.hpp"
#include "wxdraw/node/Node.hpp"

namespace wxdraw::gui {
wxBrush Canvas::BackgroundBrush;
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
  Bind(wxEVT_LEFT_DOWN, &Canvas::onLeftDown, this);
  Bind(wxEVT_MOTION, &Canvas::onMotion, this);
  Bind(wxEVT_MOUSEWHEEL, &Canvas::onMouseWheel, this);
  Bind(wxEVT_RIGHT_DOWN, &Canvas::onRightDown, this);
}
/**
 */
const wxBrush& Canvas::GetBackgroundBrush() {
  const int SIZE = 8;
  const wxColour C1(0x70, 0x70, 0x70);
  const wxColour C2(0x90, 0x90, 0x90);
  if(!BackgroundBrush.IsOk()) {
    wxImage image(SIZE * 2, SIZE * 2);
    for(int x = 0; x < 2; x++) {
      for(int y = 0; y < 2; y++) {
        wxRect rect(wxPoint(SIZE * x, SIZE * y), wxSize(SIZE, SIZE));
        if(((x + y) & 1) == 0) {
          image.SetRGB(rect, C1.Red(), C1.Green(), C1.Blue());
        }
        else {
          image.SetRGB(rect, C2.Red(), C2.Green(), C2.Blue());
        }
      }
    }
    BackgroundBrush.SetStipple(image);
  }
  return BackgroundBrush;
}
/**
   描画
*/
void Canvas::OnDraw(wxDC& dc) {
  super::OnDraw(dc);
  dc.SetBackground(GetBackgroundBrush());
  dc.Clear();
  viewNode_ = nullptr;
  if(auto selectNode = mainFrame_->getOutliner()->getSelectNode()) {
    if(auto view = Node::GetParentComponent<ViewComponent>(selectNode)) {
      viewNode_ = view->getNode();
      glm::dvec2 size(GetSize().GetWidth(), GetSize().GetHeight());
      viewTransform_.matrix = glm::scale(glm::translate(glm::dmat3(1.0), offset_), 
                                         glm::dvec2(zoom_));
      viewTransform_.rect.size = size / zoom_;
      viewTransform_.rect.pos = glm::dvec2(0.0);
      Renderer renderer(dc, viewTransform_.matrix);
      viewNode_->render(renderer, viewTransform_);
      drawCursor(renderer, selectNode);
    }
  }
}
/**
 */
void Canvas::onLeftDown(wxMouseEvent& event) {
  if(viewNode_) {
    auto pos = glm::dvec2(event.GetX(), event.GetY());
    if(auto node = getNode(viewNode_, viewTransform_, pos)) {
      mainFrame_->getOutliner()->selectNode(node);
    }
  }
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
/**
   選択中のノードにカーソルを表示する
   @param renderer レンダラー
   @param node 選択中のノード
*/
void Canvas::drawCursor(Renderer& renderer, const NodePtr& node) {
  /*
  if(auto layout = node->getLayout()) {
    auto& context = renderer.getContext();
    context.SetTransform(context.CreateMatrix());
    context.SetPen(context.CreatePen(wxGraphicsPenInfo(*wxRED, 0.5)));

    auto m = viewMatrix_ * layout->getMatrix();
    auto& rect = layout->getRect();
    glm::dvec2 p[4];
    for(int i = 0; i < 4; i++) {
      p[i] = m * glm::dvec3(rect.pos.x + rect.size.x * (i & 1), 
                            rect.pos.y + rect.size.y * (i / 2), 1.0);
    }
    auto path = context.CreatePath();
    path.MoveToPoint(p[0].x, p[0].y);
    path.AddLineToPoint(p[1].x, p[1].y);
    path.AddLineToPoint(p[3].x, p[3].y);
    path.AddLineToPoint(p[2].x, p[2].y);
    path.AddLineToPoint(p[0].x, p[0].y);
    context.StrokePath(path);
  }
  */
}
/**
 */
NodePtr Canvas::getNode(const NodePtr& node, 
                        const Transform& parent, 
                        const glm::dvec2& pos) const {
  auto transform = node->getLayout()->apply(parent);
  if(auto container = node->getContainer()) {
    for(auto iter = std::rbegin(container->getChildren());
        iter != std::rend(container->getChildren());
        iter++) {
      if(auto found = getNode(*iter, transform, pos)) {
        return found;
      }
    }
  }
  auto p = glm::inverse(transform.matrix) * glm::dvec3(pos, 1.0);
  return transform.rect.isContain(p) ? node : nullptr;
}
}
