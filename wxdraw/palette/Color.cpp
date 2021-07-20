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
   コンストラクタ
*/
Color::Color(const PaletteComponentPtr& palette, 
             const wxString& name, 
             const wxColour& color)
  : super(TYPE, palette, name), 
    color_(color)
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
