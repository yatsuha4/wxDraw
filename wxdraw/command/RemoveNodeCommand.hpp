#pragma once

#include "wxdraw/command/Command.hpp"

namespace wxdraw::command {
/**
 */
class RemoveNodeCommand
  : public Command
{
  using super = Command;

 private:
  NodePtr node_;
  NodePtr parent_;
  size_t index_;

 public:
  RemoveNodeCommand(MainFrame* mainFrame, const NodePtr& node);
  ~RemoveNodeCommand() override = default;

 protected:
  bool Do() override;
  bool Undo() override;
};
}
