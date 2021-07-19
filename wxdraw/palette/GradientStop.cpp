#include "wxdraw/component/PaletteComponent.hpp"
#include "wxdraw/palette/Color.hpp"
#include "wxdraw/palette/GradientStop.hpp"
#include "wxdraw/property/Property.hpp"

namespace wxdraw::palette {
const char* GradientStop::TYPE = "GradientStop";
/**
   コンストラクタ
*/
GradientStop::GradientStop()
  : pos_(0.0)
{
}
/**
 */
bool GradientStop::operator<(const GradientStop& rhs) const {
  return getPos() < rhs.getPos();
}
/**
 */
GradientStop::operator wxGraphicsGradientStop() const {
  return wxGraphicsGradientStop(getWxColor(), pos_);
}
/**
 */
wxColour GradientStop::getWxColor() const {
  return color_ ? color_->getColor() : wxTransparentColour;
}
/**
 */
void GradientStop::update() {
  setName(wxString::FromDouble(pos_));
  setBitmap(color_ ? color_->getBitmap() : GetNullBitmap());
  super::update();
}
/**
 */
void GradientStop::onCreate(const PaletteComponentPtr& palette) {
  auto& colors = palette->getItems<Color>();
  if(!colors.empty()) {
    color_ = colors.front();
  }
}
/**
 */
PropertyPtr GradientStop::createProperty() {
  auto property = PropertyOwner::createProperty(TYPE);
  property->appendMember("Color", color_);
  property->appendMember("Pos", pos_);
  return property;
}
}
