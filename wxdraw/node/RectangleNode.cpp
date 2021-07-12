#include "wxdraw/component/RectangleComponent.hpp"
#include "wxdraw/node/RectangleNode.hpp"

namespace wxdraw::node {
const char* RectangleNode::TYPE = "Rectangle";
/**
   コンストラクタ
*/
RectangleNode::RectangleNode()
  : super(TYPE)
{
  appendComponent<RectangleComponent>();
}
}
