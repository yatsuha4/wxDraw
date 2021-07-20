#pragma once

namespace wxdraw::command {
/**
   コマンド基底クラス
*/
class Command
  : public wxCommand
{
  using super = wxCommand;

 private:
  MainFrame* mainFrame_;

 public:
  ~Command() override = default;

  WXDRAW_GETTER(MainFrame, mainFrame_);

 protected:
  Command(const wxString& name, MainFrame* mainFrame);
};
}
