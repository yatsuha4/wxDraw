#include "wxdraw/palette/ColorBase.hpp"
#include "wxdraw/palette/PenBase.hpp"
#include "wxdraw/property/Property.hpp"

namespace wxdraw::palette {
/**
   コンストラクタ
   @param type 型名
   @param palette パレットコンポーネント
   @param name 名前
   @param color カラー
*/
PenBase::PenBase(const wxString& type, 
                 const PaletteComponentPtr& palette, 
                 const wxString& name, 
                 const ColorBasePtr& color)
  : super(type, palette, name), 
    color_(color)
{
}
/**
 */
void PenBase::update() {
  setBitmap(color_ ? color_->getBitmap() : GetNullBitmap());
  super::update();
}
/**
 */
PropertyPtr PenBase::generateProperty() {
  auto property = super::generateProperty();
  property->appendMember("Name", getName());
  property->appendMember("Color", color_);
  return property;
}
}
