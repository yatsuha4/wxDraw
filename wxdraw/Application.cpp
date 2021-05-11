#include "wxdraw/Application.hpp"
#include "wxdraw/gui/MainFrame.hpp"

namespace wxdraw {
/**
   コンストラクタ
*/
Application::Application()
  : mainFrame_(nullptr)
{
}
/**
   初期化
*/
bool Application::OnInit() {
  mainFrame_ = new MainFrame(*this);
  mainFrame_->Show();
  SetTopWindow(mainFrame_);
  return super::OnInit();
}
}
