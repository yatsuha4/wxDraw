#include "wxdraw/palette/Brush.hpp"
#include "wxdraw/property/Property.hpp"

namespace wxdraw::palette {
const char* Brush::TYPE = "Brush";
int Brush::Serial = 0;
/**
   デフォルトコンストラクタ
*/
Brush::Brush()
  : direction_(0.0)
{
}
/**
 */
void Brush::onCreate(const PaletteComponentPtr& palette) {
  setName(wxString::Format("%s_%d", TYPE, ++Serial));
}
/**
 */
PropertyPtr Brush::createProperty() {
  auto property = super::createProperty(TYPE);
  property->appendMember("Direction", direction_);
  return property;
}
}
