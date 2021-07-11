#pragma once

namespace wxdraw::property {
/**
   メンバー基底クラス
*/
class MemberBase {
 private:
  std::string name_;
  std::string label_;

 public:
  MemberBase(const std::string& name);
  virtual ~MemberBase() = default;

  WXDRAW_GETTER(Name, name_);
  WXDRAW_ACCESSOR(Label, label_);

  std::string getUniqueName() const;

  virtual wxString toString() const = 0;
  virtual void fromString(const wxString& value) = 0;

  template<class T>
  static wxString ToString(const T& value) {
    return wxVariant(value).GetString();
  }

  template<class T>
  static T FromString(const wxString& value) {
    return wxAny(wxVariant(value)).As<T>();
  }

  static wxString ToString(const wxColour& value) {
    return value.GetAsString();
  }

  static wxColour FromString(const wxString& value) {
    return wxColour(value);
  }
};
}
