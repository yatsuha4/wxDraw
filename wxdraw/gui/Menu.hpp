#pragma once

namespace wxdraw::gui {
/**
   メニュー
*/
class Menu
  : public wxMenu
{
  using super = wxMenu;

 public:
  enum Type {
    None, 
    Edit, 
    Edit_NewNode, 
    Edit_NewComponent
  };

 private:
  Type type_;

 public:
  Menu(Type type = Type::None);
  ~Menu() override = default;

  WXDRAW_GETTER(Type, type_);
};
}
