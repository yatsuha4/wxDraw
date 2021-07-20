#pragma once

#include "wxdraw/property/MemberBase.hpp"

namespace wxdraw::property {
/**
   メンバー
*/
template<class T>
class Member
  : public MemberBase
{
  using super = MemberBase;

 public:
  using Ptr = std::shared_ptr<Member<T>>;

 private:
  T& value_;

 public:
  Member(const wxString& name, T& value)
    : super(name), 
      value_(value)
  {}
  ~Member() override = default;

  WXDRAW_GETTER(Value, value_);

  static Ptr As(const MemberBasePtr& member) {
    return std::dynamic_pointer_cast<Member<T>>(member);
  }
};
}
