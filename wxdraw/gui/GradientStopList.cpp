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
std::vector<GradientStopPtr>& GradientStopList::getItems() const {
  static std::vector<GradientStopPtr> EMPTY;
  return gradient_ ? gradient_->getStops() : EMPTY;
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
