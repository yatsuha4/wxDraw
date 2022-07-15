#pragma once

#include "wxdraw/command/InsertCommand.hpp"
#include "wxdraw/command/MoveCommand.hpp"

namespace wxdraw::gui {
/**
   アウトライナ
*/
class Outliner
  : public wxDataViewCtrl, 
    public InsertNodeCommand::Observer, 
    public MoveNodeCommand::Observer
{
  using super = wxDataViewCtrl;

 public:
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
  NodePtr viewNode_;
  NodePtr dragNode_;

 public:
  Outliner(wxWindow* parent, MainFrame* mainFrame);
  ~Outliner() override = default;

  WXDRAW_GETTER(MainFrame, mainFrame_);

  void update();

  void selectNode(const NodePtr& node);
  WXDRAW_GETTER(SelectNode, selectNode_);
  WXDRAW_GETTER(ViewNode, viewNode_);

  bool canCreateNode() const;

  template<class T>
  bool createNode() {
    auto [parent, index] = getInsertParent();
    if(parent) {
      return insert(T::Create(parent), parent, index);
    }
    return false;
  }

  void createProject();
  void appendProject(const NodePtr& node);

  bool canCloneNode() const;
  void cloneNode();

  bool canRemoveNode() const;
  void removeNode();

  bool insert(const NodePtr& node, const NodePtr& parent, size_t index);
  bool remove(const NodePtr& node);

  void doInsert(const NodePtr& node, const std::tuple<NodePtr, size_t>& args) override;
  std::tuple<NodePtr, size_t> doRemove(const NodePtr& node) override;
  std::tuple<NodePtr, size_t>
  doMove(const NodePtr& node, const std::tuple<NodePtr, size_t>& args) override;

  static wxDataViewItem GetItem(const NodePtr& node);

 private:
  std::tuple<NodePtr, size_t> getInsertParent() const;

  void insertNode(const NodePtr& node, const NodePtr& parent, size_t index);
  std::tuple<NodePtr, size_t> removeNode(const NodePtr& node);

  void onSelectionChanged(wxDataViewEvent& event);
  void onSelectNode(const NodePtr& node);
  void onBeginDrag(wxDataViewEvent& event);
  void onDropPossible(wxDataViewEvent& event);
  void onDrop(wxDataViewEvent& event);
  void onValueChanged(wxDataViewEvent& event);

  NodePtr getNode(const wxDataViewItem& item) const;

  template<class T, class... Args>
  bool submitCommand(const NodePtr& node, const Args&... args) {
    return mainFrame_->submitCommand<T>(this, node, args...);
  }
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
  void remove(const NodePtr& node);
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

  bool GetAttr(const wxDataViewItem& item, 
               unsigned int column, 
               wxDataViewItemAttr& attr) const override;

  wxDataViewItem GetParent(const wxDataViewItem& item) const override;
  bool IsContainer(const wxDataViewItem& item) const override;
  unsigned int GetChildren(const wxDataViewItem& item, 
                           wxDataViewItemArray& children) const override;

  bool HasContainerColumns(const wxDataViewItem& item) const override {
    return true;
  }
};
}
