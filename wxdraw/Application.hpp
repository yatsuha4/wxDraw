#pragma once

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

  static Application* GetInstance();

 protected:
  bool OnInit() override;
};
}
