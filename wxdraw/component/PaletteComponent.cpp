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
}
