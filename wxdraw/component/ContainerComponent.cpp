#include "wxdraw/component/ContainerComponent.hpp"
#include "wxdraw/node/Node.hpp"

namespace wxdraw::component {
const char* ContainerComponent::TYPE = "Container";
/**
   コンストラクタ
*/
ContainerComponent::ContainerComponent(const NodePtr& node)
  : super(TYPE, node, Priority::CONTAINER)
{
}
/**
   コピーコンストラクタ
*/
ContainerComponent::ContainerComponent(const ContainerComponent& src, const NodePtr& node)
  : super(src, node)
{
}
/**
 */
ContainerComponent::~ContainerComponent() {
  children_.clear();
}
/**
 */
void ContainerComponent::onUpdate() {
  for(auto& child : children_) {
    child->update();
  }
}
/**
 */
void ContainerComponent::onRender(Renderer& renderer) {
  for(auto& child : children_) {
    child->render(renderer);
  }
}
}
