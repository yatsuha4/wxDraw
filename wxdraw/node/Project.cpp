#include "wxdraw/component/BrushComponent.hpp"
#include "wxdraw/node/Project.hpp"

namespace wxdraw::node {
/**
   デフォルトコンストラクタ
*/
Project::Project()
  : super("Project")
{
  appendComponent<BrushComponent>();
}
}
