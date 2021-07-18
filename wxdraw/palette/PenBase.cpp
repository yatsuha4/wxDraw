#include "wxdraw/palette/ColorBase.hpp"
#include "wxdraw/palette/PenBase.hpp"
#include "wxdraw/property/Property.hpp"

namespace wxdraw::palette {
/**
 */
void PenBase::update() {
  super::update();
  setBitmap(color_ ? color_->getBitmap() : GetNullBitmap());
}
/**
 */
PropertyPtr PenBase::createProperty(const char* type) {
  auto property = PropertyOwner::createProperty(type);
  property->appendMember("Name", getName());
  property->appendMember("Color", color_);
  return property;
}
}
