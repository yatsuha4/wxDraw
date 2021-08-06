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
  std::transform(src.children_.begin(), 
                 src.children_.end(), 
                 std::back_inserter(children_), 
                 [&](auto& child) {
                 return Node::Clone(*child, node);
                 });
}
/**
 */
ContainerComponent::~ContainerComponent() {
  children_.clear();
}
/**
 */
void ContainerComponent::update() {
  super::update();
  for(auto& child : children_) {
    child->update();
  }
}
/**
 */
void ContainerComponent::render(Renderer& renderer, const LayoutComponentPtr& layout) {
  for(auto& child : children_) {
    child->render(renderer);
  }
}
}
