#include "wxdraw/component/EllipseComponent.hpp"
#include "wxdraw/node/EllipseNode.hpp"

namespace wxdraw::node {
const char* EllipseNode::TYPE = "Ellipse";
/**
   コンストラクタ
*/
EllipseNode::EllipseNode()
  : super(TYPE)
{
  appendComponent<EllipseComponent>();
}
/**
   コピーコンストラクタ
*/
EllipseNode::EllipseNode(const EllipseNode& src)
  : super(src)
{
}
/**
 */
NodePtr EllipseNode::clone() const {
  return std::make_shared<EllipseNode>(*this);
}
}
