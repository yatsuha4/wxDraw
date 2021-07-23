#pragma once

#include "wxdraw/palette/PenBase.hpp"
#include "wxdraw/property/Choice.hpp"

namespace wxdraw::palette {
/**
   ペン
*/
class Pen
  : public PenBase
{
  using super = PenBase;

 public:
  static const char* TYPE;

 private:
  double width_;
  Choice::PenStyle style_;

 public:
  Pen(const PaletteComponentPtr& palette);
  Pen(const PaletteComponentPtr& palette, 
      const wxString& name, 
      const ColorBasePtr& color = nullptr);
  Pen(const Pen& src) = default;
  ~Pen() override = default;

  WXDRAW_ACCESSOR(Width, width_);
  WXDRAW_ACCESSOR(Style, style_);

  PropertyPtr generateProperty() override;
};
}
