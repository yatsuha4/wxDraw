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
  PaletteComponentPtr paletteComponent_;
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
  WXDRAW_GETTER(PaletteComponent, paletteComponent_);

  template<class CommandType, class... Args>
  bool submitCommand(Args&&... args) {
    return submitCommand(new CommandType(args...));
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

  template<class T>
  bool createNode() {
    if(auto parent = getContainerNode()) {
      auto node = T::Create(parent);
      return submitCommand<InsertNodeCommand>(this, node, parent);
    }
    return false;
  }

  template<class T>
  bool createComponent() {
    if(auto node = getSelectNode()) {
      return submitCommand<InsertComponentCommand>(this, T::template Create<T>(node), node);
    }
    return false;
  }
};
}
