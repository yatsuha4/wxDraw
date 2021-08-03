#pragma once

#include "wxdraw/component/Component.hpp"

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

 public:
  ProxyComponent(const NodePtr& node);
  ProxyComponent(const ProxyComponent& src, const NodePtr& node);
  ~ProxyComponent() override = default;

  WXDRAW_ACCESSOR(Node, node_);

  PropertyPtr generateProperty() override;

  void render(Renderer& renderer, const LayoutComponentPtr& layout) override;
};
}
