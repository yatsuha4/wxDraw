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
  T& var_;
  T srcValue_;
  T dstValue_;

 public:
  EditCommand(const std::shared_ptr<Member<T>>& member, const T& value)
    : EditCommand(member->getLabel(), member->getValue(), value)
  {}
  EditCommand(const wxString& label, T& var, const T& value)
    : super(true, wxString::Format(_("(Edit %s)"), label)), 
      var_(var), 
      srcValue_(var), 
      dstValue_(value)
  {}
  ~EditCommand() override = default;

 protected:
  bool Do() override {
    var_ = dstValue_;
    return true;
  }

  bool Undo() override {
    var_ = srcValue_;
    return true;
  }
};
}
