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
Font::Font(const PaletteComponentPtr& palette, 
           const wxString& name, 
           const wxFont& font)
  : super(TYPE, palette, name), 
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
