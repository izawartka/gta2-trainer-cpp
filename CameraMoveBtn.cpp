#include "pch.h"
#include "CameraMoveBtn.h"

BEGIN_MESSAGE_MAP(CameraMoveBtn, CButton)
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

void CameraMoveBtn::OnLButtonDown(UINT nFlags, CPoint point)
{
	CButton::OnLButtonDown(nFlags, point);

	GetParent()->SendMessage(WM_CAMERA_MOVE_BTN, GetDlgCtrlID(), TRUE);
}

void CameraMoveBtn::OnLButtonUp(UINT nFlags, CPoint point)
{
	CButton::OnLButtonUp(nFlags, point);

	GetParent()->SendMessage(WM_CAMERA_MOVE_BTN, GetDlgCtrlID(), FALSE);
}
