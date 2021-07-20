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
  cloneItems<Font, Color, Gradient, Pen, Brush>(src);
}
/**
 */
void PaletteComponent::onNew() {
  super::onNew();
  appendItem<Font>("Default", *wxNORMAL_FONT);
  appendItem<Pen>("Transparent");
  appendItem<Pen>("Default", appendItem<Color>("Pen", *wxBLACK));
  appendItem<Brush>("Transparent");
  appendItem<Brush>("Default", appendItem<Color>("Brush", *wxWHITE));
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
void PaletteComponent::getItem(size_t index, ColorBasePtr& item) const {
  if(auto color = getItem<Color>(index)) {
    item = color;
  }
  else if(auto gradient = getItem<Gradient>(index - colors_.size())) {
    item = gradient;
  }
  else {
    item = nullptr;
  }
}
/**
 */
GradientPtr PaletteComponent::cloneItem(const PaletteComponent& palette, 
                                        const GradientPtr& src) const {
  auto dst = std::make_shared<Gradient>(*src);
  for(auto& stop : dst->getStops()) {
    stop->setColor(getItem<Color>(palette.getIndex(stop->getColor())));
  }
  return dst;
}
/**
 */
PenPtr PaletteComponent::cloneItem(const PaletteComponent& palette, 
                                   const PenPtr& src) const {
  auto dst = std::make_shared<Pen>(*src);
  dst->setColor(getItem<ColorBase>(palette.getIndex(src->getColor())));
  return dst;
}
/**
 */
BrushPtr PaletteComponent::cloneItem(const PaletteComponent& palette, 
                                     const BrushPtr& src) const {
  auto dst = std::make_shared<Brush>(*src);
  dst->setColor(getItem<ColorBase>(palette.getIndex(src->getColor())));
  return dst;
}
}
