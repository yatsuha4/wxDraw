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
  Choice::PenCap cap_;
  Choice::PenJoin join_;

 public:
  Pen(const PaletteComponentPtr& palette);
  Pen(const PaletteComponentPtr& palette, 
      const wxString& name, 
      const ColorBasePtr& color = nullptr);
  Pen(const Pen& src) = default;
  ~Pen() override = default;

  WXDRAW_ACCESSOR(Width, width_);
  WXDRAW_ACCESSOR(Style, style_);
  WXDRAW_ACCESSOR(Cap, cap_);
  WXDRAW_ACCESSOR(Join, join_);

  PropertyPtr generateProperty() override;
};
}
