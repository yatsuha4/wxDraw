#include "wxdraw/palette/ColorBase.hpp"
#include "wxdraw/palette/Pen.hpp"
#include "wxdraw/property/Property.hpp"

namespace wxdraw::palette {
const char* Pen::TYPE = "Pen";
int Pen::Serial = 0;
/**
   デフォルトコンストラクタ
*/
Pen::Pen()
  : width_(0.1)
{
}
/**
 */
void Pen::onCreate(const PaletteComponentPtr& palette) {
  setName(wxString::Format("%s_%d", TYPE, ++Serial));
}
/**
 */
void Pen::update() {
  super::update();
  setBitmap(color_ ? color_->getBitmap() : GetNullBitmap());
}
/**
 */
PropertyPtr Pen::createProperty() {
  auto property = PropertyOwner::createProperty(TYPE);
  property->appendMember("Name", getName());
  property->appendMember("Width", width_);
  return property;
}
}
