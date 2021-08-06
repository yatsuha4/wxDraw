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
    NODE, 
    COMPONENT, 
    POPUP_INSPECTOR_COMPONENT
  };

  enum {
    ID_TOP = wxID_HIGHEST, 
    ID_COMPONENT_BRUSH, 
    ID_COMPONENT_COMPOSITION, 
    ID_COMPONENT_DOWN, 
    ID_COMPONENT_EXPORT, 
    ID_COMPONENT_PEN, 
    ID_COMPONENT_REMOVE, 
    ID_COMPONENT_UP, 
    ID_EDIT_CLONE, 
    ID_FILE_EXPORT, 
    ID_FILE_QUIT, 
    ID_NODE_ELLIPSE, 
    ID_NODE_GROUP, 
    ID_NODE_LAYER, 
    ID_NODE_PROXY, 
    ID_NODE_RECTANGLE, 
    ID_NODE_TEXT, 
    ID_NODE_VIEW, 
    ID_NODE_EXPORT, 
    ID_WINDOW_PERSPECTIVE, 
    ID_WINDOW_PERSPECTIVE_LOAD, 
    ID_WINDOW_PERSPECTIVE_RESET, 
    ID_WINDOW_PERSPECTIVE_SAVE, 

    ID_TOOL_LIST_APPEND, 
    ID_TOOL_LIST_REMOVE
  };

 private:
  Type type_;

 public:
  Menu(Type type = Type::NONE);
  ~Menu() override = default;

  WXDRAW_GETTER(Type, type_);
};
}
