#pragma once

#include "wxdraw/command/InsertCommand.hpp"

namespace wxdraw::gui {
/**
   メインフレーム
*/
class MainFrame
  : public wxFrame, 
    public InsertComponentCommand::Observer
{
  using super = wxFrame;

 private:
  Application& application_;
  wxAuiManager auiManager_;
  Canvas* canvas_;
  Outliner* outliner_;
  Inspector* inspector_;
  Palette* palette_;
  ProjectComponentPtr project_;
  wxString defaultPerspective_;
  wxCommandProcessor commandProcessor_;

  static const wxSize DEFAULT_SIZE;
  static const wxSize DEFAULT_OUTLINER_SIZE;
  static const wxSize DEFAULT_INSPECTOR_SIZE;
  static const wxSize DEFAULT_PALETTE_SIZE;

 public:
  MainFrame(Application& application);
  ~MainFrame() override;

  WXDRAW_GETTER(Outliner, outliner_);
  WXDRAW_GETTER(Inspector, inspector_);

  void onSelectNode(const NodePtr& node);
  const NodePtr& getSelectNode() const;
  WXDRAW_GETTER(Project, project_);

  void update();

  bool submitCommand(wxCommand* command);

  template<class CommandType, class... Args>
  bool submitCommand(Args&&... args) {
    return submitCommand(new CommandType(args...));
  }

  void doInsert(const ComponentBasePtr& component, 
                const std::tuple<NodePtr>& args) override;
  std::tuple<NodePtr> doRemove(const ComponentBasePtr& component) override;

 private:
  void setupMenuBar();
  void onMenuOpen(wxMenuEvent& event);
  void onSelectMenu(wxCommandEvent& event);
  void onClose(wxCloseEvent& event);

  void open();
  bool save();

  void openProject(const NodePtr& project);
  bool closeProject();
  void saveProject(const ProjectComponentPtr& project);
  void onSelectFileExport();

  template<class T>
  bool createComponent() {
    if(auto node = getSelectNode()) {
      return submitCommand<InsertComponentCommand>(this, T::template Create<T>(node), node);
    }
    return false;
  }
};
}
