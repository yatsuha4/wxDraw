#include "wxdraw/palette/PaletteItem.hpp"
#include "wxdraw/property/OptionProperty.hpp"

namespace wxdraw::palette {
/**
   プロパティを生成する
*/
PropertyPtr PaletteItem::createProperty(const char* type, 
                                        const PaletteComponentPtr& palette) {
  auto property = std::make_shared<OptionProperty<PaletteComponentPtr>>(type, palette);
  return property;
}
}
