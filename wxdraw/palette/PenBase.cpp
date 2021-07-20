#include "wxdraw/palette/ColorBase.hpp"
#include "wxdraw/palette/PenBase.hpp"
#include "wxdraw/property/Property.hpp"

namespace wxdraw::palette {
/**
 */
void PenBase::update() {
  setBitmap(color_ ? color_->getBitmap() : GetNullBitmap());
  super::update();
}
/**
 */
PropertyPtr PenBase::createProperty() {
  auto property = super::createProperty();
  property->appendMember("Name", getName());
  property->appendMember("Color", color_);
  return property;
}
}
