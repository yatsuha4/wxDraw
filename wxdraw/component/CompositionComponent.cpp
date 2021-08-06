#include "wxdraw/component/CompositionComponent.hpp"
#include "wxdraw/gui/Renderer.hpp"
#include "wxdraw/property/Property.hpp"

namespace wxdraw::component {
const char* CompositionComponent::TYPE = "Composition";
/**
   コンストラクタ
*/
CompositionComponent::CompositionComponent(const NodePtr& node)
  : super(TYPE, node)
{}
/**
   コピーコンストラクタ
*/
CompositionComponent::CompositionComponent(const CompositionComponent& src, 
                                           const NodePtr& node)
  : super(src, node), 
    composition_(src.composition_)
{}
/**
 */
void CompositionComponent::onCreate() {
  super::onCreate();
  composition_.setIndex(static_cast<size_t>(Renderer::Composition::OVER));
}
/**
 */
PropertyPtr CompositionComponent::generateProperty() {
  auto property = super::generateProperty();
  property->appendChoice("Composition", composition_);
  return property;
}
/**
 */
void CompositionComponent::beginRender(Renderer& renderer, const Transform& transform) {
  renderer.pushComposition(static_cast<Renderer::Composition>(composition_.getIndex()));
}
/**
 */
void CompositionComponent::endRender(Renderer& renderer, const Transform& transform) {
  renderer.popComposition();
}
}
