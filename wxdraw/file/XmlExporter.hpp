#pragma once

#include "wxdraw/file/Exporter.hpp"

namespace wxdraw::file {
/**
   XML出力
*/
class XmlExporter
  : public Exporter
{
  using super = Exporter;

 private:
  wxFileName fileName_;
  wxXmlDocument document_;

 public:
  XmlExporter(const NodePtr& node, const wxFileName& fileName);
  ~XmlExporter() override = default;

  bool save() override;

  static wxString ToString(int value);
  static wxString ToString(double value);
  static wxString ToString(bool value);

 private:
  wxXmlNode* parse(const NodePtr& node);
  wxXmlNode* parse(const Property& property);
  wxString getValue(const MemberBasePtr& member);
};
}
