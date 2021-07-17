#pragma once

#include "wxdraw/gui/PaletteList.hpp"

namespace wxdraw::gui {
/**
 */
class BrushList
  : public PaletteList<Brush>
{
  using super = PaletteList<Brush>;

 public:
  BrushList(wxWindow* parent, Palette* palette);
  ~BrushList() override = default;

 protected:
  std::vector<BrushPtr>& getItems() const override;
  void onUpdate(const BrushPtr& brush, wxListItem& item) override;
};
}
