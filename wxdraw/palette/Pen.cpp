#include "wxdraw/palette/Pen.hpp"
#include "wxdraw/property/Property.hpp"

namespace wxdraw::palette {
const char* Pen::TYPE = "Pen";
int Pen::Serial = 0;
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
void Pen::onCreate(const PaletteComponentPtr& palette) {
  name_ = wxString::Format("%s_%d", TYPE, ++Serial);
}
/**
 */
PropertyPtr Pen::createProperty() {
  auto property = PropertyOwner::createProperty(TYPE);
  property->appendMember("Name", name_);
  property->appendMember("Width", width_);
  return property;
}
}
