#include "wxdraw/component/TextColorComponent.hpp"
#include "wxdraw/gui/Renderer.hpp"
#include "wxdraw/palette/Color.hpp"
#include "wxdraw/property/Property.hpp"

namespace wxdraw::component {
const char* TextColorComponent::TYPE = "TextColor";
/**
   コンストラクタ
   @param node ノード
*/
TextColorComponent::TextColorComponent(const NodePtr& node)
  : super(TYPE, node)
{}
/**
   コピーコンストラクタ
   @param src コピー元
   @param node ノード
*/
TextColorComponent::TextColorComponent(const TextColorComponent& src, 
                                       const NodePtr& node)
  : super(src, node), 
    color_(src.color_)
{}
/**
   @copydoc Object::generateProperty
*/
PropertyPtr TextColorComponent::generateProperty() {
  auto property = super::generateProperty();
  property->appendMember("Color", color_);
  return property;
}
/**
   @copydoc ComponentBase::beginRender
*/
void TextColorComponent::beginRender(Renderer& renderer, 
                                     const Transform& transform) {
  super::beginRender(renderer, transform);
  if(color_) {
    renderer.getTextColor().push(color_->getColor());
  }
}
/**
   @copydoc ComponentBase::endRender
*/
void TextColorComponent::endRender(Renderer& renderer, 
                                   const Transform& transform) {
  if(color_) {
    renderer.getTextColor().pop();
  }
  super::endRender(renderer, transform);
}
}
