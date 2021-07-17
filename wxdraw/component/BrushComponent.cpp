#include "wxdraw/component/BrushComponent.hpp"
#include "wxdraw/gui/Renderer.hpp"
#include "wxdraw/palette/Gradient.hpp"
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
PropertyPtr BrushComponent::createProperty() {
  auto property = super::createProperty();
  property->appendMember("Brush", brush_);
  return property;
}
/**
 */
void BrushComponent::onUpdate() {
  //brush_.SetColour(gradient_ ? gradient_->getColor() : wxTransparentColour);
}
/**
 */
void BrushComponent::onBeginRender(Renderer& renderer) {
  //renderer.pushBrush(brush_);
}
/**
 */
void BrushComponent::onEndRender(Renderer& renderer) {
  //renderer.popBrush();
}
}
