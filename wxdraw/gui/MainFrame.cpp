#include "wxdraw/component/BrushComponent.hpp"
#include "wxdraw/component/CompositionComponent.hpp"
#include "wxdraw/component/ContainerComponent.hpp"
#include "wxdraw/component/ExportComponent.hpp"
#include "wxdraw/component/PaletteComponent.hpp"
#include "wxdraw/component/PenComponent.hpp"
#include "wxdraw/component/ProjectComponent.hpp"
#include "wxdraw/file/XmlExporter.hpp"
#include "wxdraw/file/XmlImporter.hpp"
#include "wxdraw/gui/Canvas.hpp"
#include "wxdraw/gui/Inspector.hpp"
#include "wxdraw/gui/MainFrame.hpp"
#include "wxdraw/gui/Menu.hpp"
#include "wxdraw/gui/Outliner.hpp"
#include "wxdraw/gui/Palette.hpp"
#include "wxdraw/node/Node.hpp"

namespace wxdraw::gui {
const wxSize MainFrame::DEFAULT_SIZE(1200, 800);
const wxSize MainFrame::DEFAULT_OUTLINER_SIZE(240, 800);
const wxSize MainFrame::DEFAULT_INSPECTOR_SIZE(240, 800);
const wxSize MainFrame::DEFAULT_PALETTE_SIZE(720, 160);

/**
   コンストラクタ
   @param application アプリケーション
*/
MainFrame::MainFrame(Application& application)
  : super(nullptr, wxID_ANY, "wxDraw", wxDefaultPosition, DEFAULT_SIZE), 
    application_(application), 
    auiManager_(this), 
    canvas_(new Canvas(this, this)), 
    outliner_(new Outliner(this, this)), 
    inspector_(new Inspector(this, this)), 
    palette_(new Palette(this, this))
{
  setupMenuBar();
  auiManager_.AddPane(canvas_, wxAuiPaneInfo().Caption("Canvas").CenterPane());
  auiManager_.AddPane(outliner_, 
                      wxAuiPaneInfo().Caption("Outliner").Left().Layer(1).
                      BestSize(DEFAULT_OUTLINER_SIZE));
  auiManager_.AddPane(inspector_, 
                      wxAuiPaneInfo().Caption("Inspector").Right().Layer(1).
                      BestSize(DEFAULT_INSPECTOR_SIZE));
  auiManager_.AddPane(palette_, 
                      wxAuiPaneInfo().Caption("Palette").Bottom().
                      BestSize(DEFAULT_PALETTE_SIZE));
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
void MainFrame::onSelectNode(const NodePtr& node) {
  project_ = Node::GetParentComponent<ProjectComponent>(node);
  paletteComponent_ = Node::GetParentComponent<PaletteComponent>(node);
  palette_->setPaletteComponent(paletteComponent_);
  if(node) {
    inspector_->show(node->generateProperty());
  }
  update();
}
/**
 */
const NodePtr& MainFrame::getSelectNode() const {
  return outliner_->getSelectNode();
}
/**
 */
void MainFrame::doInsert(const ComponentBasePtr& component, 
                         const std::tuple<NodePtr>& args) {
  auto node = std::get<0>(args);
  node->appendComponent(component);
  outliner_->selectNode(node);
  inspector_->show(node->generateProperty());
}
/**
 */
void MainFrame::doRemove(const ComponentBasePtr& component, 
                         const std::tuple<NodePtr>& args) {
  auto node = std::get<0>(args);
  node->removeComponent(component);
  outliner_->selectNode(node);
  inspector_->show(node->generateProperty());
}
/**
   更新
*/
void MainFrame::update() {
  if(auto project = getProject()) {
    project->getNode()->update();
  }
  outliner_->update();
  inspector_->update();
  canvas_->Refresh();
  palette_->update();
}
/**
   メニューバーのセットアップ
*/
void MainFrame::setupMenuBar() {
  auto menuBar = new wxMenuBar();
  SetMenuBar(menuBar);
  {
    auto menu = new Menu();
    menu->Append(wxID_NEW);
    menu->Append(wxID_OPEN);
    menu->Append(wxID_SAVE);
    menu->Append(wxID_SAVEAS);
    menu->AppendSeparator();
    menu->Append(Menu::ID_FILE_EXPORT, "Export");
    menu->AppendSeparator();
    menu->Append(Menu::ID_FILE_QUIT, "Quit");
    menuBar->Append(menu, _("File"));
  }
  {
    auto menu = new Menu(Menu::Type::EDIT);
    menu->Append(wxID_UNDO);
    menu->Append(wxID_REDO);
    menu->AppendSeparator();
    menu->Append(wxID_CUT);
    menu->Append(wxID_COPY);
    menu->Append(wxID_PASTE);
    menu->Append(Menu::ID_EDIT_CLONE, _("Duplicate"));
    menu->Append(wxID_DELETE);
    commandProcessor_.SetEditMenu(menu);
    menuBar->Append(menu, _("Edit"));
  }
  {
    auto menu = new Menu(Menu::Type::NODE);
    menu->Append(Menu::ID_NODE_RECTANGLE, _("Rectangle"));
    menu->Append(Menu::ID_NODE_ELLIPSE, _("Ellipse"));
    menu->Append(Menu::ID_NODE_TEXT, _("Text"));
    menu->AppendSeparator();
    menu->Append(Menu::ID_NODE_VIEW, _("View"));
    menu->Append(Menu::ID_NODE_GROUP, _("Group"));
    menu->Append(Menu::ID_NODE_LAYER, _("Layer"));
    menu->AppendSeparator();
    menu->Append(Menu::ID_NODE_PROXY, _("Proxy"));
    menu->AppendSeparator();
    menu->Append(Menu::ID_NODE_EXPORT, _("Export"));
    menuBar->Append(menu, _("Node"));
  }
  {
    auto menu = new Menu(Menu::Type::COMPONENT);
    menu->Append(Menu::ID_COMPONENT_PEN, _("Pen"));
    menu->Append(Menu::ID_COMPONENT_BRUSH, _("Brush"));
    menu->Append(Menu::ID_COMPONENT_EXPORT, _("Export"));
    menu->AppendSeparator();
    menu->Append(Menu::ID_COMPONENT_COMPOSITION, _("Composition"));
    menuBar->Append(menu, _("Component"));
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
      menu->Enable(wxID_DELETE, outliner_->canRemoveNode());
      menu->Enable(Menu::ID_EDIT_CLONE, outliner_->canCloneNode());
      commandProcessor_.SetMenuStrings();
    }
    break;
  case Menu::Type::NODE:
    {
      bool enable = outliner_->canCreateNode();
      menu->Enable(Menu::ID_NODE_ELLIPSE, enable);
      menu->Enable(Menu::ID_NODE_EXPORT, enable);
      menu->Enable(Menu::ID_NODE_GROUP, enable);
      menu->Enable(Menu::ID_NODE_LAYER, enable);
      menu->Enable(Menu::ID_NODE_PROXY, enable);
      menu->Enable(Menu::ID_NODE_RECTANGLE, enable);
      menu->Enable(Menu::ID_NODE_TEXT, enable);
      menu->Enable(Menu::ID_NODE_VIEW, enable);
    }
    break;
  case Menu::Type::COMPONENT:
    {
      menu->Enable(Menu::ID_COMPONENT_PEN, 
                   node && node->canAppendComponent<PenComponent>());
      menu->Enable(Menu::ID_COMPONENT_BRUSH, 
                   node && node->canAppendComponent<BrushComponent>());
      menu->Enable(Menu::ID_COMPONENT_COMPOSITION, 
                   node && node->canAppendComponent<CompositionComponent>());
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
  case wxID_NEW:
    outliner_->createProject();
    break;
  case wxID_OPEN:
    open();
    break;
  case wxID_SAVE:
    break;
  case wxID_SAVEAS:
    saveAs();
    break;
  case Menu::ID_FILE_EXPORT:
    onSelectFileExport();
    break;
  case Menu::ID_FILE_QUIT:
  case wxID_EXIT:
    Close();
    break;
  case Menu::ID_NODE_LAYER:
    outliner_->createNode<Node::Layer>();
    break;
  case Menu::ID_NODE_PROXY:
    outliner_->createNode<Node::Proxy>();
    break;
  case Menu::ID_NODE_GROUP:
    outliner_->createNode<Node::Group>();
    break;
  case Menu::ID_NODE_RECTANGLE:
    outliner_->createNode<Node::Rectangle>();
    break;
  case Menu::ID_NODE_ELLIPSE:
    outliner_->createNode<Node::Ellipse>();
    break;
  case Menu::ID_NODE_TEXT:
    outliner_->createNode<Node::Text>();
    break;
  case Menu::ID_NODE_VIEW:
    outliner_->createNode<Node::View>();
    break;
  case Menu::ID_NODE_EXPORT:
    outliner_->createNode<Node::Export>();
    break;
  case wxID_DELETE:
    outliner_->removeNode();
    break;
  case Menu::ID_EDIT_CLONE:
    outliner_->cloneNode();
    break;
  case wxID_UNDO:
    if(commandProcessor_.Undo()) {
      update();
    }
    break;
  case wxID_REDO:
    if(commandProcessor_.Redo()) {
      update();
    }
    break;
  case Menu::ID_COMPONENT_PEN:
    createComponent<PenComponent>();
    break;
  case Menu::ID_COMPONENT_BRUSH:
    createComponent<BrushComponent>();
    break;
  case Menu::ID_COMPONENT_COMPOSITION:
    createComponent<CompositionComponent>();
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
   開く
*/
void MainFrame::open() {
  wxFileDialog dialog(this, wxFileSelectorPromptStr, wxEmptyString, wxEmptyString, 
                      "*.wxdraw", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
  if(dialog.ShowModal() == wxID_OK) {
    XmlImporter importer(dialog.GetPath());
    if(auto project = importer.load(nullptr)) {
      outliner_->appendProject(project);
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
    //project->getCommandProcessor().MarkAsSaved();
  }
}
/**
 */
void MainFrame::onSelectFileExport() {
  /*
  if(auto component = Node::GetParentComponent<ExportComponent>(getSelectNode())) {
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
  */
}
/**
   コマンドを実行する
   @param command コマンド
*/
bool MainFrame::submitCommand(wxCommand* command) {
  if(commandProcessor_.Submit(command)) {
    update();
    return true;
  }
  return false;
}
}
