#include "wxdraw/component/BrushComponent.hpp"
#include "wxdraw/gui/Renderer.hpp"
#include "wxdraw/property/Property.hpp"

namespace wxdraw::component {
const char* BrushComponent::TYPE = "Brush";
/**
   コンストラクタ
*/
BrushComponent::BrushComponent(const NodePtr& node)
  : super(TYPE, node), 
    colorIndex_(0)
{
}
/**
   コピーコンストラクタ
*/
BrushComponent::BrushComponent(const BrushComponent& src, const NodePtr& node)
  : super(src, node), 
    colorIndex_(src.colorIndex_), 
    brush_(src.brush_)
{
}
/**
 */
PropertyPtr BrushComponent::createProperty() {
  auto property = super::createProperty();
  property->appendMember("Color", colorIndex_);
  return property;
}
/**
 */
void BrushComponent::onUpdate() {
  brush_.SetColour(getColor(colorIndex_));
}
/**
 */
void BrushComponent::onBeginRender(Renderer& renderer) {
  renderer.pushBrush(brush_);
}
/**
 */
void BrushComponent::onEndRender(Renderer& renderer) {
  renderer.popBrush();
}
}
