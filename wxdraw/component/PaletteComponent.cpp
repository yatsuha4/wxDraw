#include "wxdraw/component/PaletteComponent.hpp"
#include "wxdraw/palette/Brush.hpp"
#include "wxdraw/palette/Color.hpp"
#include "wxdraw/palette/Gradient.hpp"
#include "wxdraw/palette/GradientStop.hpp"
#include "wxdraw/palette/Pen.hpp"

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
  std::transform(src.colors_.begin(), src.colors_.end(), std::back_inserter(colors_), 
                 [](auto& color) {
                   return std::make_shared<Color>(*color);
                 });
  std::transform(src.gradients_.begin(), src.gradients_.end(), 
                 std::back_inserter(gradients_), 
                 [&](auto& gradient) {
                   return clone(src, gradient);
                 });
  std::transform(src.pens_.begin(), src.pens_.end(), 
                 std::back_inserter(pens_), 
                 [&](auto& pen) {
                   return clone(src, pen);
                 });
  std::transform(src.brushes_.begin(), src.brushes_.end(), 
                 std::back_inserter(brushes_), 
                 [&](auto& brush) {
                   return clone(src, brush);
                 });
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
/**
 */
size_t PaletteComponent::getIndex(const ColorBasePtr& color) const {
  auto iter = std::find(colors_.begin(), colors_.end(), color);
  return (iter != colors_.end())
    ? std::distance(colors_.begin(), iter)
    : (std::distance(gradients_.begin(), 
                     std::find(gradients_.begin(), gradients_.end(), color)) +
       colors_.size());
}
/**
 */
GradientPtr PaletteComponent::getGradient(size_t index) const {
  return (index < gradients_.size()) ? gradients_.at(index) : nullptr;
}
/**
 */
ColorPtr PaletteComponent::getColor(size_t index) const {
  return (index < colors_.size()) ? colors_.at(index) : nullptr;
}
/**
 */
ColorBasePtr PaletteComponent::getColorBase(size_t index) const {
  if(auto color = getColor(index)) {
    return color;
  }
  if(auto gradient = getGradient(index - colors_.size())) {
    return gradient;
  }
  return nullptr;
}
/**
 */
GradientPtr PaletteComponent::clone(const PaletteComponent& palette, 
                                    const GradientPtr& src) const {
  auto dst = std::make_shared<Gradient>(*src);
  for(auto& stop : dst->getStops()) {
    stop->setColor(getColor(palette.getIndex(stop->getColor())));
  }
  return dst;
}
}
