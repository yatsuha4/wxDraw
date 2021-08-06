#include "wxdraw/component/ComponentBase.hpp"
#include "wxdraw/component/PaletteComponent.hpp"
#include "wxdraw/node/Node.hpp"
#include "wxdraw/property/Property.hpp"

namespace wxdraw::component {
/**
   コンストラクタ
   @param type 型名
   @param node ノード
   @param priority 優先順位
*/
ComponentBase::ComponentBase(const char* type, 
                             const NodePtr& node, 
                             Priority priority)
  : super(type), 
    node_(node), 
    priority_(priority)
{
}
/**
   コピーコンストラクタ
*/
ComponentBase::ComponentBase(const ComponentBase& src, const NodePtr& node)
  : super(src), 
    node_(node), 
    priority_(src.priority_)
{
}
/**
   デストラクタ
*/
ComponentBase::~ComponentBase() {
  node_.reset();
}
/**
 */
NodePtr ComponentBase::getNode() {
  return node_.lock();
}
}
