#pragma once

namespace wxdraw::command {
/**
   リスト操作コマンド
*/
template<class T, class... Args>
class InsertCommand
  : public wxCommand
{
  using super = wxCommand;

 public:
  class Observer {
   public:
    Observer() = default;
    virtual ~Observer() = default;

    virtual void doInsert(const std::shared_ptr<T>& object, 
                          const std::tuple<Args...>& args) = 0;
    virtual void doRemove(const std::shared_ptr<T>& object, 
                          const std::tuple<Args...>& args) = 0;
  };

 private:
  Observer* observer_;
  std::shared_ptr<T> object_;
  std::tuple<Args...> args_;

 public:
  InsertCommand(Observer* observer, 
                const std::shared_ptr<T>& object, 
                const Args&... args)
    : InsertCommand(wxString::Format(_("(Insert %s)"), object->getName()), 
                    observer, object, args...)
  {}
  ~InsertCommand() override = default;

 protected:
  InsertCommand(const wxString& label, 
                Observer* observer, 
                const std::shared_ptr<T>& object, 
                const Args&... args)
    : super(true, label), 
      observer_(observer), 
      object_(object), 
      args_(args...)
  {}

  bool Do() override {
    observer_->doInsert(object_, args_);
    return true;
  }

  bool Undo() override {
    observer_->doRemove(object_, args_);
    return true;
  }
};
using InsertNodeCommand = InsertCommand<Node, NodePtr, size_t>;
using InsertComponentCommand = InsertCommand<ComponentBase, NodePtr>;
}
