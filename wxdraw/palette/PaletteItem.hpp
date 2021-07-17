#pragma once

namespace wxdraw::palette {
/**
   パレット要素基底クラス
*/
class PaletteItem {
 public:
  PaletteItem() = default;
  PaletteItem(const PaletteItem& src) = default;
  virtual ~PaletteItem() = default;

  virtual void onCreate() {}
  virtual PropertyPtr createProperty(const PaletteComponentPtr& palette) = 0;

 protected:
  PropertyPtr createProperty(const char* type, 
                             const PaletteComponentPtr& palette);
};
}
