#pragma once

namespace wxdraw::file {
/**
   出力基底クラス
*/
class Exporter {
 private:
  NodePtr node_;

 public:
  Exporter(const NodePtr& node);
  virtual ~Exporter() = default;

  WXDRAW_GETTER(Node, node_);

  virtual bool save() = 0;
};
}
