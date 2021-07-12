#pragma once

#include "wxdraw/component/Component.hpp"

namespace wxdraw::component {
/**
 */
class LayerComponent
  : public Component
{
  using super = Component;

 public:
  static const char* TYPE;

 private:
  double opacity_;
  bool clip_;

 public:
  LayerComponent(Node& node);
  ~LayerComponent() override = default;

 protected:
  void onBeginRender(Renderer& renderer) override;
  void onEndRender(Renderer& renderer) override;
};
}
