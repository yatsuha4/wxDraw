#pragma once

#include "wxdraw/component/Component.hpp"

namespace wxdraw::component {
/**
 */
class BrushComponent
  : public Component
{
  using super = Component;

 private:
  wxColour color_;
  wxBrush brush_;

 public:
  BrushComponent(Node& node);
  ~BrushComponent() override = default;

  WXDRAW_GETTER(Brush, brush_);

 protected:
  void onUpdate() override;
  void onBeginRender(Renderer& renderer) override;
  void onEndRender(Renderer& renderer) override;
};
}
