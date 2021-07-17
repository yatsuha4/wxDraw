#pragma once

namespace wxdraw::gui {
/**
   メインフレーム
*/
class MainFrame
  : public wxFrame
{
  using super = wxFrame;

 private:
  Application& application_;
  wxAuiManager auiManager_;
  Canvas* canvas_;
  Outliner* outliner_;
  Inspector* inspector_;
  Palette* palette_;
  NodePtr selectNode_;
  ProjectComponentPtr project_;
  wxString defaultPerspective_;

  static const wxSize DEFAULT_SIZE;
  static const wxSize DEFAULT_OUTLINER_SIZE;
  static const wxSize DEFAULT_INSPECTOR_SIZE;
  static const wxSize DEFAULT_PALETTE_SIZE;

 public:
  MainFrame(Application& application);
  ~MainFrame() override;

  WXDRAW_GETTER(Outliner, outliner_);
  WXDRAW_GETTER(Inspector, inspector_);

  void selectNode(const NodePtr& node);
  WXDRAW_GETTER(SelectNode, selectNode_);
  WXDRAW_GETTER(Project, project_);

  template<class CommandType, class... Args>
  bool submitCommand(Args&&... args) {
    return submitCommand(new CommandType(this, args...));
  }

  void appendNode(const NodePtr& node, const NodePtr& parent);
  void insertNode(const NodePtr& node, const NodePtr& parent, size_t index);
  void removeNode(const NodePtr& node);

  void appendComponent(const ComponentBasePtr& component, const NodePtr& node);
  void removeComponent(const ComponentBasePtr& component);

  void update();

 private:
  void setupMenuBar();
  void onMenuOpen(wxMenuEvent& event);
  void onSelectMenu(wxCommandEvent& event);

  NodePtr getContainerNode() const;

  void open();
  void saveAs();
  void saveProject(const ProjectComponentPtr& project);
  void onSelectFileExport();

  bool submitCommand(wxCommand* command);

  bool newNode(const NodePtr& node);

  template<class T>
  bool newComponent() {
    if(auto node = getSelectNode()) {
      return submitCommand<InsertComponentCommand>(std::make_shared<T>(node), node);
    }
    return false;
  }
};
}
