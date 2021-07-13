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
/**
   コピーコンストラクタ
*/
RectangleNode::RectangleNode(const RectangleNode& src)
  : super(src)
{
}
/**
 */
NodePtr RectangleNode::clone() const {
  return std::make_shared<RectangleNode>(*this);
}
}
