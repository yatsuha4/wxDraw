#include "wxdraw/command/Command.hpp"

namespace wxdraw::command {
/**
   コンストラクタ
   @param name 名前
   @param mainFrame メインフレーム
*/
Command::Command(const wxString& name, MainFrame* mainFrame)
  : super(true, name), 
    mainFrame_(mainFrame)
{
}
}
