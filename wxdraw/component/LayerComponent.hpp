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

  PropertyPtr createProperty() override;

 protected:
  void onBeginRender(Renderer& renderer) override;
  void onEndRender(Renderer& renderer) override;
};
}
