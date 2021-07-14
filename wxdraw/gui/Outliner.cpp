#include "wxdraw/gui/MainFrame.hpp"
#include "wxdraw/gui/Outliner.hpp"
#include "wxdraw/node/Node.hpp"

namespace wxdraw::gui {
/**
   コンストラクタ
   @param parent 親
   @param mainFrame メインフレーム
*/
Outliner::Outliner(wxWindow* parent, MainFrame& mainFrame)
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
    rootNode_ = std::make_shared<Node>();
    rootNode_->setItem(GetRootItem());
  }
  return rootNode_;
}
/**
 */
void Outliner::insertNode(const NodePtr& node, const NodePtr& parent, size_t index) {
  wxASSERT(!node->getItem().IsOk());
  wxASSERT(parent->getItem().IsOk());
  wxASSERT(index <= parent->getChildren().size());
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
  for(size_t i = 0; i < node->getChildren().size(); i++) {
    insertNode(node->getChildren().at(i), node, i);
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
void Outliner::selectNode(const NodePtr& node) {
  for(auto item = GetItemParent(node->getItem()); item.IsOk(); item = GetItemParent(item)) {
    Expand(item);
  }
  Select(node->getItem());
}
/**
 */
void Outliner::onSelectionChanged(wxTreeListEvent& event) {
  mainFrame_.selectNode(getNode(event.GetItem()));
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
