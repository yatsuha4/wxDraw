#pragma once

#include "wxdraw/component/Component.hpp"

namespace wxdraw::component {
/**
   矩形
*/
class RectangleComponent
  : public Component
{
  using super = Component;

 private:
  double round_;

 public:
  RectangleComponent(Node& node);
  ~RectangleComponent() override = default;

 protected:
  void onRender(Renderer& renderer) override;
};
}
