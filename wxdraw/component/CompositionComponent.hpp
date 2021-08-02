#pragma once

#include "wxdraw/component/Component.hpp"
#include "wxdraw/property/Choice.hpp"

namespace wxdraw::component {
/**
 */
class CompositionComponent
  : public Component<CompositionComponent>
{
  using super = Component<CompositionComponent>;

 public:
  static const char* TYPE;

 private:
  Choice::Composition composition_;

 public:
  CompositionComponent(const NodePtr& node);
  CompositionComponent(const CompositionComponent& src, const NodePtr& node);
  ~CompositionComponent() override = default;

  void onCreate() override;
  PropertyPtr generateProperty() override;

  void beginRender(Renderer& renderer, const LayoutComponentPtr& layout) override;
  void endRender(Renderer& renderer, const LayoutComponentPtr& layout) override;
};
}
