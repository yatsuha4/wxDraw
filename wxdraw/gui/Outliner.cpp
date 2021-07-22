#include "wxdraw/component/ContainerComponent.hpp"
#include "wxdraw/gui/MainFrame.hpp"
#include "wxdraw/gui/Outliner.hpp"
#include "wxdraw/node/Node.hpp"

namespace wxdraw::gui {
/**
   コンストラクタ
   @param parent 親
   @param mainFrame メインフレーム
*/
Outliner::Outliner(wxWindow* parent, MainFrame* mainFrame)
  : super(parent, wxID_ANY), 
    mainFrame_(mainFrame)
{
  AppendColumn("Name");
  Bind(wxEVT_TREELIST_SELECTION_CHANGED, &Outliner::onSelectionChanged, this);
}
/**
 */
const NodePtr& Outliner::getRootNode() {
  if(!rootNode_) {
    rootNode_ = Node::CreateRoot();
    rootNode_->setItem(GetRootItem());
  }
  return rootNode_;
}
/**
 */
void Outliner::selectNode(const NodePtr& node) {
  for(auto item = GetItemParent(node->getItem()); item.IsOk(); item = GetItemParent(item)) {
    Expand(item);
  }
  Select(node->getItem());
}
/**
 */
void Outliner::createProject() {
  appendProject(Node::Project::Create(getRootNode()));
}
/**
 */
void Outliner::appendProject(const NodePtr& node) {
  submitInsertCommand<InsertCommand<Node>>(getRootNode(), node, 0);
}
/**
 */
void Outliner::doInsert(const NodePtr& parent, const NodePtr& node, size_t index) {
  Node::Insert(node, parent, index);
  node->update();
  insertNode(parent, node, index);
  selectNode(node);
}
/**
 */
bool Outliner::canCloneNode() const {
  return false;
}
/**
 */
void Outliner::cloneNode() {
}
/**
 */
bool Outliner::canRemoveNode() const {
  //return getSelectNode() != nullptr;
  return false;
}
/**
 */
void Outliner::removeNode() {
}
/**
 */
void Outliner::doRemove(const NodePtr& parent, const NodePtr& node, size_t index) {
  Node::Remove(node);
  removeNode(node);
}
/**
   新規ノードのコンテナを求める
   @return 新規ノードのコンテナ
*/
NodePtr Outliner::getContainerNode() const {
  if(auto node = getSelectNode()) {
    if(node->getContainer()) {
      return node;
    }
    if(auto parent = node->getParent()) {
      if(parent->getContainer()) {
        return parent;
      }
    }
  }
  return nullptr;
}
/**
   ノードを挿入する
*/
void Outliner::insertNode(const NodePtr& parent, const NodePtr& node, size_t index) {
  wxASSERT(!node->getItem().IsOk());
  wxASSERT(parent->getItem().IsOk());
  //wxASSERT(index <= parent->getChildren().size());
  wxTreeListItem item;
  if(index == 0) {
    item = PrependItem(parent->getItem(), node->getName());
  }
  else {
    auto prev = GetFirstChild(parent->getItem());
    for(size_t i = 1; i < index; i++) {
      prev = GetNextSibling(prev);
    }
    item = InsertItem(parent->getItem(), prev, node->getName());
  }
  SetItemData(item, new ClientData(node));
  node->setItem(item);
  if(auto container = node->getContainer()) {
    for(size_t i = 0; i < container->getChildren().size(); i++) {
      insertNode(container->getChildren().at(i), node, i);
    }
  }
}
/**
 */
void Outliner::removeNode(const NodePtr& node) {
  wxASSERT(node->getItem().IsOk());
  DeleteItem(node->getItem());
  node->setItem(wxTreeListItem());
}
/**
 */
void Outliner::onSelectionChanged(wxTreeListEvent& event) {
  auto node = getNode(event.GetItem());
  selectNode_ = node;
  mainFrame_->onSelectNode(node);
}
/**
 */
NodePtr Outliner::getNode(const wxTreeListItem& item) const {
  if(item.IsOk()) {
    if(auto data = static_cast<ClientData*>(GetItemData(item))) {
      return data->getNode();
    }
  }
  return nullptr;
}
/**
 */
Outliner::ClientData::ClientData(const NodePtr& node)
  : node_(node)
{
}
/**
 */
Outliner::InsertCommandObserver::InsertCommandObserver(Outliner* outliner, 
                                                       const NodePtr& parent)
  : outliner_(outliner), 
    parent_(parent)
{}
/**
 */
void Outliner::InsertCommandObserver::doInsert(const NodePtr& node, size_t index) {
  outliner_->doInsert(parent_, node, index);
}
/**
 */
void Outliner::InsertCommandObserver::doRemove(const NodePtr& node, size_t index) {
  outliner_->doRemove(parent_, node, index);
}
}
