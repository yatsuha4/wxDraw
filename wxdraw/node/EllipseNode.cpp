#include "wxdraw/component/EllipseComponent.hpp"
#include "wxdraw/node/EllipseNode.hpp"

namespace wxdraw::node {
/**
   コンストラクタ
*/
EllipseNode::EllipseNode()
  : super("Ellipse")
{
  appendComponent<EllipseComponent>();
}
}
