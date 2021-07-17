#pragma once

#include "wxdraw/property/PropertyOwner.hpp"

namespace wxdraw::palette {
/**
   パレット要素基底クラス
*/
class PaletteItem
  : public PropertyOwner
{
 public:
  PaletteItem() = default;
  PaletteItem(const PaletteItem& src) = default;
  ~PaletteItem() override = default;

  virtual void onCreate(const PaletteComponentPtr& palette) {}
  virtual PropertyPtr createProperty() = 0;
};
}
