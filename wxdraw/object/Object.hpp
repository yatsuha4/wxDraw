#pragma once

namespace wxdraw::object {
/**
   オブジェクト基底クラス
*/
class Object
  : public std::enable_shared_from_this<Object>
{
 public:
  static const char* TYPE;

 private:
  const char* type_;
  wxString id_;
  wxString name_;

  static const std::regex NAME_REGEX;
  static std::map<std::string, int> Serials;

 public:
  Object(const char* type);
  Object(const Object& src);
  virtual ~Object() = default;

  WXDRAW_GETTER(Type, type_);
  WXDRAW_ACCESSOR(Id, id_);
  WXDRAW_ACCESSOR(Name, name_);

  virtual PropertyPtr createProperty();
  virtual void onUpdateProperty();

  template<class T, class... Args>
  static std::shared_ptr<T> New(Args&&... args) {
    auto object = Create<T>(args...);
    object->onNew();
    return object;
  }

  template<class T, class... Args>
  static std::shared_ptr<T> Create(Args&&... args) {
    return std::make_shared<T>(T::TYPE, args...);
  }

  static wxString NewId();

 protected:
  virtual void onNew();
};
}
