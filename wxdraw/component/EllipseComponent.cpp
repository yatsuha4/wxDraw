#include "wxdraw/component/EllipseComponent.hpp"
#include "wxdraw/container/Transform.hpp"
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
void EllipseComponent::render(Renderer& renderer, const Transform& transform) {
  renderer.getContext().DrawEllipse(transform.rect.pos.x, 
                                    transform.rect.pos.y, 
                                    transform.rect.size.x, 
                                    transform.rect.size.y);
}
}
