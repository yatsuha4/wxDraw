#include "wxdraw/component/PaletteComponent.hpp"
#include "wxdraw/gui/GradientStopList.hpp"
#include "wxdraw/gui/Palette.hpp"

namespace wxdraw::gui {
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
List<GradientStop>& GradientStopList::getItems() const {
  static List<GradientStop> EMPTY;
  return gradient_ ? gradient_->getStops() : EMPTY;
}
/**
 */
bool GradientStopList::canAppendItem(size_t index) const {
  return gradient_ && super::canAppendItem(index);
}
/**
 */
GradientStopPtr GradientStopList::getRemoveItem(size_t index) const {
  return (getItems().size() > 2) ? super::getRemoveItem(index) : nullptr;
}
}
