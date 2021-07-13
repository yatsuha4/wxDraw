#include "wxdraw/component/BrushComponent.hpp"
#include "wxdraw/node/ProjectNode.hpp"

namespace wxdraw::node {
const char* ProjectNode::TYPE = "Project";
/**
   デフォルトコンストラクタ
*/
ProjectNode::ProjectNode()
  : super(TYPE)
{
  setContainer(true);
  appendComponent<BrushComponent>();
}
}
