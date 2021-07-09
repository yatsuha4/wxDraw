#include "wxdraw/property/MemberBase.hpp"

namespace wxdraw::property {
/**
   コンストラクタ
*/
MemberBase::MemberBase(const std::string& name)
  : name_(name), 
    label_(name)
{
}
std::string MemberBase::getUniqueName() const {
  std::stringstream stream;
  stream << name_ << "." << this;
  return stream.str();
}
}
