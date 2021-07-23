#include "wxdraw/component/GridComponent.hpp"
#include "wxdraw/component/LayoutComponent.hpp"
#include "wxdraw/gui/Renderer.hpp"
#include "wxdraw/node/Node.hpp"
#include "wxdraw/property/Property.hpp"

namespace wxdraw::component {
const char* GridComponent::TYPE = "Grid";
/**
   コンストラクタ
*/
GridComponent::GridComponent(const NodePtr& node)
  : super(TYPE, node), 
    show_(true), 
    snap_(false), 
    size_(1.0), 
    offset_(0.0), 
    color_(0x80, 0x80, 0x80, 0x80), 
    width_(0.1), 
    pen_(color_, width_)
{
}
/**
   コピーコンストラクタ
*/
GridComponent::GridComponent(const GridComponent& src, const NodePtr& node)
  : super(src, node), 
    show_(src.show_), 
    snap_(src.snap_), 
    size_(src.size_), 
    offset_(src.offset_), 
    color_(src.color_), 
    width_(src.width_), 
    pen_(src.pen_)
{
}
/**
 */
PropertyPtr GridComponent::generateProperty() {
  auto property = super::generateProperty();
  property->appendMember("Show", show_);
  property->appendMember("Snap", snap_);
  property->appendMember("Size", size_);
  property->appendMember("Offset", offset_);
  property->appendMember("Color", color_);
  property->appendMember("Width", width_);
  return property;
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
    auto& rect = getNode()->getComponent<LayoutComponent>()->getRect();
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
}
