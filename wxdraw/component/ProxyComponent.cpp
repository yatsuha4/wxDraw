#include "wxdraw/component/LayoutComponent.hpp"
#include "wxdraw/component/ProxyComponent.hpp"
#include "wxdraw/container/Transform.hpp"
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
void ProxyComponent::update() {
  super::update();
  if(node_) {
    const auto& srcSize = node_->getLayout()->getSize();
    auto layout = super::getNode()->getLayout();
    const auto& dstSize = layout->getSize();
    glm::dvec2 fitScale(1.0);
    if(glm::all(glm::greaterThan(srcSize, glm::dvec2(0.0))) &&
       glm::all(glm::greaterThan(dstSize, glm::dvec2(0.0)))) {
      auto scale = dstSize / srcSize;
      switch(fit_.getIndex()) {
      case Choice::Fit::EXPAND:
        fitScale = glm::dvec2(glm::min(scale.x, scale.y));
        break;
      case Choice::Fit::SHRINK:
        fitScale = glm::dvec2(glm::max(scale.x, scale.y));
        break;
      default:
        break;
      }
    }
    layout->setChildScale(fitScale);
  }
}
/**
 */
void ProxyComponent::render(Renderer& renderer, const Transform& transform) {
  super::getNode()->resetError<Error::RecursionRendering>();
  if(node_) {
    try {
      node_->render(renderer, transform);
    }
    catch(Error::RecursionRendering error) {
      super::getNode()->setError(error);
    }
  }
}
}
