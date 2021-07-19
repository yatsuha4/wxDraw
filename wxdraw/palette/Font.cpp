#include "wxdraw/palette/Font.hpp"
#include "wxdraw/property/Property.hpp"

namespace wxdraw::palette {
const char* Font::TYPE = "Font";
int Font::Serial = 0;
/**
 */
Font::Font(const wxFont& font)
  : font_(font)
{
}
/**
 */
PropertyPtr Font::createProperty() {
  auto property = PropertyOwner::createProperty(TYPE);
  property->appendMember("Name", getName());
  property->appendMember("Font", font_);
  return property;
}
}
