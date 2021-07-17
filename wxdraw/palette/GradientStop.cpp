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
  return wxGraphicsGradientStop(color_->getColor(), pos_);
}
/**
 */
void GradientStop::update() {
  super::update();
  setName(wxString::FromDouble(pos_));
  setBitmap(color_->getBitmap());
}
/**
 */
void GradientStop::onCreate(const PaletteComponentPtr& palette) {
  auto& colors = palette->getColors();
  if(colors.empty()) {
    colors.push_back(Create<Color>(palette));
  }
  color_ = colors.front();
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
