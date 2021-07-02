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
 */
Application* Application::GetInstance() {
  return static_cast<Application*>(super::GetInstance());
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
