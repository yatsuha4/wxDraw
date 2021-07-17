#include "wxdraw/component/PaletteComponent.hpp"
#include "wxdraw/gui/PenList.hpp"
#include "wxdraw/palette/Pen.hpp"

namespace wxdraw::gui {
/**
 */
PenList::PenList(wxWindow* parent, Palette* palette)
  : super(parent, palette)
{
}
/**
 */
std::vector<PenPtr>& PenList::getItems() const {
  return getPaletteComponent()->getPens();
}
}
