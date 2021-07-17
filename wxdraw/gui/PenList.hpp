#pragma once

#include "wxdraw/gui/PaletteList.hpp"

namespace wxdraw::gui {
/**
 */
class PenList
  : public PaletteList
{
  using super = PaletteList;

 public:
  PenList(wxWindow* parent, Palette* palette);
  ~PenList() override = default;

 protected:
  PaletteItemPtr getItem(size_t index) const override;
};
}
