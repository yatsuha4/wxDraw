#include "wxdraw/command/InsertNode.hpp"
#include "wxdraw/file/XmlExporter.hpp"
#include "wxdraw/gui/Canvas.hpp"
#include "wxdraw/gui/Inspector.hpp"
#include "wxdraw/gui/MainFrame.hpp"
#include "wxdraw/gui/Outliner.hpp"
#include "wxdraw/node/EllipseNode.hpp"
#include "wxdraw/node/LayerNode.hpp"
#include "wxdraw/node/Project.hpp"
#include "wxdraw/node/RectangleNode.hpp"
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
  MENU_EDIT_REDO, 
  MENU_WINDOW_PERSPECTIVE, 
  MENU_WINDOW_PERSPECTIVE_SAVE, 
  MENU_WINDOW_PERSPECTIVE_LOAD, 
  MENU_WINDOW_PERSPECTIVE_RESET
};
const wxSize MainFrame::DEFAULT_SIZE(960, 640);
const wxSize MainFrame::DEFAULT_OUTLINER_SIZE(240, 640);
const wxSize MainFrame::DEFAULT_INSPECTOR_SIZE(240, 640);

/**
   コンストラクタ
   @param application アプリケーション
*/
MainFrame::MainFrame(Application& application)
  : super(nullptr, wxID_ANY, "wxDraw", wxDefaultPosition, DEFAULT_SIZE), 
    application_(application), 
    auiManager_(this), 
    canvas_(new Canvas(this, this)), 
    outliner_(new Outliner(this, *this)), 
    inspector_(new Inspector(this, this))
{
  setupMenuBar();
  auiManager_.AddPane(canvas_, wxAuiPaneInfo().Caption("Canvas").CenterPane());
  auiManager_.AddPane(outliner_, 
                      wxAuiPaneInfo().Caption("Outliner").Left().
                      BestSize(DEFAULT_OUTLINER_SIZE));
  auiManager_.AddPane(inspector_, 
                      wxAuiPaneInfo().Caption("Inspector").Right().
                      BestSize(DEFAULT_INSPECTOR_SIZE));
  auiManager_.Update();
  defaultPerspective_ = auiManager_.SavePerspective();
}
/**
   デストラクタ
*/
MainFrame::~MainFrame() {
  auiManager_.UnInit();
}
/**
   ノードを選択する
   @param node ノード
*/
void MainFrame::selectNode(const NodePtr& node) {
  selectNode_ = node;
  inspector_->show(node);
  canvas_->Refresh();
}
/**
   ノードを挿入する
   @param node 挿入するノード
   @param parent 親ノード
   @param index 挿入位置
*/
void MainFrame::insertNode(const NodePtr& node, const NodePtr& parent, size_t index) {
  Node::Insert(node, parent, index);
  node->update();
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
 */
void MainFrame::updateNode(const NodePtr& node) {
  node->update();
  canvas_->Refresh();
}
/**
   メニューバーのセットアップ
*/
void MainFrame::setupMenuBar() {
  auto menuBar = new wxMenuBar();
  SetMenuBar(menuBar);
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
      subMenu->Bind(wxEVT_MENU_OPEN, &MainFrame::onMenuEditAppend, this);
    }
    menu->Append(MENU_EDIT_UNDO, "Undo");
    menu->Append(MENU_EDIT_REDO, "Redo");
    menuBar->Append(menu, "Edit");
  }
  {
    auto menu = new wxMenu();
    {
      auto perspectiveMenu = new wxMenu();
      perspectiveMenu->Append(MENU_WINDOW_PERSPECTIVE_SAVE, "Save");
      perspectiveMenu->Append(MENU_WINDOW_PERSPECTIVE_LOAD, "Load");
      perspectiveMenu->Append(MENU_WINDOW_PERSPECTIVE_RESET, "Reset");
      menu->Append(MENU_WINDOW_PERSPECTIVE, "Perspective", perspectiveMenu);
    }
    menuBar->Append(menu, "Window");
  }
  Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::onSelectMenu, this);
}
/**
 */
void MainFrame::onMenuEditAppend(wxMenuEvent& event) {
  auto menu = event.GetMenu();
  menu->Enable(MENU_EDIT_APPEND_LAYER, canAppendNode<LayerNode>());
  menu->Enable(MENU_EDIT_APPEND_RECTANGLE, canAppendNode<RectangleNode>());
  menu->Enable(MENU_EDIT_APPEND_ELLIPSE, canAppendNode<EllipseNode>());
}
/**
   メニュー選択
   @param event イベント
*/
void MainFrame::onSelectMenu(wxCommandEvent& event) {
  switch(event.GetId()) {
  case MENU_FILE_NEW:
    submitCommand<InsertNode>(std::make_shared<Project>(), outliner_->getRootNode(), 0);
    break;
  case MENU_FILE_OPEN:
    break;
  case MENU_FILE_SAVE:
    break;
  case MENU_FILE_SAVE_AS:
    saveAs();
    break;
  case MENU_FILE_QUIT:
    Close();
    break;
  case MENU_EDIT_APPEND_LAYER:
    submitCommand<InsertNode>(std::make_shared<LayerNode>(), getSelectNode(), 0);
    break;
  case MENU_EDIT_APPEND_RECTANGLE:
    submitCommand<InsertNode>(std::make_shared<RectangleNode>(), getSelectNode(), 0);
    break;
  case MENU_EDIT_APPEND_ELLIPSE:
    submitCommand<InsertNode>(std::make_shared<EllipseNode>(), getSelectNode(), 0);
    break;
  case MENU_WINDOW_PERSPECTIVE_RESET:
    SetSize(DEFAULT_SIZE);
    auiManager_.LoadPerspective(defaultPerspective_);
    break;
  default:
    break;
  }
}
/**
   名前をつけて保存
*/
void MainFrame::saveAs() {
  if(auto project = Node::GetParent<Project>(getSelectNode())) {
    wxFileDialog dialog(this, wxFileSelectorPromptStr, 
                        project->getFileName().GetPath(), 
                        project->getFileName().GetName(), 
                        "*.wxdraw", 
                        wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if(dialog.ShowModal() == wxID_OK) {
      project->getFileName().Assign(dialog.GetPath());
      saveProject(project);
    }
  }
}
/**
 */
void MainFrame::saveProject(const ProjectPtr& project) {
  XmlExporter exporter(project);
  wxFileOutputStream output(project->getFileName().GetFullPath());
  exporter.save(output);
}
/**
   コマンドを実行する
   @param command コマンド
*/
bool MainFrame::submitCommand(wxCommand* command) {
  return commandProcessor_.Submit(command);
}
}
