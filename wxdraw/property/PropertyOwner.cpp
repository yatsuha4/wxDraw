#include "wxdraw/property/Property.hpp"
#include "wxdraw/property/PropertyOwner.hpp"

namespace wxdraw::property {
/**
   プロパティを生成する
*/
PropertyPtr PropertyOwner::createProperty(const std::string& type) {
  return std::make_shared<Property>(type, shared_from_this());
}
}
