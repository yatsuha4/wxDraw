#pragma once

#include "wxdraw/command/Command.hpp"

namespace wxdraw::command {
/**
   コンポーネントを挿入する
*/
class InsertComponentCommand
  : public Command
{
  using super = Command;

 private:
  ComponentBasePtr component_;
  NodePtr node_;

 public:
  InsertComponentCommand(MainFrame* mainFrame, 
                         const ComponentBasePtr& component, 
                         const NodePtr& node);
  ~InsertComponentCommand() override = default;

 protected:
  bool Do() override;
  bool Undo() override;
};
}
