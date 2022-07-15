#pragma once

#include "wxdraw/palette/PaletteItem.hpp"

namespace wxdraw::palette {
/**
   ペン(ブラシ)基底クラス
*/
class PenBase
  : public PaletteItem
{
  using super = PaletteItem;
  using super::PaletteItem;

 private:
  ColorBasePtr color_;

 public:
  PenBase(const wxString& type, 
          const PaletteComponentPtr& palette, 
          const wxString& name, 
          const ColorBasePtr& color);
  PenBase(const PenBase& src) = default;
  ~PenBase() override = default;

  WXDRAW_ACCESSOR(Color, color_);

  void update() override;

  PropertyPtr generateProperty() override;
};
}
