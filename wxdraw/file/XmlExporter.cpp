#include "wxdraw/component/ContainerComponent.hpp"
#include "wxdraw/component/PaletteComponent.hpp"
#include "wxdraw/file/XmlExporter.hpp"
#include "wxdraw/node/Node.hpp"
#include "wxdraw/property/Member.hpp"
#include "wxdraw/property/Property.hpp"
#include "wxdraw/property/PropertyMember.hpp"

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
  return createXml(node, *node.createProperty());
}
/**
 */
wxXmlNode* XmlExporter::createXml(Node& node, const Property& property) {
  auto xml = new wxXmlNode(wxXML_ELEMENT_NODE, property.getName());
  for(auto& member : property.getMembers()) {
    if(auto component = std::dynamic_pointer_cast<PropertyMember>(member)) {
      auto componentXml = createXml(node, *component->getProperty());
      xml->AddChild(componentXml);
      if(component->getProperty()->getName() == ContainerComponent::TYPE) {
        for(auto& child : node.getContainer()->getChildren()) {
          componentXml->AddChild(createXml(*child));
        }
      }
    }
    else {
      xml->AddAttribute(member->getName(), getValue(member));
    }
  }
  return xml;
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
wxString XmlExporter::toString(const PenPtr& value) const {
  return toString(static_cast<int>(palette_->getIndex(value)));
}
/**
 */
wxString XmlExporter::toString(const BrushPtr& value) const {
  return toString(static_cast<int>(palette_->getIndex(value)));
}
}
