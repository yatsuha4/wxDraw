#include "wxdraw/container/Gradient.hpp"
#include "wxdraw/container/GradientColor.hpp"
#include "wxdraw/gui/ColorList.hpp"
#include "wxdraw/gui/Inspector.hpp"
#include "wxdraw/gui/MainFrame.hpp"
#include "wxdraw/gui/Palette.hpp"

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
      auto color = std::make_shared<GradientColor>();
      color->setColor(wxColour(i * 0x1f, i * 0x1f, i * 0x1f)).setPos(i / 8.0);
      gradient->push_back(color);
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
    for(size_t i = 0; i < gradient_->size(); i++) {
      auto& color = gradient_->at(i);
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
  if(gradient_ && event.GetIndex() < gradient_->size()) {
    if(auto color = gradient_->at(event.GetIndex())) {
      getPalette()->getMainFrame()->getInspector()->show(color->createProperty());
    }
  }
}
}
