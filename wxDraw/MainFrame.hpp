/***********************************************************************//**
	@file
***************************************************************************/
#pragma once

namespace wxdraw {
/***********************************************************************//**
	@brief 
***************************************************************************/
class MainFrame
  : public wxFrame
{
  using super = wxFrame;

 private:
  Application& application_;
  wxAuiManager auiManager_;
  Canvas* canvas_;

 public:
  MainFrame(Application& application);
  ~MainFrame() override;

 private:
  void setupMenuBar();
  void onSelectMenu(wxCommandEvent& event);
};
/***********************************************************************//**
	$Id$
***************************************************************************/
}
