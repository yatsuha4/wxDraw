﻿#pragma once

#include "wxdraw/component/Component.hpp"
#include "wxdraw/object/List.hpp"

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
  List<Node> children_;

 public:
  ContainerComponent(const NodePtr& node);
  ContainerComponent(const ContainerComponent& src, const NodePtr& node);
  ~ContainerComponent() override;

  WXDRAW_ACCESSOR(Children, children_);

  void update() override;
  void render(Renderer& renderer, const Transform& transform) override;
};
}
