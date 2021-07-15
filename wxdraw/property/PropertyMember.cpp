#include "wxdraw/property/Property.hpp"
#include "wxdraw/property/PropertyMember.hpp"

namespace wxdraw::property {
/**
   コンストラクタ
*/
PropertyMember::PropertyMember(const PropertyPtr& property)
  : super(property->getName()), 
    property_(property)
{
}
}
