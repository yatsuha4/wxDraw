#include "wxdraw/component/ViewComponent.hpp"

namespace wxdraw::component {
const char* ViewComponent::TYPE = "View";
/**
   コンストラクタ
*/
ViewComponent::ViewComponent(const NodePtr& node)
  : super(TYPE, node)
{}
/**
   コピーコンストラクタ
*/
ViewComponent::ViewComponent(const ViewComponent& src, const NodePtr& node)
  : super(src, node)
{}
}
