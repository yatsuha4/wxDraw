#include <uuid/uuid.h>
#include "wxdraw/object/Object.hpp"
#include "wxdraw/property/Property.hpp"

namespace wxdraw::object {
const char* Object::TYPE = "Object";
const std::regex Object::NAME_REGEX("^([A-Za-z]+)_(\\d+)");
std::map<std::string, int> Object::Serials;
/**
   コンストラクタ
   @param type 型名
 */
Object::Object(const char* type)
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
  onNew();
}
/**
 */
PropertyPtr Object::createProperty() {
  //auto property = std::make_shared<Property>(shared_from_this());
  auto property = std::make_shared<Property>(type_);
  return property;
}
/**
 */
void Object::onUpdateProperty() {
  std::cmatch match;
  if(std::regex_match(static_cast<const char*>(name_), match, NAME_REGEX)) {
    auto name = match[1].str();
    auto index = std::stoi(match[2].str());
    if(index > Serials[name]) {
      Serials[name] = index;
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
  setId(NewId());
  setName(wxString::Format("%s_%d", type_, ++Serials[type_]));
}
}
