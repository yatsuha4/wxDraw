#include <uuid/uuid.h>
#include "wxdraw/object/Object.hpp"
#include "wxdraw/property/Property.hpp"

namespace wxdraw::object {
std::map<std::type_index, std::map<wxString, int>> Object::Serials;
/**
   コンストラクタ
   @param type 型名
 */
Object::Object(const wxString& type)
  : type_(type)
{
}
/**
   コピーコンストラクタ
   @param src コピー元
*/
Object::Object(const Object& src)
  : type_(src.type_)
{
  onNew(typeid(src));
}
/**
 */
PropertyPtr Object::createProperty() {
  auto property = std::make_shared<Property>(shared_from_this());
  property->appendMember("Id", id_);
  return property;
}
/**
 */
void Object::onUpdateProperty() {
  wxRegEx match("^([A-Za-z]+)_(\\d+)");
  if(match.Matches(name_)) {
    std::type_index type(typeid(*this));
    auto name = match.GetMatch(name_, 1);
    auto index = wxAtoi(match.GetMatch(name_, 2));
    if(index > Serials[type][name]) {
      Serials[type][name] = index;
    }
  }
}
/**
   新規IDを生成する
   @return 新規ID
*/
wxString Object::NewId() {
  uuid_t id;
  uuid_generate(id);
  uuid_string_t strId;
  uuid_unparse_upper(id, strId);
  return wxString(strId);
}
/**
   新規に生成されたときの処理
*/
void Object::onNew() {
  onNew(typeid(*this));
}
/**
   新規に生成されたときの処理
*/
void Object::onNew(const std::type_index& type) {
  id_ = NewId();
  if(name_.IsEmpty()) {
    name_ = wxString::Format("%s_%d", type_, ++Serials[type][type_]);
  }
}
}
