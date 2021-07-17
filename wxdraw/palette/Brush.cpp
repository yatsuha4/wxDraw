#include "wxdraw/palette/Brush.hpp"
#include "wxdraw/property/OptionProperty.hpp"

namespace wxdraw::palette {
const char* Brush::TYPE = "Brush";
int Brush::Serial = 0;
/**
   デフォルトコンストラクタ
*/
Brush::Brush()
  : super()
{
}
/**
 */
void Brush::onCreate(const PaletteComponentPtr& palette) {
  name_ = wxString::Format("%s_%d", TYPE, ++Serial);
}
/**
 */
PropertyPtr Brush::createProperty(const PaletteComponentPtr& palette) {
  auto property = super::createProperty(TYPE, palette);
  property->appendMember("Name", name_);
  return property;
}
}
