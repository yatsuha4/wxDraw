#include "wxdraw/component/BrushComponent.hpp"
#include "wxdraw/gui/Renderer.hpp"

namespace wxdraw::component {
const char* BrushComponent::TYPE = "Brush";
/**
   コンストラクタ
*/
BrushComponent::BrushComponent(const NodePtr& node)
  : super(TYPE, node), 
    color_(*wxWHITE), 
    brush_(color_)
{
  setup();
}
/**
   コピーコンストラクタ
*/
BrushComponent::BrushComponent(const BrushComponent& src, const NodePtr& node)
  : super(src, node), 
    color_(src.color_), 
    brush_(src.brush_)
{
  setup();
}
/**
 */
void BrushComponent::onUpdate() {
  brush_.SetColour(color_);
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
/**
 */
void BrushComponent::setup() {
  appendMember("Color", color_);
}
}
