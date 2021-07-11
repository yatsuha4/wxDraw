#pragma once

#include "wxdraw/command/Command.hpp"

namespace wxdraw::command {
/**
   ノードを挿入する
*/
class InsertNodeCommand
  : public Command
{
  using super = Command;

 private:
  NodePtr node_;
  NodePtr parent_;
  size_t index_;

 public:
  InsertNodeCommand(MainFrame* mainFrame, 
                    const NodePtr& node, 
                    const NodePtr& parent, 
                    size_t index);
  ~InsertNodeCommand() override = default;

 protected:
  bool Do() override;
  bool Undo() override;
};
}
