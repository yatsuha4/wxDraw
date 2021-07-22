#include "wxdraw/property/MemberBase.hpp"

namespace wxdraw::property {
/**
   コンストラクタ
*/
MemberBase::MemberBase(const wxString& name)
  : name_(name), 
    label_(name), 
    show_(true)
{
}
/**
 */
wxString MemberBase::getUniqueName() const {
  return wxString::Format("%s.%p", name_, this);
}
}
