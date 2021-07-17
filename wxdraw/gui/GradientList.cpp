#include "wxdraw/component/PaletteComponent.hpp"
#include "wxdraw/gui/GradientList.hpp"
#include "wxdraw/palette/Gradient.hpp"

namespace wxdraw::gui {
/**
 */
GradientList::GradientList(wxWindow* parent, Palette* palette)
  : super(parent, palette)
{
  getList()->AppendColumn("Gradient");
}
/**
 */
std::vector<GradientPtr>& GradientList::getItems() const {
  return getPaletteComponent()->getGradients();
}
/**
 */
void GradientList::onUpdate() {
  auto& gradients = getItems();
  long index = 0;
  for(auto& gradient : gradients) {
    wxListItem item;
    item.SetId(index++);
    item.SetText(gradient->getName());
    getList()->InsertItem(item);
  }
}
}
