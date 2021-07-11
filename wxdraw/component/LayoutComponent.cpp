#include "wxdraw/component/LayoutComponent.hpp"
#include "wxdraw/gui/Renderer.hpp"
#include "wxdraw/node/Node.hpp"

namespace wxdraw::component {
/**
   コンストラクタ
   @param node ノード
*/
LayoutComponent::LayoutComponent(Node& node)
  : super("LayoutComponent", node), 
    size_(glm::dvec2(0.0), glm::dvec2(100.0)), 
    pos_(glm::dvec2(0.5), glm::dvec2(0.0)), 
    alignment_(0.5), 
    scale_(1.0), 
    rotate_(0.0), 
    matrix_(1.0), 
    rect_(glm::dvec2(0.0), glm::dvec2(0.0))
{
  appendMember("Size.Relative", size_.relative);
  appendMember("Size.Absolute", size_.absolute);
  appendMember("Pos.Relative", pos_.relative);
  appendMember("Pos.Absolute", pos_.absolute);
  appendMember("Alignment", alignment_);
  appendMember("Scale", scale_);
  appendMember("Rotate", rotate_);
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
LayoutComponentPtr LayoutComponent::getParent() const {
  if(auto parent = getNode().getParent()) {
    return parent->getComponent<LayoutComponent>();
  }
  return nullptr;
}
}
