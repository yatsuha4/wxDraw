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
  wxXmlDocument document_;

 public:
  XmlExporter(const NodePtr& node);
  ~XmlExporter() override = default;

  bool save(wxOutputStream& output) override;

  static wxString ToString(int value);
  static wxString ToString(double value);
  static wxString ToString(bool value);

 private:
  wxXmlNode* parse(const NodePtr& node);
  wxXmlNode* parse(const Property& property);
  static wxString GetValue(const MemberBasePtr& member);
};
}
