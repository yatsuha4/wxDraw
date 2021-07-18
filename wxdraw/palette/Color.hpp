#pragma once

#include "wxdraw/palette/ColorBase.hpp"

namespace wxdraw::palette {
/**
   単色
*/
class Color
  : public ColorBase
{
  using super = ColorBase;

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
