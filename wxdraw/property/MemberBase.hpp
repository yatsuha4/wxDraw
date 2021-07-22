#pragma once

namespace wxdraw::property {
/**
   メンバー基底クラス
*/
class MemberBase {
 private:
  wxString name_;
  wxString label_;
  bool show_;

 public:
  MemberBase(const wxString& name);
  virtual ~MemberBase() = default;

  WXDRAW_GETTER(Name, name_);
  WXDRAW_ACCESSOR(Label, label_);
  WXDRAW_IS_ACCESSOR(Show, show_);

  wxString getUniqueName() const;
};
}
