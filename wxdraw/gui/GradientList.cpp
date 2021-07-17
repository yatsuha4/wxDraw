#include "wxdraw/component/PaletteComponent.hpp"
#include "wxdraw/gui/GradientList.hpp"
#include "wxdraw/palette/Gradient.hpp"

namespace wxdraw::gui {
/**
 */
GradientList::GradientList(wxWindow* parent, Palette* palette)
  : super(parent, palette)
{
}
/**
 */
std::vector<GradientPtr>& GradientList::getItems() const {
  return getPaletteComponent()->getGradients();
}
}
