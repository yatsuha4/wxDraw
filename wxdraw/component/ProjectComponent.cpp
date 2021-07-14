#include "wxdraw/component/ProjectComponent.hpp"

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
}
