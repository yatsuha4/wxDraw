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
void PaletteComponent::onCreate() {
  super::onCreate();
  auto penColor = appendColor("Pen", *wxBLACK);
  auto brushColor = appendColor("Brush", *wxWHITE);
  appendPen("Transparent");
  appendPen("Default", penColor);
  appendBrush("Transparent");
  appendBrush("Default", brushColor);
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
PenPtr PaletteComponent::appendPen(const wxString& name, const ColorPtr& color) {
  auto pen = std::make_shared<Pen>();
  pen->setName(name);
  pen->setColor(color);
  pens_.push_back(pen);
  return pen;
}
/**
 */
BrushPtr PaletteComponent::appendBrush(const wxString& name, const ColorPtr& color) {
  auto brush = std::make_shared<Brush>();
  brush->setName(name);
  brush->setColor(color);
  brushes_.push_back(brush);
  return brush;
}
/**
 */
ColorPtr PaletteComponent::appendColor(const wxString& name, const wxColour& color) {
  auto item = std::make_shared<Color>();
  item->setName(name);
  item->setColor(color);
  colors_.push_back(item);
  return item;
}
/**
 */
GradientPtr PaletteComponent::clone(const PaletteComponent& palette, 
                                    const GradientPtr& src) const {
  auto dst = std::make_shared<Gradient>(*src);
  for(auto& stop : dst->getStops()) {
    stop->setColor(getItem<Color>(palette.getIndex(stop->getColor())));
  }
  return dst;
}
}
