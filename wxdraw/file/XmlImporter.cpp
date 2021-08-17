#include "wxdraw/component/BrushComponent.hpp"
#include "wxdraw/component/CompositionComponent.hpp"
#include "wxdraw/component/ContainerComponent.hpp"
#include "wxdraw/component/EllipseComponent.hpp"
#include "wxdraw/component/ExportComponent.hpp"
#include "wxdraw/component/GridComponent.hpp"
#include "wxdraw/component/LayerComponent.hpp"
#include "wxdraw/component/LayoutComponent.hpp"
#include "wxdraw/component/PaletteComponent.hpp"
#include "wxdraw/component/PenComponent.hpp"
#include "wxdraw/component/ProjectComponent.hpp"
#include "wxdraw/component/ProxyComponent.hpp"
#include "wxdraw/component/RectangleComponent.hpp"
#include "wxdraw/component/TextComponent.hpp"
#include "wxdraw/component/ViewComponent.hpp"
#include "wxdraw/file/XmlImporter.hpp"
#include "wxdraw/node/Node.hpp"
#include "wxdraw/palette/Brush.hpp"
#include "wxdraw/palette/Color.hpp"
#include "wxdraw/palette/Gradient.hpp"
#include "wxdraw/palette/GradientStop.hpp"
#include "wxdraw/palette/Pen.hpp"
#include "wxdraw/property/Choice.hpp"
#include "wxdraw/property/Property.hpp"

namespace wxdraw::file {
/**
   コンストラクタ
*/
XmlImporter::XmlImporter(const wxString& fileName)
  : super(), 
    fileName_(fileName), 
    document_(fileName)
{
}
/**
 */
NodePtr XmlImporter::load(const NodePtr& parent) {
  if(document_.IsOk()) {
    return generateNode(*document_.GetRoot(), parent);
  }
  return nullptr;
}
/**
   XMLからノードを生成する
   @param xml XML
   @return 生成したノード
*/
NodePtr XmlImporter::generateNode(const wxXmlNode& xml, const NodePtr& parent) {
  auto node = std::make_shared<Node>(xml.GetName().ToStdString(), parent);
  parseProperty(xml, *node->generateProperty());
  entryNode(node);
  for(auto componentXml = xml.GetChildren();
      componentXml;
      componentXml = componentXml->GetNext()) {
    if(auto component = GenerateComponent(node, *componentXml)) {
      parseProperty(*componentXml, *component->generateProperty());
      if(auto container = ContainerComponent::As(component)) {
        for(auto child = componentXml->GetChildren(); child; child = child->GetNext()) {
          container->getChildren().push_back(generateNode(*child, node));
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
      parseProperty(*xml, *color->generateProperty());
      palette_->getItems<Color>().push_back(color);
    }
    else if(xml->GetName() == Gradient::TYPE) {
      auto gradient = std::make_shared<Gradient>(palette_);
      parseProperty(*xml, *gradient->generateProperty());
      for(auto child = xml->GetChildren(); child; child = child->GetNext()) {
        if(child->GetName() == GradientStop::TYPE) {
          auto stop = std::make_shared<GradientStop>(palette_);
          parseProperty(*child, *stop->generateProperty());
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
      parseProperty(*xml, *pen->generateProperty());
      palette_->getItems<Pen>().push_back(pen);
    }
    else if(xml->GetName() == Brush::TYPE) {
      auto brush = std::make_shared<Brush>(palette_);
      parseProperty(*xml, *brush->generateProperty());
      palette_->getItems<Brush>().push_back(brush);
    }
    else if(xml->GetName() == Font::TYPE) {
      auto font = std::make_shared<Font>(palette_);
      parseProperty(*xml, *font->generateProperty());
      palette_->getItems<Font>().push_back(font);
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
ComponentBasePtr XmlImporter::GenerateComponent(const NodePtr& node, const wxXmlNode& xml) {
  return GenerateComponent<
    BrushComponent, 
    CompositionComponent, 
    ContainerComponent, 
    EllipseComponent, 
    ExportComponent, 
    GridComponent, 
    LayerComponent, 
    LayoutComponent, 
    PaletteComponent, 
    PenComponent, 
    ProjectComponent, 
    ProxyComponent, 
    RectangleComponent, 
    TextComponent, 
    ViewComponent
    >(node, xml);
}
/**
 */
bool XmlImporter::fromString(const wxString& src, int& dst) {
  long value;
  if(wxNumberFormatter::FromString(src, &value)) {
    dst = static_cast<int>(value);
    return true;
  }
  return false;
}
/**
 */
bool XmlImporter::fromString(const wxString& src, double& dst) {
  return wxNumberFormatter::FromString(src, &dst);
}
/**
 */
bool XmlImporter::fromString(const wxString& src, bool& dst) {
  int value;
  if(fromString(src, value)) {
    dst = static_cast<bool>(value);
    return true;
  }
  return false;
}
/**
 */
bool XmlImporter::fromString(const wxString& src, wxString& dst) {
  dst = src;
  return true;
}
/**
 */
bool XmlImporter::fromString(const wxString& src, wxColour& dst) {
  dst = wxColour(src);
  return true;
}
/**
 */
bool XmlImporter::fromString(const wxString& src, wxFileName& dst) {
  dst.Assign(src);
  return dst.MakeAbsolute(fileName_.GetPath());
}
/**
 */
bool XmlImporter::fromString(const wxString& src, wxFont& dst) {
  dst = wxFont(src);
  return true;
}
/**
 */
bool XmlImporter::fromString(const wxString& src, Choice& dst) {
  dst.setItem(src);
  return true;
}
/**
 */
bool XmlImporter::fromString(const wxString& src, NodePtr& dst) {
  getNode(src, dst);
  return true;
}
/**
   ノードを登録する
   @param node ノード
 */
void XmlImporter::entryNode(const NodePtr& node) {
  wxASSERT(!node->getId().IsEmpty());
  nodes_[node->getId()] = node;
  auto lower = nodeRefs_.lower_bound(node->getId());
  auto upper = nodeRefs_.upper_bound(node->getId());
  if(lower != upper) {
    for(auto iter = lower; iter != upper; iter++) {
      iter->second = node;
    }
    nodeRefs_.erase(lower, upper);
  }
}
/**
   IDからノードを取得する
   @param id ID
   @param node 取得先
*/
void XmlImporter::getNode(const wxString& id, NodePtr& node) {
  auto iter = nodes_.find(id);
  if(iter != nodes_.end()) {
    node = iter->second;
  }
  else {
    nodeRefs_.emplace(id, node);
  }
}
/**
 */
void XmlImporter::Warning(const wxString& message, const wxXmlNode& xml) {
  wxLogWarning("%s, '%s'(line:%d)", message, xml.GetName(), xml.GetLineNumber());
}
}
