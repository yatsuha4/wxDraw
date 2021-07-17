#include "wxdraw/palette/Color.hpp"
#include "wxdraw/property/Property.hpp"

namespace wxdraw::palette {
const char* Color::TYPE = "Color";
int Color::Serial = 0;
/**
   コンストラクタ
*/
Color::Color()
  : color_(wxTransparentColour)
{
}
/**
 */
void Color::update() {
  wxImage image(BITMAP_SIZE);
  image.SetRGB(image.GetSize(), color_.Red(), color_.Green(), color_.Blue());
  setBitmap(image);
}
/**
 */
void Color::onCreate(const PaletteComponentPtr& palette) {
  setName(wxString::Format("%s_%d", TYPE, ++Serial));
}
/**
 */
PropertyPtr Color::createProperty() {
  auto property = PropertyOwner::createProperty(TYPE);
  property->appendMember("Name", getName());
  property->appendMember("Color", color_);
  return property;
}
}
