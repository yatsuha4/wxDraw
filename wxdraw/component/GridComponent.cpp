#include "wxdraw/component/GridComponent.hpp"
#include "wxdraw/component/LayoutComponent.hpp"
#include "wxdraw/gui/Renderer.hpp"
#include "wxdraw/node/Node.hpp"

namespace wxdraw::component {
const char* GridComponent::TYPE = "Grid";
/**
   コンストラクタ
*/
GridComponent::GridComponent(Node& node)
  : super(TYPE, node), 
    show_(true), 
    snap_(false), 
    size_(1.0), 
    offset_(0.0), 
    color_(0x80, 0x80, 0x80, 0x80), 
    width_(0.1), 
    pen_(color_, width_)
{
  setup();
}
/**
   コピーコンストラクタ
*/
GridComponent::GridComponent(const GridComponent& src, Node& node)
  : super(src, node), 
    show_(src.show_), 
    snap_(src.snap_), 
    size_(src.size_), 
    offset_(src.offset_), 
    color_(src.color_), 
    width_(src.width_), 
    pen_(src.pen_)
{
  setup();
}
/**
 */
ComponentPtr GridComponent::clone(Node& node) const {
  return std::make_shared<GridComponent>(*this, node);
}
/**
 */
void GridComponent::onUpdate() {
  pen_.Colour(color_).Width(width_);
}
/**
 */
void GridComponent::onRender(Renderer& renderer) {
  if(show_) {
    auto& context = renderer.getContext();
    renderer.pushPen(pen_);
    auto path = context.CreatePath();
    auto& rect = getNode().getComponent<LayoutComponent>()->getRect();
    for(auto x = offset_.x; x < rect.size.x; x += size_.x) {
      path.MoveToPoint(rect.pos.x + x, rect.pos.y);
      path.AddLineToPoint(rect.pos.x + x, rect.pos.y + rect.size.y);
    }
    for(auto y = offset_.y; y < rect.size.y; y += size_.y) {
      path.MoveToPoint(rect.pos.x, rect.pos.y + y);
      path.AddLineToPoint(rect.pos.x + rect.size.x, rect.pos.y + y);
    }
    context.StrokePath(path);
    renderer.popPen();
  }
}
/**
 */
void GridComponent::setup() {
  appendMember("Show", show_);
  appendMember("Snap", snap_);
  appendMember("Size", size_);
  appendMember("Offset", offset_);
  appendMember("Color", color_);
  appendMember("Width", width_);
}
}
