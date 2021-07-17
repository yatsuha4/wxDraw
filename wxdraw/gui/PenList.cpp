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
  return getPaletteComponent()->getPens();
}
/**
 */
void PenList::onUpdate() {
  auto& pens = getItems();
  long index = 0;
  for(auto& pen : pens) {
    wxListItem item;
    item.SetId(index++);
    item.SetText(pen->getName());
    getList()->InsertItem(item);
  }
}
}
