#include "wxdraw/component/PaletteComponent.hpp"
#include "wxdraw/gui/PenList.hpp"
#include "wxdraw/palette/Pen.hpp"

namespace wxdraw::gui {
/**
 */
PenList::PenList(wxWindow* parent, Palette* palette)
  : super(parent, palette)
{
  getList()->AppendColumn("Pen");
}
/**
 */
std::vector<PenPtr>& PenList::getItems() const {
  if(auto palette = getPaletteComponent()) {
    return palette->getPens();
  }
  return super::getItems();
}
}
