#include "wxdraw/component/EllipseComponent.hpp"
#include "wxdraw/component/LayoutComponent.hpp"
#include "wxdraw/gui/Renderer.hpp"
#include "wxdraw/node/Node.hpp"

namespace wxdraw::component {
const char* EllipseComponent::TYPE = "Ellipse";
/**
   コンストラクタ
*/
EllipseComponent::EllipseComponent(const NodePtr& node)
  : super(TYPE, node)
{
}
/**
   コピーコンストラクタ
*/
EllipseComponent::EllipseComponent(const EllipseComponent& src, const NodePtr& node)
  : super(src, node)
{
}
/**
 */
void EllipseComponent::onRender(Renderer& renderer) {
  if(auto layout = getNode()->getComponent<LayoutComponent>()) {
    auto& rect = layout->getRect();
    renderer.getContext().DrawEllipse(rect.pos.x, rect.pos.y, rect.size.x, rect.size.y);
  }
}
}
