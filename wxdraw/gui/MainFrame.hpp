#pragma once

#include "wxdraw/node/Node.hpp"

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
  NodePtr selectNode_;
  wxString defaultPerspective_;

  static const wxSize DEFAULT_SIZE;
  static const wxSize DEFAULT_OUTLINER_SIZE;
  static const wxSize DEFAULT_INSPECTOR_SIZE;

 public:
  MainFrame(Application& application);
  ~MainFrame() override;

  WXDRAW_GETTER(Outliner, outliner_);

  void selectNode(const NodePtr& node);
  WXDRAW_GETTER(SelectNode, selectNode_);
  ProjectNodePtr getSelectProject() const;

  template<class CommandType, class... Args>
  bool submitCommand(Args&&... args) {
    return submitCommand(new CommandType(this, args...));
  }

  void appendNode(const NodePtr& node, const NodePtr& parent);
  void insertNode(const NodePtr& node, const NodePtr& parent, size_t index);
  void removeNode(const NodePtr& node);
  void updateNode(const NodePtr& node);

 private:
  void setupMenuBar();
  void onMenuEdit(wxMenuEvent& event);
  void onMenuEditAppend(wxMenuEvent& event);
  void onSelectMenu(wxCommandEvent& event);

  template<class T>
  bool canAppendNode() const {
    return getAppendParent(typeid(T)) != nullptr;
  }

  NodePtr getAppendParent(const std::type_info& type) const;

  void open();
  void saveAs();
  void saveProject(const ProjectNodePtr& project);

  bool submitCommand(wxCommand* command);

  template<class T>
  bool appendNode() {
    return submitCommand<InsertNodeCommand>(std::make_shared<T>(), 
                                            getAppendParent(typeid(T)));
  }
};
}
