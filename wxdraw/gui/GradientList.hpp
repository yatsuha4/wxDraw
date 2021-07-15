#pragma once

#include "wxdraw/gui/EditableList.hpp"

namespace wxdraw::gui {
/**
 */
class GradientList
  : public EditableList
{
  using super = EditableList;

 public:
  GradientList(wxWindow* parent);
  ~GradientList() override = default;
};
}
