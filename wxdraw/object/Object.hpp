#pragma once

namespace wxdraw::object {
/**
   オブジェクト基底クラス
*/
class Object
  : public std::enable_shared_from_this<Object>
{
 private:
  wxString type_;
  wxString id_;
  wxString name_;

  static std::map<wxString, int> Serials;

 public:
  Object(const wxString& type);
  Object(const Object& src);
  virtual ~Object() = default;

  WXDRAW_GETTER(Type, type_);
  WXDRAW_ACCESSOR(Id, id_);
  WXDRAW_ACCESSOR(Name, name_);

  virtual PropertyPtr createProperty();
  virtual void onUpdateProperty();

  template<class T, class... Args>
  static std::shared_ptr<T> New(Args&&... args) {
    auto object = std::make_shared<T>(args...);
    object->onNew();
    return object;
  }

  static wxString NewId();

  virtual void onNew();
};
}
