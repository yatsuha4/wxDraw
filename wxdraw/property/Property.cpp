#include "wxdraw/object/Object.hpp"
#include "wxdraw/property/Property.hpp"

namespace wxdraw::property {
/**
   コンストラクタ
*/
Property::Property(const ObjectPtr& object)
  : object_(object)
{
}
/**
 */
const wxString& Property::getName() const {
  return object_->getName();
}
/**
   メンバーを追加する
   @param member 追加するメンバー
*/
void Property::appendMember(const MemberBasePtr& member) {
  members_.push_back(member);
}
/**
 */
void Property::appendMember(const std::string& name, glm::ivec2& value) {
  appendMember(name + ".x", value.x);
  appendMember(name + ".y", value.y);
}
/**
 */
void Property::appendMember(const std::string& name, glm::dvec2& value) {
  appendMember(name + ".x", value.x);
  appendMember(name + ".y", value.y);
}
}
