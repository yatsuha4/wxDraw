#include "wxdraw/component/LayerComponent.hpp"
#include "wxdraw/gui/Renderer.hpp"

namespace wxdraw::component {
const char* LayerComponent::TYPE = "Layer";
/**
   コンストラクタ
*/
LayerComponent::LayerComponent(Node& node)
  : super(TYPE, node), 
    opacity_(1.0), 
    clip_(false)
{
  setup();
}
/**
   コピーコンストラクタ
*/
LayerComponent::LayerComponent(const LayerComponent& src, Node& node)
  : super(src, node), 
    opacity_(src.opacity_), 
    clip_(src.clip_)
{
  setup();
}
/**
 */
ComponentPtr LayerComponent::clone(Node& node) const {
  return std::make_shared<LayerComponent>(*this, node);
}
/**
 */
void LayerComponent::onBeginRender(Renderer& renderer) {
  auto& context = renderer.getContext();
  context.PushState();
  context.BeginLayer(opacity_);
}
/**
 */
void LayerComponent::onEndRender(Renderer& renderer) {
  auto& context = renderer.getContext();
  context.EndLayer();
  context.PopState();
}
/**
 */
void LayerComponent::setup() {
  appendMember("Opacity", opacity_);
  appendMember("Clip", clip_);
}
}
