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
  NodePtr selectNode_;
  wxCommandProcessor commandProcessor_;

  static const wxSize DEFAULT_SIZE;

 public:
  MainFrame(Application& application);
  ~MainFrame() override;

  WXDRAW_GETTER(Outliner, outliner_);
  WXDRAW_GETTER(SelectNode, selectNode_);

  bool submitCommand(wxCommand* command);

  void insertNode(const NodePtr& node, const NodePtr& parent, size_t index);
  void removeNode(const NodePtr& node);

 private:
  void setupMenuBar();
  void onSelectMenu(wxCommandEvent& event);
};
}
