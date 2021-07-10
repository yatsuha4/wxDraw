#pragma once

#include "wxdraw/property/Member.hpp"

namespace wxdraw::property {
/**
   プロパティ
*/
class Property {
 private:
  std::string name_;
  std::vector<MemberBasePtr> members_;

 public:
  Property(const std::string& name);
  virtual ~Property() = default;

  WXDRAW_GETTER(Name, name_);
  WXDRAW_GETTER(Members, members_);

  void appendMember(const std::string& name, glm::dvec2& value);

  template <class T>
  Member<T>& appendMember(const std::string& name, T& value) {
    auto member = std::make_shared<Member<T>>(name, value);
    members_.push_back(member);
    return *member;
  }
};
}
