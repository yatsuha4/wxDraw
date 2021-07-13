#pragma once

#include "wxdraw/component/Component.hpp"

namespace wxdraw::component {
/**
   グリッド
*/
class GridComponent
  : public Component
{
  using super = Component;

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
  GridComponent(Node& node);
  GridComponent(const GridComponent& src, Node& node);
  ~GridComponent() override = default;

  ComponentPtr clone(Node& node) const override;

 protected:
  void onUpdate() override;
  void onRender(Renderer& renderer) override;

 private:
  void setup();
};
}
