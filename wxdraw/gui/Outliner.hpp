#pragma once

#include "wxdraw/command/InsertCommand.hpp"

namespace wxdraw::gui {
/**
   アウトライナ
*/
class Outliner
  : public wxDataViewCtrl, 
    public InsertNodeCommand::Observer
{
  using super = wxDataViewCtrl;

 public:
  class ClientData;
  class Model;

  enum Column {
    SHOW, 
    NAME, 
    MAX
  };

 private:
  MainFrame* mainFrame_;
  wxObjectDataPtr<Model> model_;
  NodePtr selectNode_;
  NodePtr dragNode_;

 public:
  Outliner(wxWindow* parent, MainFrame* mainFrame);
  ~Outliner() override = default;

  WXDRAW_GETTER(MainFrame, mainFrame_);

  void update();

  void selectNode(const NodePtr& node);
  WXDRAW_GETTER(SelectNode, selectNode_);

  bool canCreateNode() const;

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
  std::tuple<NodePtr, size_t> getInsertParent() const;

  void insertNode(const NodePtr& node, const NodePtr& parent, size_t index);
  void removeNode(const NodePtr& node);

  void updateItem(const wxDataViewItem& item);

  void onSelectionChanged(wxDataViewEvent& event);
  void onSelectNode(const NodePtr& node);
  void onBeginDrag(wxDataViewEvent& event);
  void onDropPossible(wxDataViewEvent& event);
  void onDrop(wxDataViewEvent& event);
  void onValueChanged(wxDataViewEvent& event);

  NodePtr getNode(const wxDataViewItem& item) const;

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
/**
 */
class Outliner::Model
  : public wxDataViewModel
{
  using super = wxDataViewModel;

 private:
  Outliner* outliner_;
  NodePtr root_;

 public:
  Model(Outliner* outliner);
  ~Model() override = default;

  void insert(const NodePtr& node, const NodePtr& parent, size_t index);
  void updateItem(const wxDataViewItem& item);
  NodePtr getNode(const wxDataViewItem& item) const;

 protected:
  unsigned int GetColumnCount() const override;
  wxString GetColumnType(unsigned int column) const override;

  bool SetValue(const wxVariant& value, 
                const wxDataViewItem& item, 
                unsigned int column) override;

  void GetValue(wxVariant& value, 
                const wxDataViewItem& item, 
                unsigned int column) const override;

  wxDataViewItem GetParent(const wxDataViewItem& item) const override;
  bool IsContainer(const wxDataViewItem& item) const override;
  unsigned int GetChildren(const wxDataViewItem& item, 
                           wxDataViewItemArray& children) const override;

  bool HasContainerColumns(const wxDataViewItem& item) const override {
    return true;
  }

 private:
  static wxDataViewItem GetItem(const NodePtr& node);
};
}
