#include "wxdraw/component/PaletteComponent.hpp"
#include "wxdraw/gui/ColorProperty.hpp"
#include "wxdraw/node/Node.hpp"

namespace wxdraw::gui {
/**
 */
ColorProperty::ColorProperty(const wxString& label, 
                             const wxString& name, 
                             ColorIndex value, 
                             ComponentBase& component)
  : ColorProperty(label, name, value, component, 
                  component.getNode()->getParentComponent<PaletteComponent>())
{
}
/**
 */
wxColour ColorProperty::GetColour(int index) const {
  return palette_->getColors().at(index).color;
}
/**
 */
ColorProperty::ColorProperty(const wxString& label, 
                             const wxString& name, 
                             ColorIndex value, 
                             ComponentBase& component, 
                             const PaletteComponentPtr& palette)
  : super(label, name, palette->getLabels().data(), nullptr, &choices_, 
          wxColourPropertyValue()), 
    palette_(palette)
{
  Init(static_cast<int>(value), component.getColor(value));
}
}
