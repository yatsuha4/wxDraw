#include "wxdraw/gui/Canvas.hpp"

namespace wxdraw::gui {
/**
   コンストラクタ
   @param parent 親
   @param mainFrame メインフレーム
*/
Canvas::Canvas(wxWindow* parent, MainFrame& mainFrame)
  : super(parent), 
    mainFrame_(mainFrame)
{
  SetDoubleBuffered(true);
}
/**
   描画
*/
void Canvas::OnDraw(wxDC& dc) {
  super::OnDraw(dc);
}
}
