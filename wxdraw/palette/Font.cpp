#include "wxdraw/palette/Font.hpp"
#include "wxdraw/property/Property.hpp"

namespace wxdraw::palette {
const char* Font::TYPE = "Font";
/**
 */
Font::Font(const PaletteComponentPtr& palette)
  : super(TYPE, palette)
{
}
/**
 */
Font::Font(const PaletteComponentPtr& palette, const wxFont& font)
  : super(TYPE, palette), 
    font_(font)
{
}
/**
 */
PropertyPtr Font::createProperty() {
  auto property = super::createProperty();
  property->appendMember("Name", getName());
  property->appendMember("Font", font_);
  return property;
}
}
