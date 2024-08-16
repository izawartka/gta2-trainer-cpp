#pragma once
#include <afxwin.h>
#include <afxext.h>

#define WM_CAMERA_MOVE_BTN (WM_USER + 1000)

class CameraMoveBtn : public CButton
{
public:

protected:
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

    DECLARE_MESSAGE_MAP()
};