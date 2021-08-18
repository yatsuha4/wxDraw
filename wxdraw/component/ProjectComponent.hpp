#pragma once

#include "wxdraw/component/Component.hpp"

namespace wxdraw::component {
/**
 */
class ProjectComponent
  : public Component<ProjectComponent>
{
  using super = Component<ProjectComponent>;

 public:
  static const char* TYPE;

 private:
  wxFileName fileName_;

 public:
  ProjectComponent(const NodePtr& node);
  ProjectComponent(const ProjectComponent& src, const NodePtr& node);
  ~ProjectComponent() override = default;

  WXDRAW_ACCESSOR(FileName, fileName_);

  PropertyPtr generateProperty() override;
};
}
