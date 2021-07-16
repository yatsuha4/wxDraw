#pragma once

#include "wxdraw/component/Component.hpp"

namespace wxdraw::component {
/**
 */
class BrushComponent
  : public Component<BrushComponent>
{
  using super = Component<BrushComponent>;

 public:
  static const char* TYPE;

 private:
  GradientPtr gradient_;
  wxBrush brush_;

 public:
  BrushComponent(const NodePtr& node);
  BrushComponent(const BrushComponent& src, const NodePtr& node);
  ~BrushComponent() override = default;

  WXDRAW_GETTER(Brush, brush_);

  PropertyPtr createProperty() override;

 protected:
  void onUpdate() override;
  void onBeginRender(Renderer& renderer) override;
  void onEndRender(Renderer& renderer) override;
};
}
