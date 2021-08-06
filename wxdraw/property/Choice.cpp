#include "wxdraw/property/Choice.hpp"

namespace wxdraw::property {
const char* Choice::Composition::ITEMS[] = {
  "Clear", 
  "Source", 
  "Over", 
  "In", 
  "Out", 
  "Atop", 
  "Dest", 
  "DestOver", 
  "DestIn", 
  "DestOut", 
  "DestAtop", 
  "Xor", 
  "Add", 
  nullptr
};
const char* Choice::Fit::ITEMS[] = {
  "None", 
  "Expand", 
  "Shrink"
};
const char* Choice::GradientType::ITEMS[] = {
  "Linear", 
  "Radial", 
  nullptr
};
const char* Choice::PenCap::ITEMS[] = {
  "Round", 
  "Projecting", 
  "Butt", 
  nullptr
};
const char* Choice::PenJoin::ITEMS[] = {
  "Round", 
  "Bevel", 
  "Miter", 
  nullptr
};
const char* Choice::PenStyle::ITEMS[] = {
  "Solid", 
  "Dot", 
  "LongDash", 
  "ShortDash", 
  "DotDash", 
  "BackwardDiagonalHatch", 
  "CrossDiagnonalHatch", 
  "ForwardDiagonalHatch", 
  "CrossHatch", 
  "HorizontalHatch", 
  "VerticalHatch", 
  nullptr
};
/**
 */
Choice::Choice()
  : Choice(nullptr)
{}
/**
   コンストラクタ
*/
Choice::Choice(const char** items)
  : items_(items), 
    index_(0)
{}
/**
 */
Choice& Choice::operator=(const Choice& src) {
  index_ = src.index_;
  return *this;
}
/**
 */
void Choice::setItem(const wxString& item) {
  for(size_t i = 0; items_[i]; i++) {
    if(item == items_[i]) {
      index_ = i;
      return;
    }
  }
  wxLogWarning("no such value, '%s'", item);
  index_ = 0;
}
}
