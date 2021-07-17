#include "wxdraw/component/PaletteComponent.hpp"
#include "wxdraw/gui/ColorList.hpp"
#include "wxdraw/palette/Color.hpp"

namespace wxdraw::gui {
/**
 */
ColorList::ColorList(wxWindow* parent, Palette* palette)
  : super(parent, palette)
{
  getList()->AppendColumn("Color");
  /*
  {
    auto gradient = std::make_shared<Gradient>();
    for(int i = 0; i < 8; i++) {
      auto color = std::make_shared<Color>();
      color->setColor(wxColour(i * 0x1f, i * 0x1f, i * 0x1f)).setPos(i / 8.0);
      gradient->getColors().push_back(color);
    }
    setGradient(gradient);
  }
  */
}
/**
 */
std::vector<ColorPtr>& ColorList::getItems() const {
  return getPaletteComponent()->getColors();
}
/**
 */
void ColorList::onUpdate(const ColorPtr& color, wxListItem& item) {
  item.SetText(color->getName());
  item.SetImage(appendColorImage(color->getColor()));
  super::onUpdate(color, item);
}
}
