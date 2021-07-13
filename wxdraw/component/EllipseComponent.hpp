#pragma once

#include "wxdraw/component/Component.hpp"

namespace wxdraw::component {
/**
 */
class EllipseComponent
  : public Component
{
  using super = Component;

 public:
  static const char* TYPE;

 public:
  EllipseComponent(Node& node);
  EllipseComponent(const EllipseComponent& src, Node& node);
  ~EllipseComponent() override = default;

  ComponentPtr clone(Node& node) const override;

 protected:
  void onRender(Renderer& renderer) override;
};
}
