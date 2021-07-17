#include "wxdraw/component/PaletteComponent.hpp"

namespace wxdraw::component {
const char* PaletteComponent::TYPE = "Palette";
/**
 */
PaletteComponent::PaletteComponent(const NodePtr& node)
  : super(TYPE, node)
{
}
/**
 */
PaletteComponent::PaletteComponent(const PaletteComponent& src, const NodePtr& node)
  : super(src, node)
{
}
/**
 */
size_t PaletteComponent::getIndex(const PenPtr& pen) const {
  return std::distance(pens_.begin(), 
                       std::find(pens_.begin(), pens_.end(), pen));
}
/**
 */
size_t PaletteComponent::getIndex(const BrushPtr& brush) const {
  return std::distance(brushes_.begin(), 
                       std::find(brushes_.begin(), brushes_.end(), brush));
}
/**
 */
size_t PaletteComponent::getIndex(const GradientPtr& gradient) const {
  return std::distance(gradients_.begin(), 
                       std::find(gradients_.begin(), gradients_.end(), gradient));
}
/**
 */
size_t PaletteComponent::getIndex(const ColorPtr& color) const {
  return std::distance(colors_.begin(), 
                       std::find(colors_.begin(), colors_.end(), color));
}
}
