#include "wxdraw/property/Property.hpp"

namespace wxdraw::property {
/**
   コンストラクタ
   @param name 名前
*/
Property::Property(const std::string& name, const PropertyOwnerPtr& owner)
  : name_(name), 
    owner_(owner)
{
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
