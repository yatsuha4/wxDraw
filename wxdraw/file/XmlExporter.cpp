#include "wxdraw/component/ContainerComponent.hpp"
#include "wxdraw/component/PaletteComponent.hpp"
#include "wxdraw/file/XmlExporter.hpp"
#include "wxdraw/node/Node.hpp"
#include "wxdraw/palette/Brush.hpp"
#include "wxdraw/palette/Color.hpp"
#include "wxdraw/palette/Font.hpp"
#include "wxdraw/palette/Gradient.hpp"
#include "wxdraw/palette/GradientStop.hpp"
#include "wxdraw/palette/Pen.hpp"
#include "wxdraw/property/Member.hpp"
#include "wxdraw/property/Property.hpp"
#include "wxdraw/property/PropertyMember.hpp"
#include "wxdraw/property/Choice.hpp"

namespace wxdraw::file {
/**
   コンストラクタ
*/
XmlExporter::XmlExporter(const NodePtr& node, const wxFileName& fileName)
  : super(node), 
    fileName_(fileName), 
    palette_(Node::GetParentComponent<PaletteComponent>(node))
{
  document_.SetRoot(createXml(*node));
}
/**
   出力
*/
bool XmlExporter::save() {
  wxFileOutputStream output(fileName_.GetFullPath());
  return document_.Save(output);
}
/**
 */
wxXmlNode* XmlExporter::createXml(Node& node) {
  return createXml(*node.generateProperty());
}
/**
 */
wxXmlNode* XmlExporter::createXml(const Property& property) {
  auto xml = new wxXmlNode(wxXML_ELEMENT_NODE, property.getObject()->getType());
  for(auto& member : property.getMembers()) {
    if(auto child = std::dynamic_pointer_cast<PropertyMember>(member)) {
      auto childXml = createXml(*child->getProperty());
      auto component = std::dynamic_pointer_cast<ComponentBase>
        (child->getProperty()->getObject());
      wxASSERT(component);
      if(auto palette = PaletteComponent::As(component)) {
        parsePalette(palette, childXml);
      }
      else if(auto container = ContainerComponent::As(component)) {
        for(auto& node : container->getChildren()) {
          childXml->AddChild(createXml(*node));
        }
      }
      xml->AddChild(childXml);
    }
    else {
      xml->AddAttribute(member->getName(), getValue(member));
    }
  }
  return xml;
}
/**
   パレットをXMLに書き出す
   @param palette パレット
   @param parent 親XMLノード
*/
void XmlExporter::parsePalette(const PaletteComponentPtr& palette, wxXmlNode* parent) {
  for(auto& color : palette->getItems<Color>()) {
    parent->AddChild(createXml(*color->generateProperty()));
  }
  for(auto& gradient : palette->getItems<Gradient>()) {
    auto xml = createXml(*gradient->generateProperty());
    for(auto& stop : gradient->getStops()) {
      xml->AddChild(createXml(*stop->generateProperty()));
    }
    parent->AddChild(xml);
  }
  for(auto& pen : palette->getItems<Pen>()) {
    parent->AddChild(createXml(*pen->generateProperty()));
  }
  for(auto& brush : palette->getItems<Brush>()) {
    parent->AddChild(createXml(*brush->generateProperty()));
  }
  for(auto& font : palette->getItems<Font>()) {
    parent->AddChild(createXml(*font->generateProperty()));
  }
}
/**
 */
wxString XmlExporter::getValue(const MemberBasePtr& member) {
  wxString value;
  if(!getValue<WXDRAW_PROPERTY_CLASSES>(member, value)) {
    wxLogError("illegal member");
  }
  return value;
}
/**
 */
wxString XmlExporter::toString(int value) const {
  return wxNumberFormatter::ToString(static_cast<long>(value), wxNumberFormatter::Style_None);
}
/**
 */
wxString XmlExporter::toString(double value) const {
  return wxNumberFormatter::ToString(value, 16, wxNumberFormatter::Style_NoTrailingZeroes);
}
/**
 */
wxString XmlExporter::toString(bool value) const {
  return toString(static_cast<int>(value));
}
/**
 */
wxString XmlExporter::toString(const wxString& value) const {
  return value;
}
/**
 */
wxString XmlExporter::toString(const wxColour& value) const {
  return value.GetAsString(wxC2S_HTML_SYNTAX);
}
/**
 */
wxString XmlExporter::toString(const wxFileName& value) const {
  auto fileName(value);
  fileName.MakeRelativeTo(fileName_.GetPath());
  return fileName.GetFullPath();
}
/**
 */
wxString XmlExporter::toString(const wxFont& value) const {
  return value.GetNativeFontInfoDesc();
}
/**
 */
wxString XmlExporter::toString(const Choice& value) const {
  return value.getItems()[value.getIndex()];
}
/**
 */
wxString XmlExporter::toString(const ObjectPtr& value) const {
  if(value) {
    return value->getId();
  }
  return wxEmptyString;
}
}
