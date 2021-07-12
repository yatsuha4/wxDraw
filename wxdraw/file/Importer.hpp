#pragma once

namespace wxdraw::file {
/**
   入力基底クラス
*/
class Importer {
 private:
  std::unique_ptr<wxInputStream> input_;

 public:
  virtual ~Importer() = default;

  NodePtr load(const wxString& fileName);

 protected:
  Importer() = default;

  virtual NodePtr onLoad() = 0;
  wxInputStream& getInput() const;
};
}
