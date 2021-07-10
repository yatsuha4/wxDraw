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
    size_(glm::dvec2(0.0), glm::dvec2(0.0)), 
    pos_(glm::dvec2(0.5), glm::dvec2(0.0)), 
    alignment_(0.5), 
    scale_(1.0), 
    rotate_(0.0), 
    matrix_(1.0), 
    rect_(glm::dvec2(0.0), glm::dvec2(0.0))
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
void LayoutComponent::onUpdate() {
  glm::dmat3 m(1.0);
  if(auto parent = getParent()) {
    auto& rect = parent->getRect();
    m = glm::translate(m, rect.pos + rect.size * pos_.alignment + pos_.offset);
    m = glm::rotate(m, glm::radians(rotate_));
    m = glm::scale(m, scale_);
    matrix_ = parent->getMatrix() * m;
    rect_.size = rect.size * size_.alignment + size_.offset;
  }
  else {
    m = glm::translate(m, pos_.offset);
    m = glm::rotate(m, glm::radians(rotate_));
    m = glm::scale(m, scale_);
    matrix_ = m;
    rect_.size = size_.offset;
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
LayoutComponentPtr LayoutComponent::getParent() const {
  if(auto parent = getNode().getParent()) {
    return parent->getComponent<LayoutComponent>();
  }
  return nullptr;
}
}
