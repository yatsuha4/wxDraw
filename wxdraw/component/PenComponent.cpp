#include "wxdraw/component/LayoutComponent.hpp"
#include "wxdraw/component/PaletteComponent.hpp"
#include "wxdraw/component/PenComponent.hpp"
#include "wxdraw/gui/Renderer.hpp"
#include "wxdraw/node/Node.hpp"
#include "wxdraw/palette/Color.hpp"
#include "wxdraw/palette/Gradient.hpp"
#include "wxdraw/palette/Pen.hpp"
#include "wxdraw/property/Property.hpp"

namespace wxdraw::component {
const char* PenComponent::TYPE = "Pen";
/**
   コンストラクタ
*/
PenComponent::PenComponent(const NodePtr& node)
  : super(TYPE, node)
{
}
/**
   コピーコンストラクタ
*/
PenComponent::PenComponent(const PenComponent& src, const NodePtr& node)
  : super(src, node), 
    pen_(src.pen_)
{
}
/**
 */
void PenComponent::onCreate() {
  super::onCreate();
  if(auto palette = Node::GetParentComponent<PaletteComponent>(getNode())) {
    pen_ = palette->getDefaultItem<Pen>("Default");
  }
}
/**
 */
PropertyPtr PenComponent::generateProperty() {
  auto property = super::generateProperty();
  property->appendMember("Pen", pen_);
  return property;
}
/**
 */
void PenComponent::onBeginRender(Renderer& renderer) {
  if(pen_) {
    auto layout = getNode()->getLayout();
    renderer.pushPen(*pen_, layout->getRect());
  }
}
/**
 */
void PenComponent::onEndRender(Renderer& renderer) {
  if(pen_) {
    renderer.popPen();
  }
}
}
