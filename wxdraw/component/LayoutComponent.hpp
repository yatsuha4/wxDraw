#pragma once

#include "wxdraw/component/Component.hpp"
#include "wxdraw/container/Layout.hpp"
#include "wxdraw/container/Rect.hpp"

namespace wxdraw::component {
/**
 */
class LayoutComponent
  : public Component<LayoutComponent>
{
  using super = Component<LayoutComponent>;

 public:
  static const char* TYPE;

 private:
  Layout size_;
  Layout pos_;
  glm::dvec2 alignment_;
  glm::dvec2 scale_;
  double rotate_;
  glm::dmat3 matrix_;
  Rect rect_;

 public:
  LayoutComponent(const NodePtr& node);
  LayoutComponent(const LayoutComponent& src, const NodePtr& node);
  ~LayoutComponent() override = default;

  WXDRAW_ACCESSOR(Size, size_);
  WXDRAW_ACCESSOR(Pos, pos_);
  WXDRAW_ACCESSOR(Alignment, alignment_);
  WXDRAW_ACCESSOR(Scale, scale_);
  WXDRAW_ACCESSOR(Rotate, rotate_);

  WXDRAW_GETTER(Matrix, matrix_);
  WXDRAW_GETTER(Rect, rect_);

  PropertyPtr generateProperty() override;

  void update() override;

 private:
  LayoutComponentPtr getParent();
};
}
