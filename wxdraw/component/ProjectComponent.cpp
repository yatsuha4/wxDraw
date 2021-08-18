#include "wxdraw/component/ProjectComponent.hpp"
#include "wxdraw/property/Property.hpp"

namespace wxdraw::component {
const char* ProjectComponent::TYPE = "Project";
/**
 */
ProjectComponent::ProjectComponent(const NodePtr& node)
  : super(TYPE, node)
{
}
/**
 */
ProjectComponent::ProjectComponent(const ProjectComponent& src, const NodePtr& node)
  : super(src, node)
{
}
/**
   @copydoc Object::generateProperty
*/
PropertyPtr ProjectComponent::generateProperty() {
  auto property = super::generateProperty();
  property->appendMember("FileName", fileName_);
  return property;
}
}
