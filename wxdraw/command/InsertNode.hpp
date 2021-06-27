#pragma once

namespace wxdraw::command {
/**
   ノードを挿入する
 */
class InsertNode
  : public wxCommand
{
  using super = wxCommand;

 private:
  NodePtr node_;
  NodePtr parent_;
  size_t index_;

 public:
  InsertNode(const NodePtr& node, const NodePtr& parent, size_t index);
  ~InsertNode() override = default;

 protected:
  bool Do() override;
  bool Undo() override;
};
}
