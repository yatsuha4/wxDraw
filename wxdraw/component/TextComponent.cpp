#include "wxdraw/component/LayoutComponent.hpp"
#include "wxdraw/component/TextComponent.hpp"
#include "wxdraw/gui/Renderer.hpp"
#include "wxdraw/node/Node.hpp"
#include "wxdraw/palette/Color.hpp"
#include "wxdraw/property/Property.hpp"

namespace wxdraw::component {
const char* TextComponent::TYPE = "Text";
/**
   コンストラクタ
*/
TextComponent::TextComponent(const NodePtr& node)
  : super(TYPE, node), 
    font_(*wxNORMAL_FONT), 
    alignment_(0.5)
{
}
/**
   コピーコンストラクタ
*/
TextComponent::TextComponent(const TextComponent& src, const NodePtr& node)
  : super(src, node), 
    font_(src.font_), 
    text_(src.text_), 
    alignment_(src.alignment_)
{
}
/**
 */
PropertyPtr TextComponent::createProperty() {
  auto property = super::createProperty();
  property->appendMember("Font", font_);
  property->appendMember("Text", text_);
  property->appendMember("Color", color_);
  property->appendMember("Alignment", alignment_);
  return property;
}
/**
 */
void TextComponent::onRender(Renderer& renderer) {
  if(!text_.IsEmpty()) {
    if(auto layout = getNode()->getComponent<LayoutComponent>()) {
      auto& context = renderer.getContext();
      context.SetFont(font_, color_ ? color_->getColor() : *wxBLACK);
      wxDouble width = 0.0;
      wxDouble height = 0.0;
      wxDouble descent = 0.0;
      wxDouble externalLeading = 0.0;
      context.GetTextExtent(text_, &width, &height, &descent, &externalLeading);
      auto& rect = layout->getRect();
      auto pos = rect.pos + (rect.size - glm::dvec2(width, height)) * alignment_;
      context.DrawText(text_, pos.x, pos.y);
    }
  }
}
}
