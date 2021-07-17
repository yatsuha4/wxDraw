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
  return getPaletteComponent()->getBrushes();
}
/**
 */
void BrushList::onUpdate() {
  auto& brushes = getItems();
  long index = 0;
  for(auto& brush : brushes) {
    wxListItem item;
    item.SetId(index++);
    item.SetText(brush->getName());
    getList()->InsertItem(item);
  }
}
}
