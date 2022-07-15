#include "wxdraw/palette/Brush.hpp"
#include "wxdraw/property/Property.hpp"

namespace wxdraw::palette {
const char* Brush::TYPE = "Brush";
/**
   コンストラクタ
*/
Brush::Brush(const PaletteComponentPtr& palette)
  : super(TYPE, palette), 
    direction_(0.0)
{
}
/**
   コンストラクタ
*/
Brush::Brush(const PaletteComponentPtr& palette, 
             const wxString& name, 
             const ColorBasePtr& color)
  : super(TYPE, palette, name, color), 
    direction_(0.0)
{
}
/**
 */
PropertyPtr Brush::generateProperty() {
  auto property = super::generateProperty();
  property->appendMember("Direction", direction_);
  return property;
}
}
