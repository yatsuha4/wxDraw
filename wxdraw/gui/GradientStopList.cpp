#include "wxdraw/component/PaletteComponent.hpp"
#include "wxdraw/gui/GradientStopList.hpp"
#include "wxdraw/gui/Palette.hpp"
#include "wxdraw/palette/Color.hpp"
#include "wxdraw/palette/Gradient.hpp"
#include "wxdraw/palette/GradientStop.hpp"

namespace wxdraw::gui {
/**
 */
GradientStopList::GradientStopList(wxWindow* parent, Palette* palette)
  : super(parent, palette)
{
  getList()->AppendColumn("Stop");
}
/**
 */
void GradientStopList::setGradient(const GradientPtr& gradient) {
  if(gradient != gradient_) {
    gradient_ = gradient;
    refresh();
  }
}
/**
 */
std::vector<GradientStopPtr>& GradientStopList::getItems() const {
  return gradient_ ? gradient_->getStops() : super::getItems();
}
/**
 */
bool GradientStopList::canAppendItem(size_t index) const {
  return gradient_ && super::canAppendItem(index);
}
/**
 */
bool GradientStopList::canRemoveItem(size_t index) const {
  return getItems().size() > 2 && super::canRemoveItem(index);
}
}
