#pragma once

#include "wxdraw/palette/PaletteItem.hpp"

namespace wxdraw::palette {
/**
   グラデーションの要素
*/
class Color
  : public PaletteItem
{
  using super = PaletteItem;

 public:
  static const char* TYPE;

 private:
  wxColour color_;

  static int Serial;

 public:
  Color();
  Color(const Color& src) = default;
  ~Color() = default;

  WXDRAW_ACCESSOR(Color, color_);

  void update() override;
  void onCreate(const PaletteComponentPtr& palette) override;
  PropertyPtr createProperty() override;
};
}
