#include "wxdraw/command/InsertComponentCommand.hpp"
#include "wxdraw/command/InsertNodeCommand.hpp"
#include "wxdraw/command/RemoveNodeCommand.hpp"
#include "wxdraw/component/BrushComponent.hpp"
#include "wxdraw/component/ContainerComponent.hpp"
#include "wxdraw/component/ExportComponent.hpp"
#include "wxdraw/component/ProjectComponent.hpp"
#include "wxdraw/file/XmlExporter.hpp"
#include "wxdraw/file/XmlImporter.hpp"
#include "wxdraw/gui/Canvas.hpp"
#include "wxdraw/gui/Inspector.hpp"
#include "wxdraw/gui/MainFrame.hpp"
#include "wxdraw/gui/Menu.hpp"
#include "wxdraw/gui/Outliner.hpp"
#include "wxdraw/node/Node.hpp"

namespace wxdraw::gui {
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
  project_ = node ? node->getParentComponent<ProjectComponent>() : nullptr;
  inspector_->show(node);
  canvas_->Refresh();
}
/**
   ノードを追加する
   @param node 挿入するノード
   @param parent 親ノード
*/
void MainFrame::appendNode(const NodePtr& node, const NodePtr& parent) {
  wxASSERT(parent);
  auto container = parent->getContainer();
  wxASSERT(container);
  insertNode(node, parent, container->getChildren().size());
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
 */
void MainFrame::appendComponent(const ComponentBasePtr& component, const NodePtr& node) {
  node->appendComponent(component);
  node->update();
  selectNode(node);
}
/**
 */
void MainFrame::removeComponent(const ComponentBasePtr& component) {
  auto node = component->getNode();
  node->removeComponent(component);
  node->update();
  selectNode(node);
}
/**
   メニューバーのセットアップ
*/
void MainFrame::setupMenuBar() {
  auto menuBar = new wxMenuBar();
  SetMenuBar(menuBar);
  {
    auto menu = new Menu();
    menu->Append(Menu::ID_FILE_NEW, "New Project");
    menu->Append(Menu::ID_FILE_OPEN, "Open");
    menu->Append(Menu::ID_FILE_SAVE, "Save");
    menu->Append(Menu::ID_FILE_SAVE_AS, "Save as");
    menu->AppendSeparator();
    menu->Append(Menu::ID_FILE_EXPORT, "Export");
    menu->AppendSeparator();
    menu->Append(Menu::ID_FILE_QUIT, "Quit");
    menuBar->Append(menu, "File");
  }
  {
    auto menu = new Menu(Menu::Type::EDIT);
    {
      auto subMenu = new Menu(Menu::Type::EDIT_NEW_NODE);
      subMenu->Append(Menu::ID_EDIT_APPEND_LAYER, "Layer");
      subMenu->Append(Menu::ID_EDIT_APPEND_RECTANGLE, "Rectangle");
      subMenu->Append(Menu::ID_EDIT_APPEND_ELLIPSE, "Ellipse");
      menu->Append(Menu::ID_EDIT_APPEND, "New Node", subMenu);
    }
    {
      auto subMenu = new Menu(Menu::Type::EDIT_NEW_COMPONENT);
      subMenu->Append(Menu::ID_EDIT_NEW_COMPONENT_PEN, "Pen");
      subMenu->Append(Menu::ID_EDIT_NEW_COMPONENT_BRUSH, "Brush");
      subMenu->Append(Menu::ID_EDIT_NEW_COMPONENT_EXPORT, "Export");
      menu->Append(Menu::ID_EDIT_NEW_COMPONENT, "New Component", subMenu);
    }
    menu->Append(Menu::ID_EDIT_REMOVE, "Remove");
    menu->Append(Menu::ID_EDIT_CLONE, "Clone");
    menu->AppendSeparator();
    menu->Append(Menu::ID_EDIT_UNDO, "Undo");
    menu->Append(Menu::ID_EDIT_REDO, "Redo");
    menuBar->Append(menu, "Edit");
  }
  {
    auto menu = new Menu();
    {
      auto perspectiveMenu = new Menu();
      perspectiveMenu->Append(Menu::ID_WINDOW_PERSPECTIVE_SAVE, "Save");
      perspectiveMenu->Append(Menu::ID_WINDOW_PERSPECTIVE_LOAD, "Load");
      perspectiveMenu->Append(Menu::ID_WINDOW_PERSPECTIVE_RESET, "Reset");
      menu->Append(Menu::ID_WINDOW_PERSPECTIVE, "Perspective", perspectiveMenu);
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
  auto project = getProject();
  switch(menu->getType()) {
  case Menu::Type::EDIT:
    {
      menu->Enable(Menu::ID_EDIT_REMOVE, node != nullptr);
      menu->Enable(Menu::ID_EDIT_CLONE, 
                   node && 
                   node->getParent() && 
                   node->getParent()->getContainer());
      menu->Enable(Menu::ID_EDIT_UNDO, project && project->getCommandProcessor().CanUndo());
      menu->Enable(Menu::ID_EDIT_REDO, project && project->getCommandProcessor().CanRedo());
    }
    break;
  case Menu::Type::EDIT_NEW_NODE:
    {
      auto enable = (getContainerNode() != nullptr);
      menu->Enable(Menu::ID_EDIT_APPEND_LAYER, enable);
      menu->Enable(Menu::ID_EDIT_APPEND_RECTANGLE, enable);
      menu->Enable(Menu::ID_EDIT_APPEND_ELLIPSE, enable);
    }
    break;
  case Menu::Type::EDIT_NEW_COMPONENT:
    {
      auto node = getSelectNode();
      menu->Enable(Menu::ID_EDIT_NEW_COMPONENT_BRUSH, 
                   node && !node->getComponent<BrushComponent>());
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
  case Menu::ID_FILE_NEW:
    appendNode(Node::CreateProject(), outliner_->getRootNode());
    break;
  case Menu::ID_FILE_OPEN:
    open();
    break;
  case Menu::ID_FILE_SAVE:
    break;
  case Menu::ID_FILE_SAVE_AS:
    saveAs();
    break;
  case Menu::ID_FILE_EXPORT:
    onSelectFileExport();
    break;
  case Menu::ID_FILE_QUIT:
    Close();
    break;
  case Menu::ID_EDIT_APPEND_LAYER:
    newNode(Node::CreateLayer());
    break;
  case Menu::ID_EDIT_APPEND_RECTANGLE:
    newNode(Node::CreateRectangle());
    break;
  case Menu::ID_EDIT_APPEND_ELLIPSE:
    newNode(Node::CreateEllipse());
    break;
  case Menu::ID_EDIT_REMOVE:
    submitCommand<RemoveNodeCommand>(getSelectNode());
    break;
  case Menu::ID_EDIT_CLONE:
    submitCommand<InsertNodeCommand>(Node::Clone(getSelectNode()), 
                                     getSelectNode()->getParent());
    break;
  case Menu::ID_EDIT_UNDO:
    getProject()->getCommandProcessor().Undo();
    break;
  case Menu::ID_EDIT_REDO:
    getProject()->getCommandProcessor().Redo();
    break;
  case Menu::ID_EDIT_NEW_COMPONENT_BRUSH:
    newComponent<BrushComponent>();
    break;
  case Menu::ID_WINDOW_PERSPECTIVE_RESET:
    SetSize(DEFAULT_SIZE);
    auiManager_.LoadPerspective(defaultPerspective_);
    break;
  default:
    break;
  }
}
/**
 */
NodePtr MainFrame::getContainerNode() const {
  if(auto node = getSelectNode()) {
    if(node->getContainer()) {
      return node;
    }
    if(auto parent = node->getParent()) {
      if(parent->getContainer()) {
        return parent;
      }
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
  if(auto project = getProject()) {
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
void MainFrame::saveProject(const ProjectComponentPtr& project) {
  XmlExporter exporter(project->getNode(), project->getFileName());
  if(exporter.save()) {
    project->getCommandProcessor().MarkAsSaved();
  }
}
/**
 */
void MainFrame::onSelectFileExport() {
  if(auto node = getSelectNode()) {
    if(auto component = node->getParentComponent<ExportComponent>()) {
      wxFileDialog dialog(this, wxFileSelectorPromptStr, 
                          component->getFileName().GetPath(), 
                          component->getFileName().GetName(), 
                          wxImage::GetImageExtWildcard(), 
                          wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
      if(dialog.ShowModal() == wxID_OK) {
        component->getFileName().Assign(dialog.GetPath());
        component->save();
      }
    }
  }
}
/**
   コマンドを実行する
   @param command コマンド
*/
bool MainFrame::submitCommand(wxCommand* command) {
  if(auto project = getProject()) {
    return project->getCommandProcessor().Submit(command);
  }
  return false;
}
/**
   ノードを生成する
   @param node ノード
*/
bool MainFrame::newNode(const NodePtr& node) {
  return submitCommand<InsertNodeCommand>(node, getContainerNode());
}
}
