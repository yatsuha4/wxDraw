#include "wxdraw/component/BrushComponent.hpp"
#include "wxdraw/node/ProjectNode.hpp"

namespace wxdraw::node {
/**
   デフォルトコンストラクタ
*/
ProjectNode::ProjectNode()
  : super("Project")
{
  appendComponent<BrushComponent>();
}
}
