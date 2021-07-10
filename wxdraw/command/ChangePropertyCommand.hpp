#pragma once

#include "wxdraw/command/Command.hpp"

namespace wxdraw::command {
/**
   プロパティ変更コマンド
*/
template<class T>
class ChangePropertyCommand
  : public Command
{
  using super = Command;

 private:
  const NodePtr& node_;
  T& property_;
  T srcValue_;
  T dstValue_;

 public:
  ChangePropertyCommand(MainFrame* mainFrame, 
                        const NodePtr& node, 
                        T& property, 
                        const T& value)
    : super("ChangeProperty", mainFrame), 
      node_(node), 
      property_(property), 
      srcValue_(property), 
      dstValue_(value)
  {}
  ~ChangePropertyCommand() override = default;

 protected:
  bool Do() override {
    property_ = dstValue_;
    getMainFrame()->updateNode(node_);
    return true;
  }

  bool Undo() override {
    property_ = srcValue_;
    getMainFrame()->updateNode(node_);
    return true;
  }
};
}
