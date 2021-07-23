#pragma once

#include "wxdraw/property/Member.hpp"

namespace wxdraw::command {
/**
   プロパティ変更コマンド
*/
template<class T>
class EditCommand
  : public wxCommand
{
  using super = wxCommand;

 private:
  std::shared_ptr<Member<T>> member_;
  T srcValue_;
  T dstValue_;

 public:
  EditCommand(const std::shared_ptr<Member<T>>& member, const T& value)
    : super(true, wxString::Format(_("(Edit %s)"), member->getLabel())), 
      member_(member), 
      srcValue_(member->getValue()), 
      dstValue_(value)
  {}
  ~EditCommand() override = default;

 protected:
  bool Do() override {
    member_->getValue() = dstValue_;
    return true;
  }

  bool Undo() override {
    member_->getValue() = srcValue_;
    return true;
  }
};
}
