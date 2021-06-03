#pragma once

#include "wxdraw/property/MemberBase.hpp"

namespace wxdraw::property {
/**
   プロパティ
*/
class Property
  : public MemberBase
{
 private:
  std::vector<MemberBasePtr> members_;

 public:
  Property(const std::string& id);
  ~Property() override = default;

  WXDRAW_GETTER(Members, members_);
};
}
