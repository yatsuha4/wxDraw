#include "wxdraw/gui/ColorList.hpp"
#include "wxdraw/gui/Inspector.hpp"
#include "wxdraw/gui/MainFrame.hpp"
#include "wxdraw/gui/Palette.hpp"
#include "wxdraw/palette/Color.hpp"
#include "wxdraw/palette/Gradient.hpp"

namespace wxdraw::gui {
std::vector<ColorPtr> ColorList::EMPTY;
/**
 */
ColorList::ColorList(wxWindow* parent, Palette* palette)
  : super(parent, palette)
{
  getList()->AppendColumn("Color");
  {
    auto gradient = std::make_shared<Gradient>();
    for(int i = 0; i < 8; i++) {
      auto color = std::make_shared<Color>();
      color->setColor(wxColour(i * 0x1f, i * 0x1f, i * 0x1f)).setPos(i / 8.0);
      gradient->getColors().push_back(color);
    }
    setGradient(gradient);
  }
}
/**
 */
void ColorList::setGradient(const GradientPtr& gradient) {
  gradient_ = gradient;
  update();
}
/**
 */
std::vector<ColorPtr>& ColorList::getItems() const {
  return gradient_ ? gradient_->getColors() : EMPTY;
}
/**
 */
void ColorList::onUpdate(const ColorPtr& color, wxListItem& item) {
  item.SetText(wxString::FromDouble(color->getPos()));
  item.SetImage(appendColorImage(color->getColor()));
}
}
