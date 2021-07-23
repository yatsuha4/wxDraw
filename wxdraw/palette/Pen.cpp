#include "wxdraw/palette/Pen.hpp"
#include "wxdraw/property/Property.hpp"

namespace wxdraw::palette {
const char* Pen::TYPE = "Pen";
/**
   コンストラクタ
*/
Pen::Pen(const PaletteComponentPtr& palette)
  : super(TYPE, palette), 
    width_(1.0)
{
}
/**
   コンストラクタ
*/
Pen::Pen(const PaletteComponentPtr& palette, 
         const wxString& name, 
         const ColorBasePtr& color)
  : super(TYPE, palette, name, color), 
    width_(1.0)
{
}
/**
 */
PropertyPtr Pen::generateProperty() {
  auto property = super::generateProperty();
  property->appendMember("Width", width_);
  property->appendChoice("Style", style_);
  property->appendChoice("Cap", cap_);
  property->appendChoice("Join", join_);
  return property;
}
}
