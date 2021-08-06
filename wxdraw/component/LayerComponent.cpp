#include "wxdraw/component/LayerComponent.hpp"
#include "wxdraw/gui/Renderer.hpp"
#include "wxdraw/property/Property.hpp"

namespace wxdraw::component {
const char* LayerComponent::TYPE = "Layer";
/**
   コンストラクタ
*/
LayerComponent::LayerComponent(const NodePtr& node)
  : super(TYPE, node), 
    opacity_(1.0), 
    clip_(false)
{
}
/**
   コピーコンストラクタ
*/
LayerComponent::LayerComponent(const LayerComponent& src, const NodePtr& node)
  : super(src, node), 
    opacity_(src.opacity_), 
    clip_(src.clip_)
{
}
/**
 */
PropertyPtr LayerComponent::generateProperty() {
  auto property = super::generateProperty();
  property->appendMember("Opacity", opacity_);
  property->appendMember("Clip", clip_);
  return property;
}
/**
 */
void LayerComponent::beginRender(Renderer& renderer, const Transform& transform) {
  auto& context = renderer.getContext();
  context.PushState();
  context.BeginLayer(opacity_);
}
/**
 */
void LayerComponent::endRender(Renderer& renderer, const Transform& transform) {
  auto& context = renderer.getContext();
  context.EndLayer();
  context.PopState();
}
}
