#include "wxdraw/gui/Canvas.hpp"
#include "wxdraw/gui/MainFrame.hpp"

namespace wxdraw::gui {
enum {
  MENU_TOP = wxID_HIGHEST, 
  MENU_FILE_OPEN, 
  MENU_FILE_SAVE, 
  MENU_FILE_SAVE_AS, 
  MENU_FILE_QUIT
};
/**
   コンストラクタ
   @param application アプリケーション
*/
MainFrame::MainFrame(Application& application)
  : super(nullptr, wxID_ANY, "wxDraw"), 
    application_(application), 
    auiManager_(this), 
    canvas_(new Canvas(this, *this))
{
  setupMenuBar();
  auiManager_.AddPane(canvas_, wxCENTER, wxT("Canvas"));
  auiManager_.Update();
}
/**
   デストラクタ
*/
MainFrame::~MainFrame() {
  auiManager_.UnInit();
}
/**
   メニューバーのセットアップ
*/
void MainFrame::setupMenuBar() {
  auto menuBar = new wxMenuBar();
  {
    auto menu = new wxMenu();
    menu->Append(MENU_FILE_OPEN, "Open");
    menu->Append(MENU_FILE_SAVE, "Save");
    menu->Append(MENU_FILE_SAVE_AS, "Save as");
    menu->AppendSeparator();
    menu->Append(MENU_FILE_QUIT, "Quit");
    menuBar->Append(menu, "File");
  }
  SetMenuBar(menuBar);
  Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::onSelectMenu, this);
}
/**
   メニュー選択
   @param event イベント
*/
void MainFrame::onSelectMenu(wxCommandEvent& event) {
  switch(event.GetId()) {
  case MENU_FILE_OPEN:
    break;
  case MENU_FILE_SAVE:
    break;
  case MENU_FILE_SAVE_AS:
    break;
  case MENU_FILE_QUIT:
    Close();
    break;
  default:
    break;
  }
}
}
