#pragma once

#include "wxdraw/component/Component.hpp"

namespace wxdraw::component {
/**
   グラデーションリストコンポーネント
*/
class GradientListComponent
  : public Component<GradientListComponent>
{
  using super = Component<GradientListComponent>;

 public:
  static const char* TYPE;

 private:
  std::vector<GradientPtr> gradients_;

 public:
  GradientListComponent(const NodePtr& node);
  GradientListComponent(const GradientListComponent& src, const NodePtr& node);
  ~GradientListComponent() override = default;

  WXDRAW_GETTER(Gradients, gradients_);
};
}
