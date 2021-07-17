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
PaletteItemPtr GradientList::getItem(size_t index) const {
  return GetItem(index, getPaletteComponent()->getGradients());
}
}
