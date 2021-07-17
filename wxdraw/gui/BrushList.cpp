#include "wxdraw/component/PaletteComponent.hpp"
#include "wxdraw/gui/BrushList.hpp"
#include "wxdraw/palette/Brush.hpp"

namespace wxdraw::gui {
/**
 */
BrushList::BrushList(wxWindow* parent, Palette* palette)
  : super(parent, palette)
{
}
/**
 */
std::vector<BrushPtr>& BrushList::getItems() const {
  return getPaletteComponent()->getBrushes();
}
}
