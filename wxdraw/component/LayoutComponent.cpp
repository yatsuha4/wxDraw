#include "wxdraw/component/LayoutComponent.hpp"
#include "wxdraw/gui/Renderer.hpp"
#include "wxdraw/node/Node.hpp"

namespace wxdraw::component {
/**
   コンストラクタ
   @param node ノード
*/
LayoutComponent::LayoutComponent(Node& node)
  : super(node), 
    scale_(1.0), 
    rotate_(0.0), 
    matrix_(1.0)
{
}
/**
 */
void LayoutComponent::onUpdate() {
  glm::dmat3 m;
  m = glm::scale(m, scale_);
  m = glm::rotate(m, rotate_);
  m = glm::translate(m, apply(pos_));
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
