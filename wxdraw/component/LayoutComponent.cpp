#include "wxdraw/component/LayoutComponent.hpp"
#include "wxdraw/gui/Renderer.hpp"
#include "wxdraw/node/Node.hpp"
#include "wxdraw/property/Property.hpp"

namespace wxdraw::component {
const char* LayoutComponent::TYPE = "Layout";
/**
   コンストラクタ
   @param node ノード
*/
LayoutComponent::LayoutComponent(const NodePtr& node)
  : super(TYPE, node, Priority::LAYOUT), 
    size_(glm::dvec2(0.0), glm::dvec2(100.0)), 
    pos_(glm::dvec2(0.5), glm::dvec2(0.0)), 
    alignment_(0.5), 
    scale_(1.0), 
    rotate_(0.0), 
    matrix_(1.0), 
    rect_(glm::dvec2(0.0), glm::dvec2(0.0))
{
}
/**
   コピーコンストラクタ
   @param src コピー元
   @param node ノード
*/
LayoutComponent::LayoutComponent(const LayoutComponent& src, const NodePtr& node)
  : super(src, node), 
    size_(src.size_), 
    pos_(src.pos_), 
    alignment_(src.alignment_), 
    scale_(src.scale_), 
    rotate_(src.rotate_), 
    matrix_(src.matrix_), 
    rect_(src.rect_)
{
}
/**
 */
PropertyPtr LayoutComponent::createProperty() {
  auto property = super::createProperty();
  property->appendMember("Size.Relative", size_.relative);
  property->appendMember("Size.Absolute", size_.absolute);
  property->appendMember("Pos.Relative", pos_.relative);
  property->appendMember("Pos.Absolute", pos_.absolute);
  property->appendMember("Alignment", alignment_);
  property->appendMember("Scale", scale_);
  property->appendMember("Rotate", rotate_);
  return property;
}
/**
 */
void LayoutComponent::onUpdate() {
  glm::dmat3 m(1.0);
  if(auto parent = getParent()) {
    auto& rect = parent->getRect();
    m = glm::translate(m, rect.pos + rect.size * pos_.relative + pos_.absolute);
    m = glm::rotate(m, glm::radians(rotate_));
    m = glm::scale(m, scale_);
    matrix_ = parent->getMatrix() * m;
    rect_.size = rect.size * size_.relative + size_.absolute;
  }
  else {
    m = glm::translate(m, pos_.absolute);
    m = glm::rotate(m, glm::radians(rotate_));
    m = glm::scale(m, scale_);
    matrix_ = m;
    rect_.size = size_.absolute;
  }
  rect_.pos = -rect_.size * alignment_;
}
/**
 */
void LayoutComponent::onBeginRender(Renderer& renderer) {
  renderer.setMatrix(matrix_);
}
/**
   親を取得する
   @return 親
*/
LayoutComponentPtr LayoutComponent::getParent() {
  if(auto parent = getNode()->getParent()) {
    return parent->getComponent<LayoutComponent>();
  }
  return nullptr;
}
}
