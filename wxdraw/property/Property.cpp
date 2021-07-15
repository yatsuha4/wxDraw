#include "wxdraw/property/Property.hpp"

namespace wxdraw::property {
/**
   コンストラクタ
   @param name 名前
*/
Property::Property(const std::string& name)
  : name_(name)
{
}
/**
   コピーコンストラクタ
   @param src コピー元
*/
Property::Property(const Property& src)
  : name_(src.name_)
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
