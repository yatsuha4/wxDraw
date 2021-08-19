#pragma once

#include "wxdraw/component/Component.hpp"

namespace wxdraw::component {
/**
   テキストカラーコンポーネント
*/
class TextColorComponent
  : public Component<TextColorComponent>
{
  using super = Component<TextColorComponent>;

 public:
  static const char* TYPE;

 private:
  ColorPtr color_;

 public:
  TextColorComponent(const NodePtr& node);
  TextColorComponent(const TextColorComponent& src, const NodePtr& node);
  ~TextColorComponent() override = default;

  PropertyPtr generateProperty() override;

  void beginRender(Renderer& renderer, const Transform& transform) override;
  void endRender(Renderer& renderer, const Transform& transform) override;
};
}
