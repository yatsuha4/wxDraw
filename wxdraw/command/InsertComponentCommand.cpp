#include "wxdraw/command/InsertComponentCommand.hpp"
#include "wxdraw/gui/MainFrame.hpp"

namespace wxdraw::command {
/**
   コンストラクタ
*/
InsertComponentCommand::InsertComponentCommand(MainFrame* mainFrame, 
                                               const ComponentBasePtr& component, 
                                               const NodePtr& node)
  : super("InsertComponent", mainFrame), 
    component_(component), 
    node_(node)
{
}
/**
 */
bool InsertComponentCommand::Do() {
  getMainFrame()->appendComponent(component_, node_);
  return true;
}
/**
 */
bool InsertComponentCommand::Undo() {
  getMainFrame()->removeComponent(component_);
  return true;
}
}
