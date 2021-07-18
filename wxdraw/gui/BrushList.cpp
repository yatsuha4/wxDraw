#include "wxdraw/component/PaletteComponent.hpp"
#include "wxdraw/gui/BrushList.hpp"
#include "wxdraw/palette/Brush.hpp"

namespace wxdraw::gui {
/**
 */
BrushList::BrushList(wxWindow* parent, Palette* palette)
  : super(parent, palette)
{
  getList()->AppendColumn("Brush");
}
/**
 */
std::vector<BrushPtr>& BrushList::getItems() const {
  if(auto palette = getPaletteComponent()) {
    return palette->getBrushes();
  }
  return super::getItems();
}
}
