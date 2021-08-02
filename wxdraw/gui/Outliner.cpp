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
  Bind(wxEVT_DATAVIEW_SELECTION_CHANGED, &Outliner::onSelectionChanged, this);
}
/**
 */
void Outliner::selectNode(const NodePtr& node) {
  ExpandAncestors(node->getItem());
  Select(node->getItem());
  onSelectNode(node);
}
/**
   ノードを新規作成できる？
   @return 新規作成できるとき真
*/
bool Outliner::canCreateNode() const {
  auto [parent, index] = getInsertParent();
  return parent != nullptr;
}
/**
 */
void Outliner::createProject() {
  appendProject(Node::Project::Create(nullptr));
}
/**
 */
void Outliner::appendProject(const NodePtr& node) {
  submitInsertCommand<InsertNodeCommand>(node, nullptr, 0);
}
/**
 */
void Outliner::doInsert(const NodePtr& node, const std::tuple<NodePtr, size_t>& args) {
  auto parent = std::get<0>(args);
  auto index = std::get<1>(args);
  if(parent) {
    parent->getContainer()->getChildren().insert(index, node);
  }
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
   新規作成するノードの親と挿入位置を求める
   @return { 親ノード, 挿入位置 }
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
  //wxASSERT(parent->getItem().IsOk());
  //wxASSERT(index <= parent->getChildren().size());
  auto parentItem = parent ? parent->getItem() : wxDataViewItem();
  wxDataViewItem item;
  if(index == 0) {
    item = node->getContainer()
      ? PrependContainer(parentItem, node->getName())
      : PrependItem(parentItem, node->getName());
  }
  else if(index < GetChildCount(parentItem)) {
    auto prev = GetNthChild(parentItem, static_cast<unsigned int>(index));
    item = node->getContainer()
      ? InsertContainer(parentItem, prev, node->getName())
      : InsertItem(parentItem, prev, node->getName());
  }
  else {
    item = node->getContainer()
      ? AppendContainer(parentItem, node->getName())
      : AppendItem(parentItem, node->getName());
  }
  if(node->getContainer()) {
    SetItemIcon(item, wxArtProvider::GetIcon(wxART_FOLDER));
    SetItemExpandedIcon(item, wxArtProvider::GetIcon(wxART_FOLDER_OPEN));
  }
  else {
    SetItemIcon(item, wxArtProvider::GetIcon(wxART_NORMAL_FILE));
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
  node->setItem(wxDataViewItem());
}
/**
 */
void Outliner::onSelectionChanged(wxDataViewEvent& event) {
  onSelectNode(getNode(event.GetItem()));
}
/**
 */
void Outliner::onSelectNode(const NodePtr& node) {
  if(node != selectNode_) {
    selectNode_ = node;
    mainFrame_->onSelectNode(node);
  }
}
/**
 */
NodePtr Outliner::getNode(const wxDataViewItem& item) const {
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
