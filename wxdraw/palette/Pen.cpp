#include "wxdraw/palette/Pen.hpp"
#include "wxdraw/property/Property.hpp"

namespace wxdraw::palette {
const char* Pen::TYPE = "Pen";
/**
   コンストラクタ
*/
Pen::Pen(const PaletteComponentPtr& palette)
  : super(TYPE, palette), 
    width_(0.1)
{
}
/**
   コンストラクタ
*/
Pen::Pen(const PaletteComponentPtr& palette, 
         const wxString& name, 
         const ColorBasePtr& color)
  : super(TYPE, palette, name, color), 
    width_(0.1)
{
}
/**
 */
PropertyPtr Pen::createProperty() {
  auto property = super::createProperty();
  property->appendMember("Width", width_);
  return property;
}
}
