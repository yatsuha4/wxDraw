#include "wxdraw/component/BrushComponent.hpp"
#include "wxdraw/component/ExportComponent.hpp"
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
  appendComponent<ExportComponent>();
}
}
