#include "wxdraw/component/PaletteComponent.hpp"

namespace wxdraw::component {
const char* PaletteComponent::TYPE = "Palette";
/**
 */
PaletteComponent::PaletteComponent(const NodePtr& node)
  : super(TYPE, node)
{
  colors_.emplace_back("Foreground", *wxWHITE);
  colors_.emplace_back("Background", *wxBLACK);
}
/**
 */
PaletteComponent::PaletteComponent(const PaletteComponent& src, const NodePtr& node)
  : super(src, node)
{
}
/**
 */
std::vector<const char*> PaletteComponent::getLabels() const {
  std::vector<const char*> labels;
  for(auto& color : colors_) {
    labels.push_back(color.label.c_str());
  }
  labels.push_back(nullptr);
  return labels;
}
}
