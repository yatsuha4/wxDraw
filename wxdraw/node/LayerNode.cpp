#include "wxdraw/component/GridComponent.hpp"
#include "wxdraw/component/LayerComponent.hpp"
#include "wxdraw/node/LayerNode.hpp"

namespace wxdraw::node {
const char* LayerNode::TYPE = "Layer";
/**
 */
LayerNode::LayerNode()
  : super(TYPE)
{
  setContainer(true);
  appendComponent<LayerComponent>();
  appendComponent<GridComponent>();
}
}
