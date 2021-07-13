#include "wxdraw/component/ComponentBase.hpp"
#include "wxdraw/file/XmlExporter.hpp"
#include "wxdraw/node/Node.hpp"
#include "wxdraw/property/Member.hpp"

namespace wxdraw::file {
/**
   コンストラクタ
*/
XmlExporter::XmlExporter(const NodePtr& node)
  : super(node)
{
  document_.SetRoot(parse(node));
}
/**
   出力
*/
bool XmlExporter::save(wxOutputStream& output) {
  return document_.Save(output);
}
/**
 */
wxString XmlExporter::ToString(int value) {
  return wxNumberFormatter::ToString(static_cast<long>(value), wxNumberFormatter::Style_None);
}
/**
 */
wxString XmlExporter::ToString(double value) {
  return wxNumberFormatter::ToString(value, 16, wxNumberFormatter::Style_NoTrailingZeroes);
}
/**
 */
wxString XmlExporter::ToString(bool value) {
  return ToString(static_cast<int>(value));
}
/**
 */
wxXmlNode* XmlExporter::parse(const NodePtr& node) {
  auto xml = parse(*node);

  auto components = new wxXmlNode(wxXML_ELEMENT_NODE, "Components");
  for(auto& component : node->getComponents()) {
    components->AddChild(parse(*component));
  }
  xml->AddChild(components);

  for(auto& child : node->getChildren()) {
    xml->AddChild(parse(child));
  }
  return xml;
}
/**
 */
wxXmlNode* XmlExporter::parse(const Property& property) {
  auto xml = new wxXmlNode(wxXML_ELEMENT_NODE, property.getName());
  for(auto& member : property.getMembers()) {
    xml->AddAttribute(member->getName(), GetValue(member));
  }
  return xml;
}
/**
 */
wxString XmlExporter::GetValue(const MemberBasePtr& member) {
  if(auto m = Member<int>::As(member)) {
    return ToString(m->getValue());
  }
  else if(auto m = Member<double>::As(member)) {
    return ToString(m->getValue());
  }
  else if(auto m = Member<bool>::As(member)) {
    return ToString(m->getValue());
  }
  else if(auto m = Member<std::string>::As(member)) {
    return m->getValue();
  }
  else if(auto m = Member<wxColour>::As(member)) {
    return m->getValue().GetAsString();
  }
  wxLogError("illegal member");
  return wxEmptyString;
}
}
