#include "wxdraw/component/GridComponent.hpp"
#include "wxdraw/component/LayerComponent.hpp"
#include "wxdraw/node/LayerNode.hpp"

namespace wxdraw::node {
const char* LayerNode::TYPE = "Layer";
/**
   コンストラクタ
*/
LayerNode::LayerNode()
  : super(TYPE)
{
  setContainer(true);
  appendComponent<LayerComponent>();
  appendComponent<GridComponent>();
}
/**
   コピーコンストラクタ
*/
LayerNode::LayerNode(const LayerNode& src)
  : super(src)
{
}
/**
 */
NodePtr LayerNode::clone() const {
  return std::make_shared<LayerNode>(*this);
}
}
