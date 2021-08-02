#include "wxdraw/component/ProxyComponent.hpp"
#include "wxdraw/node/Node.hpp"

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
void ProxyComponent::render(Renderer& renderer, const LayoutComponentPtr& layout) {
  if(node_) {
    if(!getNode()->setError(Node::Error::RECURSION_RENDERING, node_->isRendering())) {
      node_->render(renderer, layout);
    }
  }
}
}
