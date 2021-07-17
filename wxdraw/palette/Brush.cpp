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
void Brush::onCreate() {
  name_ = wxString::Format("%s_%d", TYPE, ++Serial);
}
/**
 */
PropertyPtr Brush::createProperty(const PaletteComponentPtr& palette) {
  auto property = std::make_shared<OptionProperty<PaletteComponentPtr>>(TYPE, palette);
  return property;
}
}
