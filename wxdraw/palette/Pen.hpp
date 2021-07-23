#pragma once

#include "wxdraw/palette/PenBase.hpp"

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

 public:
  Pen(const PaletteComponentPtr& palette);
  Pen(const PaletteComponentPtr& palette, 
      const wxString& name, 
      const ColorBasePtr& color = nullptr);
  Pen(const Pen& src) = default;
  ~Pen() override = default;

  WXDRAW_GETTER(Width, width_);

  PropertyPtr generateProperty() override;
};
}
