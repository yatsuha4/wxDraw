#include "wxdraw/component/BrushComponent.hpp"
#include "wxdraw/gui/Renderer.hpp"

namespace wxdraw::component {
/**
   コンストラクタ
*/
BrushComponent::BrushComponent(Node& node)
  : super("BrushComponent", node), 
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
