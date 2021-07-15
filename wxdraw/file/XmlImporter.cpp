#include "wxdraw/component/BrushComponent.hpp"
#include "wxdraw/component/ContainerComponent.hpp"
#include "wxdraw/component/EllipseComponent.hpp"
#include "wxdraw/component/GridComponent.hpp"
#include "wxdraw/component/LayerComponent.hpp"
#include "wxdraw/component/LayoutComponent.hpp"
#include "wxdraw/component/RectangleComponent.hpp"
#include "wxdraw/file/XmlImporter.hpp"
#include "wxdraw/node/Node.hpp"
#include "wxdraw/property/Property.hpp"

namespace wxdraw::file {
/**
   コンストラクタ
*/
XmlImporter::XmlImporter(const wxString& fileName)
  : super(), 
    document_(fileName)
{
}
/**
 */
NodePtr XmlImporter::load() {
  if(document_.IsOk()) {
    return createNode(*document_.GetRoot());
  }
  return nullptr;
}
/**
 */
bool XmlImporter::FromString(const wxString& text, int& value) {
  long v;
  if(wxNumberFormatter::FromString(text, &v)) {
    value = static_cast<int>(v);
    return true;
  }
  return false;
}
/**
 */
bool XmlImporter::FromString(const wxString& text, double& value) {
  return wxNumberFormatter::FromString(text, &value);
}
/**
 */
bool XmlImporter::FromString(const wxString& text, bool& value) {
  long v;
  if(wxNumberFormatter::FromString(text, &v)) {
    value = static_cast<bool>(v);
    return true;
  }
  return false;
}
/**
   XMLからノードを生成する
   @param xml XML
   @return 生成したノード
*/
NodePtr XmlImporter::createNode(const wxXmlNode& xml) {
  auto node = std::make_shared<Node>(xml.GetName().ToStdString());
  parseProperty(xml, *node->createProperty());
  for(auto componentXml = xml.GetChildren();
      componentXml;
      componentXml = componentXml->GetNext()) {
    if(auto component = CreateComponent(node, *componentXml)) {
      parseProperty(*componentXml, *component->createProperty());
      if(auto container = std::dynamic_pointer_cast<ContainerComponent>(component)) {
        for(auto child = componentXml->GetChildren(); child; child = child->GetNext()) {
          Node::Append(createNode(*child), node);
        }
      }
    }
    else {
      Warning("syntax error", *componentXml);
    }
  }
  return node;
}
/**
   メンバーに値を書き込む
   @param xml XMLノード
   @param property プロパティ
*/
void XmlImporter::parseProperty(const wxXmlNode& xml, const Property& property) {
  for(auto& member : property.getMembers()) {
    wxString text;
    if(xml.GetAttribute(member->getName(), &text)) {
      if(auto m = Member<int>::As(member)) {
        FromString(text, m->getValue());
      }
      else if(auto m = Member<double>::As(member)) {
        FromString(text, m->getValue());
      }
      else if(auto m = Member<bool>::As(member)) {
        FromString(text, m->getValue());
      }
      else if(auto m = Member<wxString>::As(member)) {
        m->getValue() = text;
      }
      else if(auto m =  Member<wxColour>::As(member)) {
        m->getValue() = wxColour(text);
      }
    }
  }
}
/**
 */
ComponentBasePtr XmlImporter::CreateComponent(const NodePtr& node, const wxXmlNode& xml) {
  return CreateComponent<BrushComponent, 
                        ContainerComponent, 
                        EllipseComponent, 
                        GridComponent, 
                        LayerComponent, 
                        LayoutComponent, 
                        RectangleComponent>(node, xml);
}
/**
 */
void XmlImporter::Warning(const wxString& message, const wxXmlNode& xml) {
  wxLogWarning("%s, '%s'(line:%d)", message, xml.GetName(), xml.GetLineNumber());
}
}
