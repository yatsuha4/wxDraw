#pragma once

#include "wxdraw/gui/PaletteList.hpp"

namespace wxdraw::gui {
/**
 */
class GradientStopList
  : public PaletteList<GradientStop>
{
  using super = PaletteList<GradientStop>;
  using super::PaletteList;

 private:
  GradientPtr gradient_;

 public:
  void setGradient(const GradientPtr& gradient) override;

 protected:
  List<GradientStop>& getItems() const override;
  bool canAppendItem(size_t index) const override;
  GradientStopPtr getRemoveItem(size_t index) const override;
};
}
