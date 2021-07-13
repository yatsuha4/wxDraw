#include "wxdraw/component/EllipseComponent.hpp"
#include "wxdraw/component/LayoutComponent.hpp"
#include "wxdraw/gui/Renderer.hpp"
#include "wxdraw/node/Node.hpp"

namespace wxdraw::component {
const char* EllipseComponent::TYPE = "Ellipse";
/**
   コンストラクタ
*/
EllipseComponent::EllipseComponent(Node& node)
  : super(TYPE, node)
{
}
/**
   コピーコンストラクタ
*/
EllipseComponent::EllipseComponent(const EllipseComponent& src, Node& node)
  : super(src, node)
{
}
/**
 */
ComponentPtr EllipseComponent::clone(Node& node) const {
  return std::make_shared<EllipseComponent>(*this, node);
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
