#pragma once

#include "wxdraw/gui/PaletteList.hpp"

namespace wxdraw::gui {
/**
 */
class PenList
  : public PaletteList<Pen>
{
  using super = PaletteList<Pen>;

 public:
  PenList(wxWindow* parent, Palette* palette);
  ~PenList() override = default;

 protected:
  std::vector<PenPtr>& getItems() const override;

  void onUpdate() override;
};
}
