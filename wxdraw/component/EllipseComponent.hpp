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
  EllipseComponent(const NodePtr& node);
  EllipseComponent(const EllipseComponent& src, const NodePtr& node);
  ~EllipseComponent() override = default;

 protected:
  void onRender(Renderer& renderer) override;
};
}
