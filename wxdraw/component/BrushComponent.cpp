#include "wxdraw/component/BrushComponent.hpp"
#include "wxdraw/component/PaletteComponent.hpp"
#include "wxdraw/container/Transform.hpp"
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
void BrushComponent::beginRender(Renderer& renderer, const Transform& transform) {
  if(brush_) {
    renderer.pushBrush(*brush_, transform.rect);
  }
}
/**
 */
void BrushComponent::endRender(Renderer& renderer, const Transform& transform) {
  if(brush_) {
    renderer.popBrush();
  }
}
}
