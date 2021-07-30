#include "wxdraw/component/BrushComponent.hpp"
#include "wxdraw/component/LayoutComponent.hpp"
#include "wxdraw/component/PaletteComponent.hpp"
#include "wxdraw/gui/Renderer.hpp"
#include "wxdraw/node/Node.hpp"
#include "wxdraw/property/Property.hpp"

namespace wxdraw::component {
const char* BrushComponent::TYPE = "Brush";
/**
   コンストラクタ
*/
BrushComponent::BrushComponent(const NodePtr& node)
  : super(TYPE, node)
{
}
/**
   コピーコンストラクタ
*/
BrushComponent::BrushComponent(const BrushComponent& src, const NodePtr& node)
  : super(src, node), 
    brush_(src.brush_)
{
}
/**
 */
void BrushComponent::onCreate() {
  super::onCreate();
  if(auto palette = Node::GetParentComponent<PaletteComponent>(getNode())) {
    brush_ = palette->getDefaultItem<Brush>("Default");
  }
}
/**
 */
PropertyPtr BrushComponent::generateProperty() {
  auto property = super::generateProperty();
  property->appendMember("Brush", brush_);
  return property;
}
/**
 */
void BrushComponent::onBeginRender(Renderer& renderer) {
  if(brush_) {
    auto layout = getNode()->getLayout();
    renderer.pushBrush(*brush_, layout->getRect());
  }
}
/**
 */
void BrushComponent::onEndRender(Renderer& renderer) {
  if(brush_) {
    renderer.popBrush();
  }
}
}
