#pragma once

#include "wxdraw/gui/PaletteList.hpp"

namespace wxdraw::gui {
/**
 */
class BrushList
  : public PaletteList
{
  using super = PaletteList;

 public:
  BrushList(wxWindow* parent, Palette* palette);
  ~BrushList() override = default;

 protected:
  PaletteItemPtr getItem(size_t index) const override;
};
}
