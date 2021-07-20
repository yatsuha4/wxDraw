﻿#pragma once

#include "wxdraw/component/Component.hpp"

namespace wxdraw::component {
/**
   テキストコンポーネント
*/
class TextComponent
  : public Component<TextComponent>
{
  using super = Component<TextComponent>;

 public:
  static const char* TYPE;

 private:
  FontPtr font_;
  ColorPtr color_;
  wxString text_;
  glm::dvec2 alignment_;

 public:
  TextComponent(const NodePtr& node);
  TextComponent(const TextComponent& src, const NodePtr& node);
  ~TextComponent() override = default;

  WXDRAW_ACCESSOR(Font, font_);
  WXDRAW_ACCESSOR(Text, text_);

  PropertyPtr createProperty() override;

 protected:
  void onRender(Renderer& renderer) override;
};
}
