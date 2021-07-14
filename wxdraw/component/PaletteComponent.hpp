#pragma once

#include "wxdraw/component/Component.hpp"
#include "wxdraw/container/Color.hpp"

namespace wxdraw::component {
/**
   カラーパレットコンポーネント
*/
class PaletteComponent
  : public Component<PaletteComponent>
{
  using super = Component<PaletteComponent>;

 public:
  static const char* TYPE;

 private:
  std::vector<Color> colors_;

 public:
  PaletteComponent(const NodePtr& node);
  PaletteComponent(const PaletteComponent& src, const NodePtr& node);
  ~PaletteComponent() override = default;

  WXDRAW_GETTER(Colors, colors_);
  std::vector<const char*> getLabels() const;
};
}
