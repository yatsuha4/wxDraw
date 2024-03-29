﻿#include "wxdraw/component/RectangleComponent.hpp"
#include "wxdraw/container/Transform.hpp"
#include "wxdraw/gui/Renderer.hpp"
#include "wxdraw/node/Node.hpp"
#include "wxdraw/property/Property.hpp"

namespace wxdraw::component {
const char* RectangleComponent::TYPE = "Rectangle";
/**
   コンストラクタ
*/
RectangleComponent::RectangleComponent(const NodePtr& node)
  : super(TYPE, node), 
    round_(0.0)
{
}
/**
   コピーコンストラクタ
*/
RectangleComponent::RectangleComponent(const RectangleComponent& src, 
                                       const NodePtr& node)
  : super(src, node), 
    round_(src.round_)
{
}
/**
 */
PropertyPtr RectangleComponent::generateProperty() {
  auto property = super::generateProperty();
  property->appendMember("Round", round_);
  return property;
}
/**
 */
void RectangleComponent::render(Renderer& renderer, const Transform& transform) {
  auto& context = renderer.getContext();
  auto& rect = transform.rect;
  if(round_ <= 0.0) {
    context.DrawRectangle(rect.pos.x, rect.pos.y, rect.size.x, rect.size.y);
  }
  else {
    context.DrawRoundedRectangle(rect.pos.x, rect.pos.y, rect.size.x, rect.size.y, round_);
  }
}
}
