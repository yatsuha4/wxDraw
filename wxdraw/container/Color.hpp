#pragma once

namespace wxdraw::container {
/**
   カラー
*/
class Color {
 public:
  wxString label;
  wxColour color;

 public:
  Color(const wxString& label, const wxColour& color)
    : label(label), 
      color(color)
  {}
  Color(const Color& src) = default;
  ~Color() = default;
};
}
