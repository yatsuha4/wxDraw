#include "wxdraw/gui/Renderer.hpp"

namespace wxdraw::gui {
/**
   コンストラクタ
*/
Renderer::Renderer(wxDC& dc)
  : context_(wxGraphicsContext::CreateFromUnknownDC(dc))
{
}
}
