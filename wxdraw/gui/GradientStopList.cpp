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
  getList()->AppendColumn("Color");
}
/**
 */
void GradientStopList::setGradient(const GradientPtr& gradient) {
  gradient_ = gradient;
  update();
}
/**
 */
std::vector<GradientStopPtr>& GradientStopList::getItems() const {
  return gradient_ ? gradient_->getStops() : super::getItems();
}
/**
 */
void GradientStopList::onUpdate(const GradientStopPtr& stop, wxListItem& item) {
  item.SetText(wxString::FromDouble(stop->getPos()));
  item.SetImage(appendColorImage(stop->getColor()->getColor()));
  super::onUpdate(stop, item);
  /*
  {
    wxListItem second;
    second.SetId(item.GetId());
    second.SetColumn(1);
    second.SetText(stop->getColor()->getName());
    getList()->SetItem(second);
  }
  */
}
}
