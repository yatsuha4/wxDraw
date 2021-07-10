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

  virtual bool save(wxOutputStream& output) = 0;

 protected:
  Exporter(const NodePtr& node);
};
}
