#pragma once

namespace wxdraw::gui {
/**
   アウトライナ
*/
class Outliner
  : public wxTreeListCtrl
{
  using super = wxTreeListCtrl;

 private:
  class ClientData;

 private:
  MainFrame& mainFrame_;
  RootNodePtr rootNode_;

 public:
  Outliner(wxWindow* parent, MainFrame& mainFrame);
  ~Outliner() override = default;

  const RootNodePtr& getRootNode();
  void insertNode(const NodePtr& node, const NodePtr& parent, size_t index);
  void removeNode(const NodePtr& node);

 private:
  void onSelectionChanged(wxTreeListEvent& event);

  NodePtr getNode(const wxTreeListItem& item) const;
};
/**
 */
class Outliner::ClientData
  : public wxClientData
{
 private:
  NodePtr node_;

 public:
  ClientData(const NodePtr& node);
  ~ClientData() override = default;

  WXDRAW_GETTER(Node, node_);
};
}
