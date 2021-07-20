#include "wxdraw/object/Object.hpp"
#include "wxdraw/property/Property.hpp"
#include "wxdraw/property/PropertyMember.hpp"

namespace wxdraw::property {
/**
   コンストラクタ
*/
PropertyMember::PropertyMember(const PropertyPtr& property)
  : super(property->getObject()->getType()), 
    property_(property)
{
}
}
