#include "wxdraw/command/InsertNodeCommand.hpp"
#include "wxdraw/command/RemoveNodeCommand.hpp"
#include "wxdraw/file/XmlExporter.hpp"
#include "wxdraw/file/XmlImporter.hpp"
#include "wxdraw/gui/Canvas.hpp"
#include "wxdraw/gui/Inspector.hpp"
#include "wxdraw/gui/MainFrame.hpp"
#include "wxdraw/gui/Menu.hpp"
#include "wxdraw/gui/Outliner.hpp"
#include "wxdraw/node/EllipseNode.hpp"
#include "wxdraw/node/LayerNode.hpp"
#include "wxdraw/node/ProjectNode.hpp"
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
  MENU_EDIT_NEW_COMPONENT, 
  MENU_EDIT_NEW_COMPONENT_EXPORT, 
  MENU_EDIT_REMOVE, 
  MENU_EDIT_CLONE, 
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
   @return 選択中のプロジェクト
*/
ProjectNodePtr MainFrame::getSelectProject() const {
  return Node::GetParent<ProjectNode>(getSelectNode());
}
/**
   ノードを追加する
   @param node 挿入するノード
   @param parent 親ノード
*/
void MainFrame::appendNode(const NodePtr& node, const NodePtr& parent) {
  insertNode(node, parent, parent->getChildren().size());
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
  outliner_->selectNode(node);
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
    auto menu = new Menu();
    menu->Append(MENU_FILE_NEW, "New Project");
    menu->Append(MENU_FILE_OPEN, "Open");
    menu->Append(MENU_FILE_SAVE, "Save");
    menu->Append(MENU_FILE_SAVE_AS, "Save as");
    menu->AppendSeparator();
    menu->Append(MENU_FILE_QUIT, "Quit");
    menuBar->Append(menu, "File");
  }
  {
    auto menu = new Menu(Menu::Type::Edit);
    {
      auto subMenu = new Menu(Menu::Type::Edit_NewNode);
      subMenu->Append(MENU_EDIT_APPEND_LAYER, "Layer");
      subMenu->Append(MENU_EDIT_APPEND_RECTANGLE, "Rectangle");
      subMenu->Append(MENU_EDIT_APPEND_ELLIPSE, "Ellipse");
      menu->Append(MENU_EDIT_APPEND, "New Node", subMenu);
    }
    {
      auto subMenu = new Menu(Menu::Type::Edit_NewComponent);
      subMenu->Append(MENU_EDIT_NEW_COMPONENT_EXPORT, "Export");
      menu->Append(MENU_EDIT_NEW_COMPONENT, "New Component", subMenu);
    }
    menu->Append(MENU_EDIT_REMOVE, "Remove");
    menu->Append(MENU_EDIT_CLONE, "Clone");
    menu->AppendSeparator();
    menu->Append(MENU_EDIT_UNDO, "Undo");
    menu->Append(MENU_EDIT_REDO, "Redo");
    menuBar->Append(menu, "Edit");
  }
  {
    auto menu = new Menu();
    {
      auto perspectiveMenu = new Menu();
      perspectiveMenu->Append(MENU_WINDOW_PERSPECTIVE_SAVE, "Save");
      perspectiveMenu->Append(MENU_WINDOW_PERSPECTIVE_LOAD, "Load");
      perspectiveMenu->Append(MENU_WINDOW_PERSPECTIVE_RESET, "Reset");
      menu->Append(MENU_WINDOW_PERSPECTIVE, "Perspective", perspectiveMenu);
    }
    menuBar->Append(menu, "Window");
  }
  Bind(wxEVT_MENU_OPEN, &MainFrame::onMenuOpen, this);
  Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::onSelectMenu, this);
}
/**
 */
void MainFrame::onMenuOpen(wxMenuEvent& event) {
  auto menu = static_cast<Menu*>(event.GetMenu());
  auto node = getSelectNode();
  auto project = getSelectProject();
  switch(menu->getType()) {
  case Menu::Type::Edit:
    {
      menu->Enable(MENU_EDIT_REMOVE, node != nullptr);
      menu->Enable(MENU_EDIT_CLONE, 
                   node && 
                   node->getParent() && 
                   node->getParent()->canAppend(typeid(*node)));
      menu->Enable(MENU_EDIT_UNDO, project && project->getCommandProcessor().CanUndo());
      menu->Enable(MENU_EDIT_REDO, project && project->getCommandProcessor().CanRedo());
    }
    break;
  case Menu::Type::Edit_NewNode:
    {
      menu->Enable(MENU_EDIT_APPEND_LAYER, canAppendNode<LayerNode>());
      menu->Enable(MENU_EDIT_APPEND_RECTANGLE, canAppendNode<RectangleNode>());
      menu->Enable(MENU_EDIT_APPEND_ELLIPSE, canAppendNode<EllipseNode>());
    }
    break;
  default:
    break;
  }
}
/**
   メニュー選択
   @param event イベント
*/
void MainFrame::onSelectMenu(wxCommandEvent& event) {
  switch(event.GetId()) {
  case MENU_FILE_NEW:
    appendNode(std::make_shared<ProjectNode>(), outliner_->getRootNode());
    break;
  case MENU_FILE_OPEN:
    open();
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
    appendNode<LayerNode>();
    break;
  case MENU_EDIT_APPEND_RECTANGLE:
    appendNode<RectangleNode>();
    break;
  case MENU_EDIT_APPEND_ELLIPSE:
    appendNode<EllipseNode>();
    break;
  case MENU_EDIT_REMOVE:
    submitCommand<RemoveNodeCommand>(getSelectNode());
    break;
  case MENU_EDIT_CLONE:
    submitCommand<InsertNodeCommand>(Node::Clone(getSelectNode()), 
                                     getSelectNode()->getParent());
    break;
  case MENU_EDIT_UNDO:
    if(auto project = getSelectProject()) {
      project->getCommandProcessor().Undo();
    }
    break;
  case MENU_EDIT_REDO:
    if(auto project = getSelectProject()) {
      project->getCommandProcessor().Redo();
    }
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
 */
NodePtr MainFrame::getAppendParent(const std::type_info& type) const {
  for(auto node = getSelectNode(); node; node = node->getParent()) {
    if(node->canAppend(type)) {
      return node;
    }
  }
  return nullptr;
}
/**
   開く
*/
void MainFrame::open() {
  wxFileDialog dialog(this, wxFileSelectorPromptStr, wxEmptyString, wxEmptyString, 
                      "*.wxdraw", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
  if(dialog.ShowModal() == wxID_OK) {
    XmlImporter importer(dialog.GetPath());
    if(auto project = importer.load()) {
      appendNode(project, outliner_->getRootNode());
    }
  }
}
/**
   名前をつけて保存
*/
void MainFrame::saveAs() {
  if(auto project = getSelectProject()) {
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
void MainFrame::saveProject(const ProjectNodePtr& project) {
  XmlExporter exporter(project);
  wxFileOutputStream output(project->getFileName().GetFullPath());
  if(exporter.save(output)) {
    project->getCommandProcessor().MarkAsSaved();
  }
}
/**
   コマンドを実行する
   @param command コマンド
*/
bool MainFrame::submitCommand(wxCommand* command) {
  if(auto project = getSelectProject()) {
    return project->getCommandProcessor().Submit(command);
  }
  return false;
}
}
