#include "wxdraw/palette/Pen.hpp"
#include "wxdraw/property/OptionProperty.hpp"

namespace wxdraw::palette {
const char* Pen::TYPE = "Pen";
/**
   デフォルトコンストラクタ
*/
Pen::Pen()
  : super(), 
    width_(0.1)
{
}
/**
 */
PropertyPtr Pen::createProperty(const PaletteComponentPtr& palette) {
  auto property = std::make_shared<OptionProperty<PaletteComponentPtr>>(TYPE, palette);
  property->appendMember("Width", width_);
  return property;
}
}
