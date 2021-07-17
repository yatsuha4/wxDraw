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
void PenList::onUpdate(const PenPtr& pen, wxListItem& item) {
  item.SetText(pen->getName());
  item.SetImage(appendGradientImage(pen->getGradient()));
}
}
