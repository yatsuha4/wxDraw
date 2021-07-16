#include "wxdraw/container/GradientColor.hpp"
#include "wxdraw/property/Property.hpp"

namespace wxdraw::container {
const char* GradientColor::TYPE = "GradientColor";
/**
   コンストラクタ
*/
GradientColor::GradientColor()
  : color_(wxTransparentColour), 
    pos_(0.0)
{
}
/**
 */
PropertyPtr GradientColor::createProperty() {
  auto property = std::make_shared<Property>(TYPE);
  property->appendMember("Color", color_);
  property->appendMember("Pos", pos_);
  return property;
}
/**
 */
GradientColor::operator wxGraphicsGradientStop() const {
  return wxGraphicsGradientStop(color_, pos_);
}
}
