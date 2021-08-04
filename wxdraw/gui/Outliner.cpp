#include "wxdraw/command/EditCommand.hpp"
#include "wxdraw/component/ContainerComponent.hpp"
#include "wxdraw/component/ProxyComponent.hpp"
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
  : super(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxDV_ROW_LINES), 
    mainFrame_(mainFrame), 
    model_(new Model(this))
{
  AssociateModel(model_.get());
  AppendToggleColumn("Show", Column::SHOW, wxDATAVIEW_CELL_EDITABLE, 40, wxALIGN_CENTER, 0);
  auto column = AppendIconTextColumn("Name", Column::NAME, wxDATAVIEW_CELL_EDITABLE, -1, 
                                     wxALIGN_LEFT, wxDATAVIEW_COL_RESIZABLE);
  SetExpanderColumn(column);
  Bind(wxEVT_DATAVIEW_SELECTION_CHANGED, &Outliner::onSelectionChanged, this);
  Bind(wxEVT_DATAVIEW_ITEM_BEGIN_DRAG, &Outliner::onBeginDrag, this);
  Bind(wxEVT_DATAVIEW_ITEM_DROP_POSSIBLE, &Outliner::onDropPossible, this);
  Bind(wxEVT_DATAVIEW_ITEM_DROP, &Outliner::onDrop, this);
  Bind(wxEVT_DATAVIEW_ITEM_VALUE_CHANGED, &Outliner::onValueChanged, this);
}
/**
 */
void Outliner::update() {
  Refresh();
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
  model_->insert(node, parent, index);
  /*
  auto parentItem = parent ? parent->getItem() : wxDataViewItem();
  wxDataViewItem item;
  if(index == 0) {
    item = node->getContainer()
      ? model_->PrependContainer(parentItem, node->getName())
      : model_->PrependItem(parentItem, node->getName());
  }
  else if(index < model_->GetChildCount(parentItem)) {
    auto prev = model_->GetNthChild(parentItem, static_cast<unsigned int>(index));
    item = node->getContainer()
      ? model_->InsertContainer(parentItem, prev, node->getName())
      : model_->InsertItem(parentItem, prev, node->getName());
  }
  else {
    item = node->getContainer()
      ? model_->AppendContainer(parentItem, node->getName())
      : model_->AppendItem(parentItem, node->getName());
  }
  model_->SetItemData(item, new ClientData(node));
  model_->ItemAdded(parentItem, item);
  node->setItem(item);
  model_->updateItem(item);
  if(auto container = node->getContainer()) {
    for(size_t i = 0; i < container->getChildren().size(); i++) {
      insertNode(container->getChildren().at(i), node, i);
    }
  }
  */
}
/**
 */
