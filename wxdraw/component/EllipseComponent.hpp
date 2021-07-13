#pragma once

#include "wxdraw/component/Component.hpp"

namespace wxdraw::component {
/**
 */
class EllipseComponent
  : public Component<EllipseComponent>
{
  using super = Component<EllipseComponent>;

 public:
  static const char* TYPE;

 public:
  EllipseComponent(Node& node);
  EllipseComponent(const EllipseComponent& src, Node& node);
  ~EllipseComponent() override = default;

 protected:
  void onRender(Renderer& renderer) override;
};
}
