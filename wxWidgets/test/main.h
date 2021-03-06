#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif 

class MyApp : public wxApp
{
public:
	virtual bool OnInit();
};

class MyFrame :public wxFrame
{
public:
	MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
private:
	void OnHello(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};

enum
{
	ID_Hello = 1
};

//
//wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
//EVT_MENU(ID_Hello, MyFrame::OnHello)
//EVT_MENU(wxID_EXIT, MyFrame::OnExit)
//EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
//wxEND_EVENT_TABLE()
