#include "wxdraw/gui/Renderer.hpp"
#include "wxdraw/node/Layer.hpp"
#include "wxdraw/property/Property.hpp"

namespace wxdraw::node {
/**
 */
Layer::Layer()
  : super("Layer"), 
    opacity_(1.0)
{
  getProperty()->
    appendMember("Opacity", opacity_);
}
/**
 */
void Layer::render(Renderer& renderer) {
  renderer.getContext().BeginLayer(opacity_);
  super::render(renderer);
  renderer.getContext().EndLayer();
}
}
