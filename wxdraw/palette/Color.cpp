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
void Color::onCreate(const PaletteComponentPtr& palette) {
  name_ = wxString::Format("%s_%d", TYPE, ++Serial);
}
/**
 */
PropertyPtr Color::createProperty() {
  auto property = PropertyOwner::createProperty(TYPE);
  property->appendMember("Name", name_);
  property->appendMember("Color", color_);
  return property;
}
}
