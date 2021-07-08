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

 private:
  T& value_;

 public:
  Member(const std::string& id, T& value)
    : super(id), 
      value_(value)
  {}
  ~Member() override = default;

  WXDRAW_GETTER(Value, value_);

  static std::shared_ptr<Member<T>> As(const MemberBasePtr& member) {
    return std::dynamic_pointer_cast<Member<T>>(member);
  }
};
}
