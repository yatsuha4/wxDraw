#include "wxdraw/palette/Brush.hpp"
#include "wxdraw/palette/ColorBase.hpp"
#include "wxdraw/property/Property.hpp"

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
  setName(wxString::Format("%s_%d", TYPE, ++Serial));
}
/**
 */
void Brush::update() {
  super::update();
  setBitmap(color_ ? color_->getBitmap() : GetNullBitmap());
}
/**
 */
PropertyPtr Brush::createProperty() {
  auto property = PropertyOwner::createProperty(TYPE);
  property->appendMember("Name", getName());
  property->appendMember("Color", color_);
  return property;
}
}
