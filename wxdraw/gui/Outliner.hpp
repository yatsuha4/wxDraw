#pragma once

#include "wxdraw/command/InsertCommand.hpp"

namespace wxdraw::gui {
/**
   アウトライナ
*/
class Outliner
  : public wxTreeListCtrl
{
  using super = wxTreeListCtrl;

 public:
  class ClientData;
  class InsertCommandObserver;

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
      return submitInsertCommand<InsertCommand<Node>>(parent, node, index);
    }
    return false;
  }

  void createProject();
  void appendProject(const NodePtr& node);

  bool canCloneNode() const;
  void cloneNode();

  bool canRemoveNode() const;
  void removeNode();

  void doInsert(const NodePtr& parent, const NodePtr& node, size_t index);
  void doRemove(const NodePtr& parent, const NodePtr& node, size_t index);

 private:
  NodePtr getContainerNode() const;
  std::tuple<NodePtr, size_t> getInsertParent() const;

  void insertNode(const NodePtr& parent, const NodePtr& node, size_t index);
  void removeNode(const NodePtr& node);

  void onSelectionChanged(wxTreeListEvent& event);

  NodePtr getNode(const wxTreeListItem& item) const;

  template<class T>
  bool submitInsertCommand(const NodePtr& parent, const NodePtr& node, size_t index) {
    return mainFrame_->submitCommand<T>
      (std::make_shared<InsertCommandObserver>(this, parent), node, index);
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
/**
   挿入コマンドのオブザーバー
*/
class Outliner::InsertCommandObserver
  : public InsertCommand<Node>::Observer
{
 private:
  Outliner* outliner_;
  NodePtr parent_;

 public:
  InsertCommandObserver(Outliner* outliner, const NodePtr& parent);
  ~InsertCommandObserver() override = default;

  void doInsert(const NodePtr& node, size_t index) override;
  void doRemove(const NodePtr& node, size_t index) override;
};
}
