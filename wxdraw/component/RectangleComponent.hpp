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

 public:
  static const char* TYPE;

 private:
  double round_;

 public:
  RectangleComponent(Node& node);
  RectangleComponent(const RectangleComponent& src, Node& node);
  ~RectangleComponent() override = default;

  ComponentPtr clone(Node& node) const override;

 protected:
  void onRender(Renderer& renderer) override;

 private:
  void setup();
};
}
