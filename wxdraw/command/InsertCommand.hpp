#pragma once

#include "wxdraw/command/Command.hpp"

namespace wxdraw::command {
/**
   リスト操作コマンド
*/
template<class T>
class InsertCommand
  : public wxCommand
{
  using super = wxCommand;

 public:
  class Observer {
   public:
    virtual void doInsert(const std::shared_ptr<T>& object, size_t index) = 0;
    virtual void doRemove(const std::shared_ptr<T>& object, size_t index) = 0;
  };

 private:
  std::shared_ptr<Observer> observer_;
  std::shared_ptr<T> object_;
  size_t index_;

 public:
  InsertCommand(const std::shared_ptr<Observer>& observer, 
                const std::shared_ptr<T>& object, 
                size_t index)
    : super(true, wxString::Format("Insert %s", object->getType())), 
      observer_(observer), 
      object_(object), 
      index_(index)
  {}
  ~InsertCommand() override = default;

 protected:
  bool Do() override {
    observer_->doInsert(object_, index_);
    return true;
  }

  bool Undo() override {
    observer_->doRemove(object_, index_);
    return true;
  }
};
}
