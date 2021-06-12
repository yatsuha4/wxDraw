#include "wxdraw/gui/Renderer.hpp"
#include "wxdraw/node/Layer.hpp"

namespace wxdraw::node {
/**
 */
void Layer::render(Renderer& renderer) {
  renderer.getContext().BeginLayer(opacity_);
  super::render(renderer);
  renderer.getContext().EndLayer();
}
}
