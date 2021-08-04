#include "wxdraw/component/ProxyComponent.hpp"
#include "wxdraw/node/Node.hpp"
#include "wxdraw/property/Property.hpp"

namespace wxdraw::component {
const char* ProxyComponent::TYPE = "Proxy";
/**
   コンストラクタ
*/
ProxyComponent::ProxyComponent(const NodePtr& node)
  : super(TYPE, node)
{}
/**
   コピーコンストラクタ
*/
ProxyComponent::ProxyComponent(const ProxyComponent& src, const NodePtr& node)
  : super(src, node)
{}
/**
 */
PropertyPtr ProxyComponent::generateProperty() {
  auto property = super::generateProperty();
  property->appendMember("Node", node_).setReadOnly(true);
  return property;
}
/**
 */
void ProxyComponent::render(Renderer& renderer, const LayoutComponentPtr& layout) {
  if(node_) {
    if(!getNode()->setError(Node::Error::RECURSION_RENDERING, node_->isRendering())) {
      node_->render(renderer, layout);
    }
  }
}
}