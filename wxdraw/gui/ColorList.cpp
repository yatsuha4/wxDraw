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
  return gradient_->getColors();
}
/**
 */
void ColorList::onUpdate() {
  if(gradient_) {
    updateImageList();
    for(size_t i = 0; i < gradient_->getColors().size(); i++) {
      auto& color = gradient_->getColors().at(i);
      wxListItem item;
      item.SetId(i);
      item.SetText(wxString::FromDouble(color->getPos()));
      item.SetImage(static_cast<int>(i));
      getList()->InsertItem(item);
    }
  }
}
/**
 */
void ColorList::updateImageList() {
  getImageList()->RemoveAll();
  for(auto& color : gradient_->getColors()) {
    getImageList()->Add(CreateBitmap(*color));
  }
}
/**
 */
wxBitmap ColorList::CreateBitmap(const Color& color) {
  wxImage image(IMAGE_SIZE);
  image.SetRGB(IMAGE_SIZE, 
               color.getColor().Red(), 
               color.getColor().Green(), 
               color.getColor().Blue());
  return wxBitmap(image);
}
}
