#include "wxdraw/node/LayerNode.hpp"
#include "wxdraw/component/LayerComponent.hpp"

namespace wxdraw::node {
const char* LayerNode::TYPE = "Layer";
/**
 */
LayerNode::LayerNode()
  : super(TYPE)
{
  setContainer(true);
  appendComponent<LayerComponent>();
}
}
