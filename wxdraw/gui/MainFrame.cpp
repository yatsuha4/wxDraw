#include "wxdraw/command/InsertNode.hpp"
#include "wxdraw/gui/Canvas.hpp"
#include "wxdraw/gui/Inspector.hpp"
#include "wxdraw/gui/MainFrame.hpp"
#include "wxdraw/gui/Outliner.hpp"
#include "wxdraw/node/Project.hpp"
#include "wxdraw/node/RootNode.hpp"

namespace wxdraw::gui {
enum {
  MENU_TOP = wxID_HIGHEST, 
  MENU_FILE_NEW, 
  MENU_FILE_OPEN, 
  MENU_FILE_SAVE, 
  MENU_FILE_SAVE_AS, 
  MENU_FILE_QUIT, 
  MENU_EDIT_APPEND, 
  MENU_EDIT_APPEND_LAYER, 
  MENU_EDIT_APPEND_RECTANGLE, 
  MENU_EDIT_APPEND_ELLIPSE, 
  MENU_EDIT_UNDO, 
  MENU_EDIT_REDO
};
const wxSize MainFrame::DEFAULT_SIZE(960, 640);

/**
   コンストラクタ
   @param application アプリケーション
*/
MainFrame::MainFrame(Application& application)
  : super(nullptr, wxID_ANY, "wxDraw", wxDefaultPosition, DEFAULT_SIZE), 
    application_(application), 
    auiManager_(this), 
    canvas_(new Canvas(this, *this)), 
    outliner_(new Outliner(this, *this)), 
    inspector_(new Inspector(this, *this))
{
  setupMenuBar();
  auiManager_.AddPane(canvas_, wxAuiPaneInfo().Caption("Canvas").CenterPane());
  auiManager_.AddPane(outliner_, wxAuiPaneInfo().Caption("Outliner").Left());
  auiManager_.AddPane(inspector_, wxAuiPaneInfo().Caption("Inspector").Right());
  auiManager_.Update();
}
/**
   デストラクタ
*/
MainFrame::~MainFrame() {
  auiManager_.UnInit();
}
/**
   コマンドを実行する
   @param command コマンド
*/
bool MainFrame::submitCommand(wxCommand* command) {
  return commandProcessor_.Submit(command);
}
/**
   ノードを挿入する
   @param node 挿入するノード
   @param parent 親ノード
   @param index 挿入位置
*/
void MainFrame::insertNode(const NodePtr& node, const NodePtr& parent, size_t index) {
  Node::Insert(node, parent, index);
  outliner_->insertNode(node, parent, index);
}
/**
   ノードを削除する
   @param node 削除するノード
*/
void MainFrame::removeNode(const NodePtr& node) {
  Node::Remove(node);
  outliner_->removeNode(node);
}
/**
   メニューバーのセットアップ
*/
void MainFrame::setupMenuBar() {
  auto menuBar = new wxMenuBar();
  {
    auto menu = new wxMenu();
    menu->Append(MENU_FILE_NEW, "New Project");
    menu->Append(MENU_FILE_OPEN, "Open");
    menu->Append(MENU_FILE_SAVE, "Save");
    menu->Append(MENU_FILE_SAVE_AS, "Save as");
    menu->AppendSeparator();
    menu->Append(MENU_FILE_QUIT, "Quit");
    menuBar->Append(menu, "File");
  }
  {
    auto menu = new wxMenu();
    {
      auto subMenu = new wxMenu();
      subMenu->Append(MENU_EDIT_APPEND_LAYER, "Layer");
      subMenu->Append(MENU_EDIT_APPEND_RECTANGLE, "Rectangle");
      subMenu->Append(MENU_EDIT_APPEND_ELLIPSE, "Ellipse");
      menu->Append(MENU_EDIT_APPEND, "Append", subMenu);
    }
    menu->Append(MENU_EDIT_UNDO, "Undo");
    menu->Append(MENU_EDIT_REDO, "Redo");
    menuBar->Append(menu, "Edit");
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
  case MENU_FILE_NEW:
    submitCommand(new InsertNode(this, std::make_shared<Project>(), outliner_->getRootNode(), 0));
    break;
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
