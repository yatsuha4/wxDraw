#include "wxdraw/component/ProxyComponent.hpp"
#include "wxdraw/node/Error.hpp"
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
  property->appendChoice("Fit", fit_);
  return property;
}
/**
 */
void ProxyComponent::onUpdate() {
  super::onUpdate();
  if(node_) {
    node_->update();
    switch(fit_.getIndex()) {
    case Choice::Fit::EXPAND:
      break;
    default:
      break;
    }
  }
}
/**
 */
void ProxyComponent::render(Renderer& renderer, const LayoutComponentPtr& layout) {
  super::getNode()->resetError<Error::RecursionRendering>();
  if(node_) {
    try {
      node_->render(renderer, layout);
    }
    catch(Error::RecursionRendering error) {
      super::getNode()->setError(error);
    }
  }
}
}
