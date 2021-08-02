#pragma once

#include "wxdraw/component/Component.hpp"

namespace wxdraw::component {
/**
 */
class ViewComponent
  : public Component<ViewComponent>
{
  using super = Component<ViewComponent>;

 public:
  static const char* TYPE;

 public:
  ViewComponent(const NodePtr& node);
  ViewComponent(const ViewComponent& src, const NodePtr& node);
  ~ViewComponent() override = default;
};
}
