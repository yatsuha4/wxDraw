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
  RectangleComponent(const NodePtr& node);
  RectangleComponent(const RectangleComponent& src, const NodePtr& node);
  ~RectangleComponent() override = default;

  PropertyPtr createProperty() override;

 protected:
  void onRender(Renderer& renderer) override;
};
}
