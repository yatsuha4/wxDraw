#include "wxdraw/gui/Outliner.hpp"
#include "wxdraw/node/RootNode.hpp"

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
}
/**
 */
const RootNodePtr& Outliner::getRootNode() {
  if(!rootNode_) {
    rootNode_ = std::make_shared<RootNode>();
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
    for(size_t i = 0; i < index; i++) {
      prev = GetNextSibling(prev);
    }
    item = InsertItem(parent->getItem(), prev, node->getName());
  }
  SetItemData(item, new ClientData(node));
  node->setItem(item);
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
Outliner::ClientData::ClientData(const NodePtr& node)
  : node_(node)
{
}
}
