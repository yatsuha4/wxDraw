#include "wxdraw/component/LayoutComponent.hpp"
#include "wxdraw/gui/Renderer.hpp"
#include "wxdraw/node/Node.hpp"
#include "wxdraw/property/Property.hpp"

namespace wxdraw::component {
/**
   コンストラクタ
   @param node ノード
*/
LayoutComponent::LayoutComponent(Node& node)
  : super(node), 
    alignment_(0.5), 
    scale_(1.0), 
    rotate_(0.0), 
    matrix_(1.0)
{
  getProperty()->appendMember("Size.Alignment", size_.alignment);
  getProperty()->appendMember("Size.Offset", size_.offset);
  getProperty()->appendMember("Pos.Alignment", pos_.alignment);
  getProperty()->appendMember("Pos.Offset", pos_.offset);
  getProperty()->appendMember("Alignment", alignment_);
  getProperty()->appendMember("Scale", scale_);
  getProperty()->appendMember("Rotate", rotate_);
}
/**
 */
void LayoutComponent::setSize(const glm::dvec2& size) {
  size_.offset = size;
  update();
}
/**
 */
void LayoutComponent::onUpdate() {
  glm::dmat3 m(1.0);
  m = glm::scale(m, scale_);
  m = glm::rotate(m, rotate_);
  renderSize_ = getSize();
  m = glm::translate(m, apply(pos_) - renderSize_ * alignment_);
  matrix_ = m;
}
/**
 */
void LayoutComponent::onBeginRender(Renderer& renderer) {
  renderer.setMatrix(matrix_);
}
/**
 */
glm::dvec2 LayoutComponent::getSize() const {
  return apply(size_);
}
/**
 */
glm::dvec2 LayoutComponent::apply(const Layout& layout) const {
  if(auto parent = getParent()) {
    return parent->getSize() * layout.alignment + layout.offset;
  }
  return layout.offset;
}
/**
   親を取得する
   @return 親
*/
LayoutComponentPtr LayoutComponent::getParent() const {
  if(auto parent = getNode().getParent()) {
    return parent->getComponent<LayoutComponent>();
  }
  return nullptr;
}
}
