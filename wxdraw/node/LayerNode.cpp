#include "wxdraw/node/LayerNode.hpp"
#include "wxdraw/component/LayerComponent.hpp"

namespace wxdraw::node {
/**
 */
LayerNode::LayerNode()
  : super("Layer")
{
  appendComponent<LayerComponent>();
}
}
