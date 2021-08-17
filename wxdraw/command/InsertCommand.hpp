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
  using args_t = std::tuple<Args...>;

 public:
  class Observer {
   public:
    Observer() = default;
    virtual ~Observer() = default;

    virtual void insert(const std::shared_ptr<T>& object, const args_t& args) = 0;
    virtual args_t remove(const std::shared_ptr<T>& object) = 0;
  };

 private:
  Observer* observer_;
  std::shared_ptr<T> object_;
  args_t args_;

 public:
  InsertCommand(Observer* observer, 
                const std::shared_ptr<T>& object, 
                const Args&... args)
    : InsertCommand(wxString::Format(_("(Insert %s)"), object->getName()), observer, object)
  {
    args_ = std::make_tuple(args...);
  }
  ~InsertCommand() override = default;

 protected:
  InsertCommand(const wxString& label, 
                Observer* observer, 
                const std::shared_ptr<T>& object)
    : super(true, label), 
      observer_(observer), 
      object_(object)
  {}

  bool Do() override {
    observer_->insert(object_, args_);
    return true;
  }

  bool Undo() override {
    args_ = observer_->remove(object_);
    return true;
  }
};
using InsertNodeCommand = InsertCommand<Node, NodePtr, size_t>;
using InsertComponentCommand = InsertCommand<ComponentBase, NodePtr>;
}
