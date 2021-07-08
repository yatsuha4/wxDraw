﻿#pragma once

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
  wxCommandProcessor commandProcessor_;
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

  bool submitCommand(wxCommand* command);

  void insertNode(const NodePtr& node, const NodePtr& parent, size_t index);
  void removeNode(const NodePtr& node);

 private:
  void setupMenuBar();
  void onMenuEditAppend(wxMenuEvent& event);
  void onSelectMenu(wxCommandEvent& event);

  template<class T>
  bool canAppendNode() const {
    return getSelectNode() && getSelectNode()->canAppend(typeid(T));
  }
};
}