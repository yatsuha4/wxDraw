#include "wxdraw/component/GridComponent.hpp"
#include "wxdraw/component/LayoutComponent.hpp"
#include "wxdraw/component/PaletteComponent.hpp"
#include "wxdraw/gui/Renderer.hpp"
#include "wxdraw/node/Node.hpp"
#include "wxdraw/palette/Pen.hpp"
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
    size_(32.0), 
    offset_(0.0)
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
    pen_(src.pen_)
{
}
/**
 */
void GridComponent::onCreate() {
  if(auto palette = Node::GetParentComponent<PaletteComponent>(getNode())) {
    pen_ = palette->getDefaultItem<Pen>("Grid");
  }
}
/**
 */
PropertyPtr GridComponent::generateProperty() {
  auto property = super::generateProperty();
  property->appendMember("Show", show_);
  property->appendMember("Snap", snap_);
  property->appendMember("Size", size_);
  property->appendMember("Offset", offset_);
  property->appendMember("Pen", pen_);
  return property;
}
/**
 */
void GridComponent::onRender(Renderer& renderer) {
  if(show_ && pen_) {
    auto& context = renderer.getContext();
    auto& rect = getNode()->getComponent<LayoutComponent>()->getRect();
    renderer.pushPen(*pen_, rect);
    auto path = context.CreatePath();
    for(auto x = offset_.x; x <= rect.size.x; x += size_.x) {
      path.MoveToPoint(rect.pos.x + x, rect.pos.y);
      path.AddLineToPoint(rect.pos.x + x, rect.pos.y + rect.size.y);
    }
    for(auto y = offset_.y; y <= rect.size.y; y += size_.y) {
      path.MoveToPoint(rect.pos.x, rect.pos.y + y);
      path.AddLineToPoint(rect.pos.x + rect.size.x, rect.pos.y + y);
    }
    context.StrokePath(path);
    renderer.popPen();
  }
}
}
