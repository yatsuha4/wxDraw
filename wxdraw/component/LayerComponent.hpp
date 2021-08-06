#pragma once

#include "wxdraw/component/Component.hpp"

namespace wxdraw::component {
/**
 */
class LayerComponent
  : public Component<LayerComponent>
{
  using super = Component<LayerComponent>;

 public:
  static const char* TYPE;

 private:
  double opacity_;
  bool clip_;

 public:
  LayerComponent(const NodePtr& node);
  LayerComponent(const LayerComponent& src, const NodePtr& node);
  ~LayerComponent() override = default;

  PropertyPtr generateProperty() override;

  void beginRender(Renderer& renderer, const Transform& transform) override;
  void endRender(Renderer& renderer, const Transform& transform) override;
};
}
