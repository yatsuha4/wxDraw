#include "wxdraw/container/Pen.hpp"
#include "wxdraw/property/OptionProperty.hpp"

namespace wxdraw::container {
const char* Pen::TYPE = "Pen";
/**
   デフォルトコンストラクタ
*/
Pen::Pen()
  : width_(0.1)
{
}
/**
 */
PropertyPtr Pen::createProperty(const PaletteComponentPtr& palette) const {
  auto property = std::make_shared<OptionProperty<PaletteComponentPtr>>(TYPE, palette);
  property->appendMember("Width", width_);
  return property;
}
}

