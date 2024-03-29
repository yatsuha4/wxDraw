﻿#pragma once

#include "wxdraw/component/Component.hpp"

namespace wxdraw::component {
/**
   ペンコンポーネント
*/
class PenComponent
  : public Component<PenComponent>
{
  using super = Component<PenComponent>;

 public:
  static const char* TYPE;

 private:
  PenPtr pen_;

 public:
  PenComponent(const NodePtr& node);
  PenComponent(const PenComponent& src, const NodePtr& node);
  ~PenComponent() override = default;

  void onCreate() override;

  WXDRAW_GETTER(Pen, pen_);

  PropertyPtr generateProperty() override;

  void beginRender(Renderer& renderer, const Transform& transform) override;
  void endRender(Renderer& renderer, const Transform& transform) override;
};
}
