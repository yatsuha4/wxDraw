#include "wxdraw/component/ContainerComponent.hpp"
#include "wxdraw/node/Node.hpp"

namespace wxdraw::component {
const char* ContainerComponent::TYPE = "Container";
/**
   コンストラクタ
*/
ContainerComponent::ContainerComponent(const NodePtr& node)
  : super(TYPE, node)
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
void ContainerComponent::appendChild(const NodePtr& child) {
  children_.push_back(child);
}
/**
 */
void ContainerComponent::insertChild(const NodePtr& child, size_t index) {
  wxASSERT(index <= children_.size());
  children_.insert(children_.begin() + index, child);
}
/**
 */
void ContainerComponent::removeChild(const NodePtr& child) {
  children_.erase(std::remove(children_.begin(), children_.end(), child));
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
