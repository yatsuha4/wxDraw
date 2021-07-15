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
    NONE, 
    EDIT, 
    EDIT_NEW_NODE, 
    EDIT_NEW_COMPONENT, 
    POPUP_INSPECTOR_COMPONENT
  };

  enum {
    ID_TOP = wxID_HIGHEST, 
    ID_FILE_NEW, 
    ID_FILE_OPEN, 
    ID_FILE_SAVE, 
    ID_FILE_SAVE_AS, 
    ID_FILE_EXPORT, 
    ID_FILE_QUIT, 
    ID_EDIT_APPEND, 
    ID_EDIT_APPEND_LAYER, 
    ID_EDIT_APPEND_RECTANGLE, 
    ID_EDIT_APPEND_ELLIPSE, 
    ID_EDIT_NEW_COMPONENT, 
    ID_EDIT_NEW_COMPONENT_PEN, 
    ID_EDIT_NEW_COMPONENT_BRUSH, 
    ID_EDIT_NEW_COMPONENT_EXPORT, 
    ID_EDIT_REMOVE, 
    ID_EDIT_CLONE, 
    ID_EDIT_UNDO, 
    ID_EDIT_REDO, 
    ID_WINDOW_PERSPECTIVE, 
    ID_WINDOW_PERSPECTIVE_SAVE, 
    ID_WINDOW_PERSPECTIVE_LOAD, 
    ID_WINDOW_PERSPECTIVE_RESET, 
    ID_COMPONENT_REMOVE, 
    ID_COMPONENT_UP, 
    ID_COMPONENT_DOWN
  };

 private:
  Type type_;

 public:
  Menu(Type type = Type::NONE);
  ~Menu() override = default;

  WXDRAW_GETTER(Type, type_);
};
}
