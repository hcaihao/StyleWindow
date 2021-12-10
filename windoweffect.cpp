#include "stdafx.h"
#include "windoweffect.h"

#include <dwmapi.h>

namespace WindowEffect
{
	void moveWindow(HWND hWnd)
	{
		ReleaseCapture();
		SendMessage(hWnd, WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
	}

	void addShadowEffect(HWND hWnd)
	{
		DWMNCRENDERINGPOLICY ncrp = DWMNCRP_ENABLED;
		::DwmSetWindowAttribute(hWnd, DWMWA_NCRENDERING_POLICY, &ncrp, sizeof(ncrp));

		MARGINS margins = { -1 };
		::DwmExtendFrameIntoClientArea(hWnd, &margins);
	}

	void removeShadowEffect(HWND hWnd)
	{
		DWMNCRENDERINGPOLICY ncrp = DWMNCRP_DISABLED;
		::DwmSetWindowAttribute(hWnd, DWMWA_NCRENDERING_POLICY, &ncrp, sizeof(ncrp));
	}

	void removeMenuShadowEffect(HWND hWnd)
	{
		DWORD style = GetClassLong(hWnd, GCL_STYLE);
		style &= ~0x00020000;  // CS_DROPSHADOW;
		SetClassLong(hWnd, GCL_STYLE, style);
	}

	void addWindowAnimation(HWND hWnd)
	{
		DWORD style = GetWindowLong(hWnd, GWL_STYLE);
		SetWindowLong(hWnd, GWL_STYLE, style
			| WS_MAXIMIZEBOX
			| WS_CAPTION
			| CS_DBLCLKS
			| WS_THICKFRAME
		);
	}
}