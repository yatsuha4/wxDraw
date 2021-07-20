#pragma once

namespace wxdraw::property {
/**
   メンバー基底クラス
*/
class MemberBase {
 private:
  wxString name_;
  wxString label_;

 public:
  MemberBase(const wxString& name);
  virtual ~MemberBase() = default;

  WXDRAW_GETTER(Name, name_);
  WXDRAW_ACCESSOR(Label, label_);

  wxString getUniqueName() const;
};
}
