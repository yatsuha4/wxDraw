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
  double pos_;

 public:
  Color();
  Color(const Color& src) = default;
  ~Color() = default;

  bool operator<(const Color& rhs) const;

  WXDRAW_ACCESSOR(Color, color_);
  WXDRAW_ACCESSOR(Pos, pos_);

  operator wxGraphicsGradientStop() const;

  PropertyPtr createProperty(const PaletteComponentPtr& palette) override;
};
}
