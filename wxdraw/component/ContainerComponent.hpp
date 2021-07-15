#pragma once

#include "wxdraw/component/Component.hpp"

namespace wxdraw::component {
/**
 */
class ContainerComponent
  : public Component<ContainerComponent>
{
  using super = Component<ContainerComponent>;

 public:
  static const char* TYPE;

 private:
  std::vector<NodePtr> children_;

 public:
  ContainerComponent(const NodePtr& node);
  ContainerComponent(const ContainerComponent& src, const NodePtr& node);
  ~ContainerComponent() override = default;

  WXDRAW_GETTER(Children, children_);
  void appendChild(const NodePtr& child);
  void insertChild(const NodePtr& child, size_t index);
  void removeChild(const NodePtr& child);

 protected:
  void onUpdate() override;
  void onRender(Renderer& renderer) override;
};
}