void Outliner::removeNode(const NodePtr& node) {
  wxASSERT(node->getItem().IsOk());
  //model_->DeleteItem(node->getItem());
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
void Outliner::onBeginDrag(wxDataViewEvent& event) {
  dragNode_ = getNode(event.GetItem());
  if(dragNode_) {
    event.SetDataObject(dragNode_->toDataObject());
    event.SetDragFlags(wxDrag_AllowMove);
  }
  else {
    event.Veto();
  }
}
/**
 */
void Outliner::onDropPossible(wxDataViewEvent& event) {
  if(auto node = getNode(event.GetItem())) {
    if(node->getComponent<ProxyComponent>()) {
      event.SetDropEffect(wxDragLink);
      return;
    }
  }
  event.Veto();
}
/**
 */
void Outliner::onDrop(wxDataViewEvent& event) {
  if(dragNode_) {
    if(auto node = getNode(event.GetItem())) {
      if(auto proxy = node->getComponent<ProxyComponent>()) {
        mainFrame_->submitCommand
          <EditCommand<NodePtr>>("Node", proxy->getNode(), dragNode_);
      }
    }
    dragNode_ = nullptr;
  }
}
/**
 */
void Outliner::onValueChanged(wxDataViewEvent& event) {
}
/**
 */
NodePtr Outliner::getNode(const wxDataViewItem& item) const {
  return model_->getNode(item);
}
/**
 */
Outliner::ClientData::ClientData(const NodePtr& node)
  : node_(node)
{
}
/**
   コンストラクタ
   @param outliner アウトライナ
*/
Outliner::Model::Model(Outliner* outliner)
  : outliner_(outliner)
{}
/**
 */
void Outliner::Model::insert(const NodePtr& node, const NodePtr& parent, size_t index) {
  if(parent) {
    ItemAdded(GetItem(parent), GetItem(node));
  }
  else {
    Cleared();
    root_ = node;
    ItemAdded(wxDataViewItem(), GetItem(node));
  }
}
/**
 */
unsigned int Outliner::Model::GetColumnCount() const {
  return Column::MAX;
}
/**
 */
wxString Outliner::Model::GetColumnType(unsigned int column) const {
  switch(column) {
  case Column::NAME:
    return _("Name");
  case Column::SHOW:
    return _("Show");
  default:
    break;
  }
  return wxEmptyString;
}
/**
 */
bool Outliner::Model::SetValue(const wxVariant& value, 
                               const wxDataViewItem& item, 
                               unsigned int column) {
  if(auto node = getNode(item)) {
    switch(column) {
    case Column::SHOW:
      {
        outliner_->getMainFrame()->submitCommand
          <EditCommand<bool>>(_("Show"), node->getShow(), value.GetBool());
      }
      return true;
    case Column::NAME:
      {
        wxDataViewIconText iconText;
        iconText << value;
        outliner_->getMainFrame()->submitCommand
          <EditCommand<wxString>>(_("Name"), node->getName(), iconText.GetText());
      }
      return true;
    default:
      break;
    }
  }
  return false;
}
/**
 */
void Outliner::Model::GetValue(wxVariant& value, 
                               const wxDataViewItem& item, 
                               unsigned int column) const {
  if(auto node = getNode(item)) {
    switch(column) {
    case Column::NAME:
      {
        wxDataViewIconText iconText(node->getName());
        if(!node->getErrors().empty()) {
          iconText.SetIcon(wxArtProvider::GetIcon(wxART_ERROR));
        }
        else if(node->getContainer()) {
          iconText.SetIcon(wxArtProvider::GetIcon(wxART_FOLDER));
          //SetItemExpandedIcon(wxArtProvider::GetIcon(wxART_FOLDER_OPEN));
        }
        else if(node->getComponent<ProxyComponent>()) {
          iconText.SetIcon(wxArtProvider::GetIcon(wxART_COPY));
        }
        else {
          iconText.SetIcon(wxArtProvider::GetIcon(wxART_NORMAL_FILE));
        }
        value << iconText;
      }
      break;
    case Column::SHOW:
      value = node->isShow();
      break;
    default:
      break;
    }
  }
}
/**
 */
wxDataViewItem Outliner::Model::GetParent(const wxDataViewItem& item) const {
  if(auto node = getNode(item)) {
    return GetItem(node->getParent());
  }
  return wxDataViewItem();
}
/**
 */
bool Outliner::Model::IsContainer(const wxDataViewItem& item) const {
  if(auto node = getNode(item)) {
    return node->getContainer() != nullptr;
  }
  return false;
}
/**
 */
unsigned int Outliner::Model::GetChildren(const wxDataViewItem& item, 
                                          wxDataViewItemArray& children) const {
  if(auto node = getNode(item)) {
    if(auto container = node->getContainer()) {
      for(auto child : container->getChildren()) {
        children.Add(GetItem(child));
      }
      return static_cast<unsigned int>(container->getChildren().size());
    }
  }
  else if(root_) {
    children.Add(GetItem(root_));
    return 1;
  }
  return 0;
}
/**
   項目の表示を更新する
   @param item 項目
*/
void Outliner::Model::updateItem(const wxDataViewItem& item) {
  /*
  if(auto node = getNode(item)) {
    SetItemText(item, node->getName());
    if(node->getContainer()) {
      SetItemIcon(item, wxArtProvider::GetIcon(wxART_FOLDER));
      SetItemExpandedIcon(item, wxArtProvider::GetIcon(wxART_FOLDER_OPEN));
    }
    else if(node->getComponent<ProxyComponent>()) {
      SetItemIcon(item, wxArtProvider::GetIcon(wxART_COPY));
    }
    else {
      SetItemIcon(item, wxArtProvider::GetIcon(wxART_NORMAL_FILE));
    }
    //ValueChanged(item, 0);
  }
  */
}
/**
 */
NodePtr Outliner::Model::getNode(const wxDataViewItem& item) const {
  if(item.IsOk()) {
    return std::static_pointer_cast<Node>(static_cast<Node*>(item.GetID())->shared_from_this());
  }
  return nullptr;
}
/**
 */
wxDataViewItem Outliner::Model::GetItem(const NodePtr& node) {
  return wxDataViewItem(node.get());
}
}
