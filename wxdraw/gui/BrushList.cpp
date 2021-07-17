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
void BrushList::onUpdate(const BrushPtr& brush, wxListItem& item) {
  item.SetText(brush->getName());
  item.SetImage(appendGradientImage(brush->getGradient()));
}
}
