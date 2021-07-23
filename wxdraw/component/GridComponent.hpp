#pragma once

#include "wxdraw/component/Component.hpp"

namespace wxdraw::component {
/**
   グリッド
*/
class GridComponent
  : public Component<GridComponent>
{
  using super = Component<GridComponent>;

 public:
  static const char* TYPE;

 private:
  bool show_;
  bool snap_;
  glm::dvec2 size_;
  glm::dvec2 offset_;
  wxColour color_;
  double width_;
  wxGraphicsPenInfo pen_;

 public:
  GridComponent(const NodePtr& node);
  GridComponent(const GridComponent& src, const NodePtr& node);
  ~GridComponent() override = default;

  PropertyPtr generateProperty() override;

 protected:
  void onUpdate() override;
  void onRender(Renderer& renderer) override;
};
}
