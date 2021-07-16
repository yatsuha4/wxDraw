#include "wxdraw/gui/PaletteList.hpp"
#include "wxdraw/gui/Menu.hpp"

namespace wxdraw::gui {
/**
 */
PaletteList::PaletteList(wxWindow* window, Palette* palette, const wxString& label)
  : super(window, wxID_ANY, label), 
    palette_(palette), 
    list_(new wxListView(this, wxID_ANY))
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
  Bind(wxEVT_LIST_ITEM_SELECTED, &PaletteList::onListItemSelected, this, list_->GetId());
}
}
