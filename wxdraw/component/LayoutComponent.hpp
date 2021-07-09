#pragma once

#include "wxdraw/component/Component.hpp"

namespace wxdraw::component {
/**
 */
class LayoutComponent
  : public Component
{
  using super = Component;

 private:
  struct Layout {
    glm::dvec2 alignment;
    glm::dvec2 offset;

    Layout() : alignment(0.0), offset(0.0) {}
    ~Layout() = default;
  };

 private:
  Layout size_;
  Layout pos_;
  glm::dvec2 scale_;
  double rotate_;
  glm::dmat3 matrix_;

 public:
  LayoutComponent(Node& node);
  ~LayoutComponent() override = default;

 protected:
  void onUpdate() override;
  void onBeginRender(Renderer& renderer) override;

 private:
  glm::dvec2 getSize() const;
  glm::dvec2 apply(const Layout& layout) const;
  LayoutComponentPtr getParent() const;
};
}
