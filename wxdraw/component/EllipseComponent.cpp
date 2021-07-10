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
  auto layout = getNode().getComponent<LayoutComponent>();
  layout->getSize().offset = glm::dvec2(100.0);
  layout->update();
}
/**
 */
void EllipseComponent::onRender(Renderer& renderer) {
  if(auto layout = getNode().getComponent<LayoutComponent>()) {
    auto& rect = layout->getRect();
    renderer.getContext().DrawEllipse(rect.pos.x, rect.pos.y, rect.size.x, rect.size.y);
  }
}
}

