#include "wxdraw/component/RectangleComponent.hpp"
#include "wxdraw/node/RectangleNode.hpp"

namespace wxdraw::node {
/**
   コンストラクタ
*/
RectangleNode::RectangleNode()
  : super("Rectangle")
{
  appendComponent<RectangleComponent>();
}
}
