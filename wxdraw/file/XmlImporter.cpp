#include "wxdraw/component/BrushComponent.hpp"
#include "wxdraw/component/ContainerComponent.hpp"
#include "wxdraw/component/EllipseComponent.hpp"
#include "wxdraw/component/GridComponent.hpp"
#include "wxdraw/component/LayerComponent.hpp"
#include "wxdraw/component/LayoutComponent.hpp"
#include "wxdraw/component/PaletteComponent.hpp"
#include "wxdraw/component/PenComponent.hpp"
#include "wxdraw/component/ProjectComponent.hpp"
#include "wxdraw/component/RectangleComponent.hpp"
#include "wxdraw/component/TextComponent.hpp"
#include "wxdraw/file/XmlImporter.hpp"
#include "wxdraw/node/Node.hpp"
#include "wxdraw/palette/Brush.hpp"
#include "wxdraw/palette/Color.hpp"
#include "wxdraw/palette/Gradient.hpp"
#include "wxdraw/palette/GradientStop.hpp"
#include "wxdraw/palette/Pen.hpp"
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
      if(auto container = ContainerComponent::As(component)) {
        for(auto child = componentXml->GetChildren(); child; child = child->GetNext()) {
          Node::Append(createNode(*child), node);
        }
      }
      else if(auto palette = PaletteComponent::As(component)) {
        palette_ = palette;
        parsePalette(*componentXml);
      }
    }
    else {
      Warning("syntax error", *componentXml);
    }
  }
  return node;
}
/**
 */
void XmlImporter::parsePalette(const wxXmlNode& parent) {
  for(auto xml = parent.GetChildren(); xml; xml = xml->GetNext()) {
    if(xml->GetName() == Color::TYPE) {
      auto color = std::make_shared<Color>(palette_);
      parseProperty(*xml, *color->createProperty());
      palette_->getItems<Color>().push_back(color);
    }
    else if(xml->GetName() == Gradient::TYPE) {
      auto gradient = std::make_shared<Gradient>(palette_);
      parseProperty(*xml, *gradient->createProperty());
      for(auto child = xml->GetChildren(); child; child = child->GetNext()) {
        if(child->GetName() == GradientStop::TYPE) {
          auto stop = std::make_shared<GradientStop>(palette_);
          parseProperty(*child, *stop->createProperty());
          gradient->getStops().push_back(stop);
        }
        else {
          Warning("syntax error", *child);
        }
      }
      palette_->getItems<Gradient>().push_back(gradient);
    }
    else if(xml->GetName() == Pen::TYPE) {
      auto pen = std::make_shared<Pen>(palette_);
      parseProperty(*xml, *pen->createProperty());
      palette_->getItems<Pen>().push_back(pen);
    }
    else if(xml->GetName() == Brush::TYPE) {
      auto brush = std::make_shared<Brush>(palette_);
      parseProperty(*xml, *brush->createProperty());
      palette_->getItems<Brush>().push_back(brush);
    }
    else {
      Warning("syntax error", *xml);
    }
  }
}
/**
   メンバーに値を書き込む
   @param xml XMLノード
   @param property プロパティ
*/
void XmlImporter::parseProperty(const wxXmlNode& xml, const Property& property) {
  for(auto& member : property.getMembers()) {
    wxString value;
    if(xml.GetAttribute(member->getName(), &value)) {
      if(!parseMember<WXDRAW_PROPERTY_CLASSES>(member, value)) {
        Warning("illegal member", xml);
      }
    }
  }
}
/**
 */
ComponentBasePtr XmlImporter::CreateComponent(const NodePtr& node, const wxXmlNode& xml) {
  return CreateComponent<
    BrushComponent, 
    ContainerComponent, 
    EllipseComponent, 
    GridComponent, 
    LayerComponent, 
    LayoutComponent, 
    PaletteComponent, 
    PenComponent, 
    ProjectComponent, 
    RectangleComponent, 
    TextComponent
    >(node, xml);
}
/**
 */
bool XmlImporter::fromString(const wxString& src, int& dst) const {
  long value;
  if(wxNumberFormatter::FromString(src, &value)) {
    dst = static_cast<int>(value);
    return true;
  }
  return false;
}
/**
 */
bool XmlImporter::fromString(const wxString& src, double& dst) const {
  return wxNumberFormatter::FromString(src, &dst);
}
/**
 */
bool XmlImporter::fromString(const wxString& src, bool& dst) const {
  int value;
  if(fromString(src, value)) {
    dst = static_cast<bool>(value);
    return true;
  }
  return false;
}
/**
 */
bool XmlImporter::fromString(const wxString& src, wxString& dst) const {
  dst = src;
  return true;
}
/**
 */
bool XmlImporter::fromString(const wxString& src, wxColour& dst) const {
  dst = wxColour(src);
  return true;
}
/**
 */
bool XmlImporter::fromString(const wxString& src, wxFileName& dst) const {
  return false;
}
/**
 */
bool XmlImporter::fromString(const wxString& src, wxFont& dst) const {
  dst = wxFont(src);
  return true;
}
/**
 */
bool XmlImporter::fromString(const wxString& src, PenPtr& dst) const {
  return fromStringPalette(src, dst);
}
/**
 */
bool XmlImporter::fromString(const wxString& src, BrushPtr& dst) const {
  return fromStringPalette(src, dst);
}
/**
 */
bool XmlImporter::fromString(const wxString& src, ColorPtr& dst) const {
  return fromStringPalette(src, dst);
}
/**
 */
bool XmlImporter::fromString(const wxString& src, ColorBasePtr& dst) const {
  return fromStringPalette(src, dst);
}
/**
 */
void XmlImporter::Warning(const wxString& message, const wxXmlNode& xml) {
  wxLogWarning("%s, '%s'(line:%d)", message, xml.GetName(), xml.GetLineNumber());
}
}
