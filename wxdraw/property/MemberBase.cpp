#include "wxdraw/property/MemberBase.hpp"

namespace wxdraw::property {
/**
   コンストラクタ
*/
MemberBase::MemberBase(const std::string& id)
  : id_(id), 
    name_(id)
{
}
}
