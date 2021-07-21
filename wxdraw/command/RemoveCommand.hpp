#pragma once

#include "wxdraw/command/InsertCommand.hpp"

namespace wxdraw::command {
/**
 */
template<class T>
class RemoveCommand
  : public InsertCommand<T>
{
  using super = InsertCommand<T>;

 public:
  RemoveCommand(const std::shared_ptr<typename super::Observer>& observer, 
                const std::shared_ptr<T>& object, 
                size_t index)
    : super(wxString::Format("Remove %s", object->getType()), 
            observer, object, index)
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
