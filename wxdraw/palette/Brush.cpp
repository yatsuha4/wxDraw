#include "wxdraw/palette/Brush.hpp"
#include "wxdraw/property/OptionProperty.hpp"

namespace wxdraw::palette {
const char* Brush::TYPE = "Brush";
/**
   デフォルトコンストラクタ
*/
Brush::Brush()
  : super()
{
}
/**
 */
PropertyPtr Brush::createProperty(const PaletteComponentPtr& palette) {
  auto property = std::make_shared<OptionProperty<PaletteComponentPtr>>(TYPE, palette);
  return property;
}
}
