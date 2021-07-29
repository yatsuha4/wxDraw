#pragma once

namespace wxdraw::property {
/**
 */
class Choice {
 public:
  class Composition;
  class GradientType;
  class PenCap;
  class PenJoin;
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
class Choice::Composition
  : public Choice
{
 private:
  static const char* ITEMS[];

 public:
  Composition() : Choice(ITEMS) {}
  Composition(const Composition& src) = default;
  ~Composition() override = default;
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
 */
class Choice::PenCap
  : public Choice
{
 public:
  enum {
    ROUND, 
    PROJECTING, 
    BUTT
  };

 private:
  static const char* ITEMS[];

 public:
  PenCap() : Choice(ITEMS) {}
  PenCap(const PenCap& src) = default;
  ~PenCap() = default;
};
/**
 */
class Choice::PenJoin
  : public Choice
{
 public:
  enum {
    ROUND, 
    BEVEL, 
    MITER
  };

 private:
  static const char* ITEMS[];

 public:
  PenJoin() : Choice(ITEMS) {}
  PenJoin(const PenJoin& src) = default;
  ~PenJoin() = default;
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
