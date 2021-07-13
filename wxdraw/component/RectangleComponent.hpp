#pragma once

#include "wxdraw/component/Component.hpp"

namespace wxdraw::component {
/**
   矩形
*/
class RectangleComponent
  : public Component<RectangleComponent>
{
  using super = Component<RectangleComponent>;

 public:
  static const char* TYPE;

 private:
  double round_;

 public:
  RectangleComponent(Node& node);
  RectangleComponent(const RectangleComponent& src, Node& node);
  ~RectangleComponent() override = default;

 protected:
  void onRender(Renderer& renderer) override;

 private:
  void setup();
};
}
