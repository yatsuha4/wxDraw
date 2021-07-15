#include "wxdraw/command/InsertNodeCommand.hpp"
#include "wxdraw/component/ContainerComponent.hpp"
#include "wxdraw/gui/MainFrame.hpp"
#include "wxdraw/node/Node.hpp"

namespace wxdraw::command {
/**
   コンストラクタ
*/
InsertNodeCommand::InsertNodeCommand(MainFrame* mainFrame, 
                                     const NodePtr& node, 
                                     const NodePtr& parent)
  : InsertNodeCommand(mainFrame, node, parent, 
                      parent->getComponent<ContainerComponent>()->getChildren().size())
{
}
/**
   コンストラクタ
*/
InsertNodeCommand::InsertNodeCommand(MainFrame* mainFrame, 
                                     const NodePtr& node, 
                                     const NodePtr& parent, 
                                     size_t index)
  : super("InsertNode", mainFrame), 
    node_(node), 
    parent_(parent), 
    index_(index)
{
}
/**
 */
bool InsertNodeCommand::Do() {
  getMainFrame()->insertNode(node_, parent_, index_);
  return true;
}
/**
 */
bool InsertNodeCommand::Undo() {
  getMainFrame()->removeNode(node_);
  return true;
}
}
