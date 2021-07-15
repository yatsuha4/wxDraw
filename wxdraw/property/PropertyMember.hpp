#pragma once

#include "wxdraw/property/MemberBase.hpp"

namespace wxdraw::property {
/**
   入れ子のメンバー
*/
class PropertyMember
  : public MemberBase
{
  using super = MemberBase;

 private:
  PropertyPtr property_;

 public:
  PropertyMember(const PropertyPtr& property);
  ~PropertyMember() override = default;

  WXDRAW_GETTER(Property, property_);
};
}
