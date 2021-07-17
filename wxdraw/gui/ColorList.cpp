#include "wxdraw/gui/ColorList.hpp"
#include "wxdraw/gui/Inspector.hpp"
#include "wxdraw/gui/MainFrame.hpp"
#include "wxdraw/gui/Palette.hpp"
#include "wxdraw/palette/Color.hpp"
#include "wxdraw/palette/Gradient.hpp"

namespace wxdraw::gui {
/**
 */
ColorList::ColorList(wxWindow* parent, Palette* palette)
  : super(parent, palette, "Color")
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
void ColorList::update() {
  getList()->DeleteAllItems();
  if(gradient_) {
    for(size_t i = 0; i < gradient_->getColors().size(); i++) {
      auto& color = gradient_->getColors().at(i);
      wxListItem item;
      item.SetId(i);
      item.SetText(wxString::FromDouble(color->getPos()));
      item.SetTextColour((color->getColor().GetLuminance() < 0.5) ? *wxWHITE : *wxBLACK);
      item.SetBackgroundColour(color->getColor());
      getList()->InsertItem(item);
    }
  }
}
/**
 */
void ColorList::onListItemSelected(wxListEvent& event) {
  if(gradient_ && event.GetIndex() < gradient_->getColors().size()) {
    if(auto color = gradient_->getColors().at(event.GetIndex())) {
      selectItem(*color);
    }
  }
}
}
