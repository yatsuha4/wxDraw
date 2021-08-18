#pragma once

namespace wxdraw::command {
/**
   移動コマンド
*/
template<class T, class... Args>
class MoveCommand
  : public wxCommand
{
  using super = wxCommand;
  using args_t = std::tuple<Args...>;

 public:
  class Observer {
   public:
    Observer() = default;
    virtual ~Observer() = default;

    virtual args_t doMove(const std::shared_ptr<T>& object, const args_t& args) = 0;
  };

 private:
  Observer* observer_;
  std::shared_ptr<T> object_;
  args_t dstArgs_;
  args_t srcArgs_;

 public:
  MoveCommand(Observer* observer, 
              const std::shared_ptr<T>& object, 
              const Args&... args)
    : super(true, wxString::Format(_("(Move %s)"), object->getName())), 
      observer_(observer), 
      object_(object), 
      dstArgs_(args...)
  {}
  ~MoveCommand() override = default;

 protected:
  bool Do() override {
    srcArgs_ = observer_->doMove(object_, dstArgs_);
    return true;
  }

  bool Undo() override {
    dstArgs_ = observer_->doMove(object_, srcArgs_);
    return true;
  }
};
using MoveNodeCommand = MoveCommand<Node, NodePtr, size_t>;
}
