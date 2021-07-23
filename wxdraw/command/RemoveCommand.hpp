#pragma once

#include "wxdraw/command/InsertCommand.hpp"

namespace wxdraw::command {
/**
 */
template<class T, class... Args>
class RemoveCommand
  : public InsertCommand<T, Args...>
{
  using super = InsertCommand<T, Args...>;

 public:
  RemoveCommand(typename super::Observer* observer, 
                const std::shared_ptr<T>& object, 
                const Args&... args)
    : super(wxString::Format("Remove %s", object->getType()), 
            observer, object, args...)
  {}
  ~RemoveCommand() override = default;

 protected:
  bool Do() override {
    return super::Undo();
  }

  bool Undo() override {
    return super::Do();
  }
};
}
