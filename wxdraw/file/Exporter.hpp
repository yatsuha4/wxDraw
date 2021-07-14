#pragma once

namespace wxdraw::file {
/**
   出力基底クラス
*/
class Exporter {
 private:
  NodePtr node_;

 public:
  virtual ~Exporter() = default;

  WXDRAW_GETTER(Node, node_);

  virtual bool save(const wxString& fileName);
  virtual bool save(wxOutputStream& output);

 protected:
  Exporter(const NodePtr& node);
};
}
