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
  wxColour color_;
  wxBrush brush_;

 public:
  BrushComponent(Node& node);
  BrushComponent(const BrushComponent& src, Node& node);
  ~BrushComponent() override = default;

  WXDRAW_GETTER(Brush, brush_);

 protected:
  void onUpdate() override;
  void onBeginRender(Renderer& renderer) override;
  void onEndRender(Renderer& renderer) override;

 private:
  void setup();
};
}
