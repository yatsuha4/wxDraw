#include "wxdraw/component/LayoutComponent.hpp"
#include "wxdraw/container/Transform.hpp"
#include "wxdraw/property/Property.hpp"

namespace wxdraw::component {
const char* LayoutComponent::TYPE = "Layout";
/**
   コンストラクタ
   @param node ノード
*/
LayoutComponent::LayoutComponent(const NodePtr& node)
  : super(TYPE, node, Priority::LAYOUT), 
    pos_(glm::dvec2(0.5), glm::dvec2(0.0)), 
    size_(256.0), 
    alignment_(0.5), 
    scale_(1.0), 
    childScale_(1.0), 
    rotate_(0.0)
{
}
/**
   コピーコンストラクタ
   @param src コピー元
   @param node ノード
*/
LayoutComponent::LayoutComponent(const LayoutComponent& src, const NodePtr& node)
  : super(src, node), 
    pos_(src.pos_), 
    size_(src.size_), 
    alignment_(src.alignment_), 
    scale_(src.scale_), 
    childScale_(src.childScale_), 
    rotate_(src.rotate_)
{
}
/**
 */
PropertyPtr LayoutComponent::generateProperty() {
  auto property = super::generateProperty();
  property->appendMember("Pos.Relative", pos_.relative);
  property->appendMember("Pos.Absolute", pos_.absolute);
  property->appendMember("Size", size_);
  property->appendMember("Alignment", alignment_);
  property->appendMember("Scale", scale_);
  property->appendMember("Rotate", rotate_);
  return property;
}
/**
 */
Transform LayoutComponent::apply(const Transform& parent) const {
  Transform transform;
  glm::dmat3 m(1.0);
  m = glm::translate(m, parent.rect.pos + parent.rect.size * pos_.relative + pos_.absolute);
  m = glm::rotate(m, glm::radians(rotate_));
  m = glm::scale(m, scale_ * parent.scale);
  transform.matrix = parent.matrix * m;
  transform.rect.size = size_;
  transform.rect.pos = -size_ * alignment_;
  transform.scale = childScale_;
  return transform;
}
}
