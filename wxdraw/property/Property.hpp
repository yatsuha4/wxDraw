#pragma once

#include "wxdraw/property/Member.hpp"

namespace wxdraw::property {
/**
   プロパティ
*/
class Property
  : public MemberBase
{
  using super = MemberBase;

 private:
  std::vector<MemberBasePtr> members_;

 public:
  Property(const std::string& id);
  ~Property() override = default;

  WXDRAW_GETTER(Members, members_);

  template <class T>
  Member<T>& appendMember(const std::string& id, T& value) {
    auto member = std::make_shared<Member<T>>(id, value);
    members_.push_back(member);
    return *member;
  }
};
}
