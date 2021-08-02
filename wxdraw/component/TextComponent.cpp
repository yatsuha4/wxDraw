#include "wxdraw/component/LayoutComponent.hpp"
#include "wxdraw/component/TextComponent.hpp"
#include "wxdraw/component/PaletteComponent.hpp"
#include "wxdraw/gui/Renderer.hpp"
#include "wxdraw/node/Node.hpp"
#include "wxdraw/palette/Color.hpp"
#include "wxdraw/palette/Font.hpp"
#include "wxdraw/property/Property.hpp"

namespace wxdraw::component {
const char* TextComponent::TYPE = "Text";
/**
   コンストラクタ
*/
TextComponent::TextComponent(const NodePtr& node)
  : super(TYPE, node), 
    alignment_(0.5)
{
}
/**
   コピーコンストラクタ
*/
TextComponent::TextComponent(const TextComponent& src, const NodePtr& node)
  : super(src, node), 
    font_(src.font_), 
    color_(src.color_), 
    text_(src.text_), 
    alignment_(src.alignment_)
{
}
/**
 */
void TextComponent::onCreate() {
  super::onCreate();
  if(auto palette = Node::GetParentComponent<PaletteComponent>(getNode())) {
    font_ = palette->getDefaultItem<Font>("Default");
    color_ = palette->getDefaultItem<Color>("Pen");
  }
}
/**
 */
PropertyPtr TextComponent::generateProperty() {
  auto property = super::generateProperty();
  property->appendMember("Font", font_);
  property->appendMember("Color", color_);
  property->appendMember("Text", text_);
  property->appendMember("Alignment", alignment_);
  return property;
}
/**
 */
void TextComponent::render(Renderer& renderer, const LayoutComponentPtr& layout) {
  if(layout && font_ && color_ && !text_.IsEmpty()) {
    auto& context = renderer.getContext();
    context.SetFont(font_->getFont(), color_->getColor());
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
