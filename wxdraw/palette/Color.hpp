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

 public:
  Color(const PaletteComponentPtr& palette);
  Color(const PaletteComponentPtr& palette, 
        const wxString& name, 
        const wxColour& color);
  Color(const Color& src) = default;
  ~Color() = default;

  WXDRAW_ACCESSOR(Color, color_);

  void update() override;
  PropertyPtr generateProperty() override;
};
}
