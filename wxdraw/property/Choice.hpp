#pragma once

namespace wxdraw::property {
/**
 */
class Choice {
 public:
  class GradientType;
  class PenStyle;

 private:
  const char** items_;
  size_t index_;

 public:
  Choice();
  Choice(const char** items);
  Choice(const Choice& src) = default;
  virtual ~Choice() = default;

  Choice& operator=(const Choice& src);

  WXDRAW_GETTER(Items, items_);
  WXDRAW_ACCESSOR(Index, index_);

  void setItem(const wxString& item);
};
/**
 */
class Choice::GradientType
  : public Choice
{
 public:
  enum {
    LINEAR, 
    RADIAL
  };

 private:
  static const char* ITEMS[];

 public:
  GradientType() : Choice(ITEMS) {}
  GradientType(const GradientType& src) = default;
  ~GradientType() = default;
};
/**
   ペンのスタイル
*/
class Choice::PenStyle
  : public Choice
{
 public:
  enum {
    SOLID, 
    DOT, 
    LONG_DASH, 
    SHORT_DASH, 
    DOT_DASH, 
    BDIAGONAL_HATCH, 
    CROSSDIAG_HATCH, 
    FDIAGONAL_HATCH, 
    CROSS_HATCH, 
    HORIZONTAL_HATCH, 
    VERTICAL_HATCH
  };

 private:
  static const char* ITEMS[];

 public:
  PenStyle() : Choice(ITEMS) {}
  PenStyle(const PenStyle& src) = default;
  ~PenStyle() = default;
};
}
