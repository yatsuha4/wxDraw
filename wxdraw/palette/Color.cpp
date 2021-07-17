#include "wxdraw/palette/Color.hpp"
#include "wxdraw/property/Property.hpp"

namespace wxdraw::palette {
const char* Color::TYPE = "Color";
/**
   コンストラクタ
*/
Color::Color()
  : color_(wxTransparentColour), 
    pos_(0.0)
{
}
/**
 */
bool Color::operator<(const Color& rhs) const {
  return getPos() < rhs.getPos();
}
/**
 */
Color::operator wxGraphicsGradientStop() const {
  return wxGraphicsGradientStop(color_, pos_);
}
/**
 */
PropertyPtr Color::createProperty(const PaletteComponentPtr& palette) {
  auto property = super::createProperty(TYPE, palette);
  property->appendMember("Color", color_);
  property->appendMember("Pos", pos_);
  return property;
}
}
