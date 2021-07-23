#pragma once

#include "wxdraw/command/InsertCommand.hpp"

namespace wxdraw::gui {
/**
   アウトライナ
*/
class Outliner
  : public wxTreeListCtrl, 
    public InsertNodeCommand::Observer
{
  using super = wxTreeListCtrl;

 public:
  class ClientData;

 private:
  MainFrame* mainFrame_;
  NodePtr rootNode_;
  NodePtr selectNode_;

 public:
  Outliner(wxWindow* parent, MainFrame* mainFrame);
  ~Outliner() override = default;

  const NodePtr& getRootNode();

  void selectNode(const NodePtr& node);
  WXDRAW_GETTER(SelectNode, selectNode_);

  template<class T>
  bool createNode() {
    auto [parent, index] = getInsertParent();
    if(parent) {
      auto node = T::Create(parent);
      return submitInsertCommand<InsertNodeCommand>(node, parent, index);
    }
    return false;
  }

  void createProject();
  void appendProject(const NodePtr& node);

  bool canCloneNode() const;
  void cloneNode();

  bool canRemoveNode() const;
  void removeNode();

  void doInsert(const NodePtr& node, const std::tuple<NodePtr, size_t>& args) override;
  void doRemove(const NodePtr& node, const std::tuple<NodePtr, size_t>& args) override;

 private:
  NodePtr getContainerNode() const;
  std::tuple<NodePtr, size_t> getInsertParent() const;

  void insertNode(const NodePtr& node, const NodePtr& parent, size_t index);
  void removeNode(const NodePtr& node);

  void onSelectionChanged(wxTreeListEvent& event);

  NodePtr getNode(const wxTreeListItem& item) const;

  template<class T>
  bool submitInsertCommand(const NodePtr& node, const NodePtr& parent, size_t index) {
    return mainFrame_->submitCommand<T>(this, node, parent, index);
  }
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
