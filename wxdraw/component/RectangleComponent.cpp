#include "wxdraw/component/LayoutComponent.hpp"
#include "wxdraw/component/RectangleComponent.hpp"
#include "wxdraw/gui/Renderer.hpp"
#include "wxdraw/node/Node.hpp"

namespace wxdraw::component {
const char* RectangleComponent::TYPE = "Rectangle";
/**
   コンストラクタ
*/
RectangleComponent::RectangleComponent(Node& node)
  : super(TYPE, node), 
    round_(0.0)
{
  appendMember("Round", round_);
}
/**
 */
void RectangleComponent::onRender(Renderer& renderer) {
  auto& context = renderer.getContext();
  if(auto layout = getNode().getComponent<LayoutComponent>()) {
    auto& rect = layout->getRect();
    if(round_ <= 0.0) {
      context.DrawRectangle(rect.pos.x, rect.pos.y, rect.size.x, rect.size.y);
    }
    else {
      context.DrawRoundedRectangle(rect.pos.x, rect.pos.y, rect.size.x, rect.size.y, round_);
    }
  }
}
}
