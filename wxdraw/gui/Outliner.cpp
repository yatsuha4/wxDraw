#include "wxdraw/gui/Outliner.hpp"

namespace wxdraw::gui {
/**
   コンストラクタ
   @param parent 親
   @param mainFrame メインフレーム
*/
Outliner::Outliner(wxWindow* parent, MainFrame& mainFrame)
  : super(parent, wxID_ANY), 
    mainFrame_(mainFrame)
{
}
}
