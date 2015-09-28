/*
file: settings.cpp
*/

#include <windowsx.h>
#include <vector>
#include <boost/lexical_cast.hpp>
#include "resource.h"
#include "settings.h"

typedef std::basic_string<TCHAR> tstring;

static Settings s_settings;

void CentralizeWindow(HWND window, HWND parent = NULL) {
	if(NULL == parent) parent = GetDesktopWindow();
	RECT windowRect, parentRect;
	GetWindowRect(window, &windowRect);
	GetWindowRect(parent, &parentRect);
	SetWindowPos(window, HWND_TOP,
		(parentRect.right - parentRect.left) / 2 - 
			(windowRect.right - windowRect.left) / 2,
		(parentRect.bottom - parentRect.top) / 2 - 
			(windowRect.bottom - windowRect.top) / 2,
		0, 0, SWP_NOSIZE);
}

BOOL WINAPI DialogCallback(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static std::vector<sf::VideoMode> validModes;

	switch(msg)
	{
	case WM_INITDIALOG:
		CentralizeWindow(hDlg);
		for(unsigned int i = 0; i < sf::VideoMode::GetModesCount(); ++i)
		{
			sf::VideoMode mode(sf::VideoMode::GetMode(i));
			if(800 > mode.Width || 600 > mode.Height) continue;
			tstring desc = TEXT(" ") + boost::lexical_cast<tstring>(mode.Width) +
				TEXT("x") + boost::lexical_cast<tstring>(mode.Height) +
				TEXT(", ") + boost::lexical_cast<tstring>(mode.BitsPerPixel) + TEXT("bit");
			validModes.push_back(mode);
			ComboBox_AddString(GetDlgItem(hDlg, IDC_COMBO_MODE), desc.c_str());
		}
		ComboBox_SetCurSel(GetDlgItem(hDlg, IDC_COMBO_MODE), 0);
		return TRUE;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDOK:
			s_settings.video.videoMode = validModes[ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_COMBO_MODE))];
			s_settings.video.fullscreen = BST_CHECKED == IsDlgButtonChecked(hDlg, IDC_CHECK_FULLSCREEN);
			EndDialog(hDlg, 0);
			return TRUE;
		case IDCANCEL:
			EndDialog(hDlg, 1);
		default:
			return TRUE;
		};
	case WM_CLOSE:
		EndDialog(hDlg, 0);
		return TRUE;
	default:
		return FALSE;
	};
}

int ShowSettingsDialog(Settings& settings)
{
	int r = DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG_SETTINGS), NULL, DialogCallback);
	settings = s_settings;
	return r;
}