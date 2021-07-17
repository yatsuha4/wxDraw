#include "wxdraw/gui/Inspector.hpp"
#include "wxdraw/gui/MainFrame.hpp"
#include "wxdraw/gui/Menu.hpp"
#include "wxdraw/gui/Palette.hpp"
#include "wxdraw/gui/PaletteListBase.hpp"
#include "wxdraw/palette/PaletteItem.hpp"

namespace wxdraw::gui {
const wxSize PaletteListBase::IMAGE_SIZE(32, 32);
/**
 */
PaletteListBase::PaletteListBase(wxWindow* window, Palette* palette)
  : super(window, wxID_ANY), 
    palette_(palette), 
    list_(new wxListView(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 
                         wxLC_REPORT | wxLC_ICON)), 
    imageList_(new wxImageList(IMAGE_SIZE.GetWidth(), IMAGE_SIZE.GetHeight()))
{
  auto sizer = new wxBoxSizer(wxVERTICAL);
  sizer->Add(list_, wxSizerFlags().Expand().Proportion(1));
  auto toolBar = new wxToolBar(this, wxID_ANY);
  toolBar->AddTool(Menu::ID_TOOL_LIST_APPEND, "Append", 
                   wxArtProvider::GetBitmap(wxART_PLUS, wxART_TOOLBAR));
  toolBar->AddTool(Menu::ID_TOOL_LIST_REMOVE, "Remove", 
                   wxArtProvider::GetBitmap(wxART_MINUS, wxART_TOOLBAR));
  sizer->Add(toolBar, wxSizerFlags().Expand());
  SetSizerAndFit(sizer);
  list_->SetImageList(imageList_.get(), wxIMAGE_LIST_NORMAL);
  Bind(wxEVT_LIST_ITEM_SELECTED, &PaletteListBase::onListItemSelected, this, list_->GetId());
  Bind(wxEVT_TOOL, &PaletteListBase::onTool, this);
}
/**
 */
void PaletteListBase::update() {
  list_->Freeze();
  list_->DeleteAllItems();
  onUpdate();
  list_->Thaw();
}
/**
 */
const PaletteComponentPtr& PaletteListBase::getPaletteComponent() const {
  return getPalette()->getPaletteComponent();
}
/**
 */
PaletteItemPtr PaletteListBase::getItem(size_t index) const {
  return nullptr;
}
/**
 */
void PaletteListBase::onListItemSelected(wxListEvent& event) {
  index_ = event.GetIndex();
  if(auto item = getItem(index_)) {
    getPalette()->getMainFrame()->getInspector()->
      show(item->createProperty(getPaletteComponent()));
  }
}
/**
 */
void PaletteListBase::onTool(wxCommandEvent& event) {
  switch(event.GetId()) {
  case Menu::ID_TOOL_LIST_APPEND:
    appendItem(index_);
    break;
  case Menu::ID_TOOL_LIST_REMOVE:
    removeItem(index_);
    break;
  default:
    break;
  }
}
}
