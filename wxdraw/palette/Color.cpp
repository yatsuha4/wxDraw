#include "wxdraw/palette/Color.hpp"
#include "wxdraw/property/Property.hpp"

namespace wxdraw::palette {
const char* Color::TYPE = "Color";
/**
   コンストラクタ
*/
Color::Color(const PaletteComponentPtr& palette)
  : super(TYPE, palette), 
    color_(wxTransparentColour)
{
}
/**
 */
void Color::update() {
  wxImage image(BITMAP_SIZE);
  image.SetRGB(image.GetSize(), color_.Red(), color_.Green(), color_.Blue());
  setBitmap(image);
  super::update();
}
/**
 */
PropertyPtr Color::createProperty() {
  auto property = super::createProperty();
  property->appendMember("Name", getName());
  property->appendMember("Color", color_);
  return property;
}
}
