
#include<Windows.h>
#include<tchar.h>
#include"resource.h"

#define MAX_PASSWORD 50

/* 对话框消息处理函数声明 */
LRESULT CALLBACK DialogFunc(
	HWND hWnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam
);

/* 密码验证函数 */
void VerifyPassword(
	HWND hDlg
);

/* WinMain函数 */
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd
)
{
	MSG msg;
	HWND hWnd = CreateDialog( // 从资源中创建对话框
		hInstance,
		MAKEINTRESOURCE(IDD_DIALOG1),
		NULL,
		(DLGPROC)DialogFunc);
	ShowWindow(hWnd, SW_SHOWNORMAL); // 显示对话框
	while (GetMessage(&msg, NULL, 0, 0)) // 消息处理循环
	{
		if (!IsDialogMessage(hWnd, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return 0;
}


/* 窗口处理函数 */
LRESULT CALLBACK DialogFunc(
	HWND hWnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam
)
{
	switch (message)
	{
	case WM_COMMAND: // 命令消息
		switch (LOWORD(wParam)) // wParam的低位表示控件ID
		{
		case IDC_BUTTON1: // 验证按钮
			VerifyPassword(hWnd);
			break;
		}
		break;
	case WM_CLOSE: // 窗体关闭消息
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY: // 窗体销毁消息
		PostQuitMessage(0);
		break;
	}
	return FALSE;
}

/* 校验输入的密码 */
void VerifyPassword(
	HWND hDlg
)
{
	TCHAR lpString[MAX_PASSWORD] = TEXT("");
	TCHAR lpRightPassword[MAX_PASSWORD] = TEXT("abc123"); // 正确的密码

	GetDlgItemTextW(hDlg, IDC_EDIT_PASSWORD, lpString, MAX_PASSWORD); // 获取编辑框的值
	if (0 == _tcscmp( // 比较编辑框中的密码和正确密码
		lpString,
		lpRightPassword))
	{
		MessageBox(NULL, TEXT("恭喜你，密码正确！"), TEXT("信息"), MB_OK);
	}
	else
	{
		MessageBox(NULL, TEXT("密码错误，再加把劲！"), TEXT("信息"), MB_OK);
	}
}
