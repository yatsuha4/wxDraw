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
  BrushPtr brush_;

 public:
  BrushComponent(const NodePtr& node);
  BrushComponent(const BrushComponent& src, const NodePtr& node);
  ~BrushComponent() override = default;

  void onCreate() override;

  WXDRAW_GETTER(Brush, brush_);

  PropertyPtr generateProperty() override;

  void beginRender(Renderer& renderer, const Transform& transform) override;
  void endRender(Renderer& renderer, const Transform& transform) override;
};
}
