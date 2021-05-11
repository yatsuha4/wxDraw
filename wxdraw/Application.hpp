﻿#pragma once

namespace wxdraw {
/**
   アプリケーション
*/
class Application
  : public wxApp
{
  using super = wxApp;

 private:
  MainFrame* mainFrame_;

 public:
  Application();
  ~Application() override = default;

 protected:
  bool OnInit() override;
};
}
