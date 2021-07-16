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
  T& property_;
  T srcValue_;
  T dstValue_;

 public:
  ChangePropertyCommand(MainFrame* mainFrame, 
                        T& property, 
                        const T& value)
    : super("ChangeProperty", mainFrame), 
      property_(property), 
      srcValue_(property), 
      dstValue_(value)
  {}
  ~ChangePropertyCommand() override = default;

 protected:
  bool Do() override {
    property_ = dstValue_;
    return true;
  }

  bool Undo() override {
    property_ = srcValue_;
    return true;
  }
};
}
