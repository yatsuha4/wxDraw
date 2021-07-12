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
}
