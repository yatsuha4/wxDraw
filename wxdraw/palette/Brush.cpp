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
 */
PropertyPtr Brush::createProperty() {
  auto property = super::createProperty();
  property->appendMember("Direction", direction_);
  return property;
}
}
