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
  submitInsertCommand<InsertNodeCommand>(node, getRootNode(), 0);
}
/**
 */
void Outliner::doInsert(const NodePtr& node, const std::tuple<NodePtr, size_t>& args) {
  auto parent = std::get<0>(args);
  auto index = std::get<1>(args);
  parent->getContainer()->getChildren().insert(index, node);
  node->update();
  insertNode(node, parent, index);
  selectNode(node);
}
/**
 */
bool Outliner::canCloneNode() const {
  if(auto node = getSelectNode()) {
    if(auto parent = node->getParent()) {
      return parent->getContainer() != nullptr;
    }
  }
  return false;
}
/**
 */
void Outliner::cloneNode() {
  if(auto node = getSelectNode()) {
    if(auto parent = node->getParent()) {
      if(auto container = parent->getContainer()) {
        submitInsertCommand<InsertNodeCommand>
          (Node::Clone(*node, parent), 
           parent, 
           container->getChildren().getIndex(node) + 1);
      }
    }
  }
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
void Outliner::doRemove(const NodePtr& node, const std::tuple<NodePtr, size_t>& args) {
  auto parent = std::get<0>(args);
  parent->getContainer()->getChildren().remove(node);
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
   新規ノードのコンテナを求める
   @return 新規ノードのコンテナ
*/
std::tuple<NodePtr, size_t> Outliner::getInsertParent() const {
  if(auto node = getSelectNode()) {
    if(auto container = node->getContainer()) {
      return { node, container->getChildren().size() };
    }
    else if(auto parent = node->getParent()) {
      if(auto container = parent->getContainer()) {
        return { parent, container->getChildren().getIndex(node) + 1 };
      }
    }
  }
  return { nullptr, 0 };
}
/**
   ノードを挿入する
*/
void Outliner::insertNode(const NodePtr& node, const NodePtr& parent, size_t index) {
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
}
