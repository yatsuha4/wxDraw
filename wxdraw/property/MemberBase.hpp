#pragma once

namespace wxdraw::property {
/**
   メンバー基底クラス
*/
class MemberBase {
 private:
  std::string id_;
  std::string name_;

 public:
  MemberBase(const std::string& id);
  virtual ~MemberBase() = default;

  WXDRAW_GETTER(Id, id_);
  WXDRAW_ACCESSOR(Name, name_);
};
}
