#include "wxdraw/node/Layer.hpp"

namespace wxdraw::node {
/**
 */
void Layer::draw(wxGraphicsContext& gc) {
  gc.BeginLayer(opacity_);
  super::draw(gc);
  gc.EndLayer();
}
}
