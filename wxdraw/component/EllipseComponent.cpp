#include "wxdraw/component/EllipseComponent.hpp"
#include "wxdraw/component/LayoutComponent.hpp"
#include "wxdraw/gui/Renderer.hpp"
#include "wxdraw/node/Node.hpp"

namespace wxdraw::component {
/**
   コンストラクタ
*/
EllipseComponent::EllipseComponent(Node& node)
  : super(node)
{
  getNode().getComponent<LayoutComponent>()->setSize(glm::dvec2(128.0));
}
/**
 */
void EllipseComponent::onRender(Renderer& renderer) {
  if(auto layout = getNode().getComponent<LayoutComponent>()) {
    auto size = layout->getRenderSize();
    renderer.getContext().DrawEllipse(0.0, 0.0, size.x, size.y);
  }
}
}

