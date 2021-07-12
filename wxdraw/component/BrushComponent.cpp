#include "wxdraw/component/BrushComponent.hpp"
#include "wxdraw/gui/Renderer.hpp"

namespace wxdraw::component {
const char* BrushComponent::TYPE = "Brush";
/**
   コンストラクタ
*/
BrushComponent::BrushComponent(Node& node)
  : super(TYPE, node), 
    color_(*wxWHITE), 
    brush_(color_)
{
  appendMember("Color", color_);
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
}
