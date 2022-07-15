#include "wxdraw/component/PaletteComponent.hpp"
#include "wxdraw/gui/GradientList.hpp"
#include "wxdraw/gui/Palette.hpp"

namespace wxdraw::gui {
/**
 */
void GradientList::onSelectItem(const PaletteItemPtr& item) {
  super::onSelectItem(item);
  auto gradient = std::static_pointer_cast<Gradient>(item);
  getPalette()->setGradient(gradient);
}
}
