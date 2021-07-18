#include "wxdraw/gui/Inspector.hpp"
#include "wxdraw/gui/MainFrame.hpp"
#include "wxdraw/gui/Menu.hpp"
#include "wxdraw/gui/Palette.hpp"
#include "wxdraw/gui/PaletteListBase.hpp"
#include "wxdraw/palette/Gradient.hpp"

namespace wxdraw::gui {
/**
 */
PaletteListBase::PaletteListBase(wxWindow* window, Palette* palette)
  : super(window, wxID_ANY), 
    palette_(palette), 
    list_(new wxListView(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 
                         wxLC_REPORT | wxLC_ICON)), 
    imageList_(new wxImageList(PaletteItem::BITMAP_SIZE.GetWidth(), 
                               PaletteItem::BITMAP_SIZE.GetHeight())), 
    index_(0)
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
  Bind(wxEVT_LIST_ITEM_ACTIVATED, &PaletteListBase::onListItemSelected, this, list_->GetId());
  Bind(wxEVT_LIST_ITEM_SELECTED, &PaletteListBase::onListItemSelected, this, list_->GetId());
  Bind(wxEVT_TOOL, &PaletteListBase::onTool, this);
}
/**
 */
int PaletteListBase::appendImage(const wxBitmap& bitmap) {
  return imageList_->Add(bitmap);
}
/**
 */
const PaletteComponentPtr& PaletteListBase::getPaletteComponent() const {
  return getPalette()->getPaletteComponent();
}
/**
 */
void PaletteListBase::onSelectItem(const PaletteItemPtr& item) {
  getPalette()->getMainFrame()->getInspector()->show(item->createProperty());
}
/**
 */
void PaletteListBase::onListItemSelected(wxListEvent& event) {
  auto index = event.GetIndex();
  if(auto item = getItem(index)) {
    if(index_ < list_->GetItemCount()) {
      list_->SetItemBackgroundColour(index_, wxTransparentColor);
    }
    index_ = index;
    list_->SetItemBackgroundColour(index_, wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHT));
    onSelectItem(item);
    list_->SetItemState(index_, 0, wxLIST_STATE_SELECTED);
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
