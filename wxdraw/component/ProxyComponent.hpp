#pragma once

#include "wxdraw/component/Component.hpp"
#include "wxdraw/property/Choice.hpp"

namespace wxdraw::component {
/**
   プロキシコンポーネント
*/
class ProxyComponent
  : public Component<ProxyComponent>
{
  using super = Component<ProxyComponent>;

 public:
  static const char* TYPE;

 private:
  NodePtr node_;
  Choice::Fit fit_;

 public:
  ProxyComponent(const NodePtr& node);
  ProxyComponent(const ProxyComponent& src, const NodePtr& node);
  ~ProxyComponent() override = default;

  WXDRAW_ACCESSOR(Node, node_);

  PropertyPtr generateProperty() override;

  void update() override;
  void render(Renderer& renderer, const LayoutComponentPtr& layout) override;
};
}
