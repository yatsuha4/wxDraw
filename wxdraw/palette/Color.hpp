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
  wxString name_;
  wxColour color_;

  static int Serial;

 public:
  Color();
  Color(const Color& src) = default;
  ~Color() = default;

  WXDRAW_GETTER(Name, name_);
  WXDRAW_ACCESSOR(Color, color_);

  void onCreate(const PaletteComponentPtr& palette) override;
  PropertyPtr createProperty() override;
};
}
