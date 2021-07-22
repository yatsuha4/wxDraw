#pragma once

namespace wxdraw::property {
/**
 */
class Choice {
 public:
  class GradientType;

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
  using super = Choice;

 public:
  enum {
    LINEAR, 
    RADIAL
  };

 private:
  static const char* ITEMS[];

 public:
  GradientType();
  GradientType(const GradientType& src) = default;
  ~GradientType() = default;
};
}
