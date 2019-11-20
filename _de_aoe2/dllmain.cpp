// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <iostream>

#include "d3d9.h"
#include "d3dx9.h"

#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"

#include "DetourHook.hpp"
#include "json.hpp"
#include "GuiMenu.hpp"


const char* windowName = "Age of Empires II: Definitive Edition";

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

typedef HRESULT(__stdcall* f_EndScene)(IDirect3DDevice9* pDevice);
f_EndScene oEndScene;

typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);

DetourHook endsceneHook = DetourHook();

WNDPROC oWndProc;

HRESULT __stdcall Hooked_EndScene(IDirect3DDevice9* pDevice) // Our hooked endscene
{
	printf("Begin");
	static bool init = true;
	if (init)
	{
		init = false;
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();

		ImGui_ImplWin32_Init(FindWindowA(NULL, windowName));
		ImGui_ImplDX9_Init(pDevice);
	}


	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGuiIO& io = ImGui::GetIO();


	ShowGui();
	printf("AfterShow");

	ImGui::EndFrame();
	ImGui::Render();

	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	return oEndScene(pDevice); // Call original ensdcene so the game can draw
}


VOID WINAPI OnDllAttach(PVOID base)
{
#ifdef _DEBUG
	AllocConsole();
	freopen_s((FILE * *)stdin, "CONIN$", "r", stdin);
	freopen_s((FILE * *)stdout, "CONOUT$", "w", stdout);
	SetConsoleTitleA("Age of Empires 2 DE");
#endif
}

VOID WINAPI OnDllDetach()
{
#ifdef _DEBUG
	fclose((FILE*)stdin);
	fclose((FILE*)stdout);

	HWND hw_ConsoleHwnd = GetConsoleWindow();
	FreeConsole();
	PostMessageW(hw_ConsoleHwnd, WM_CLOSE, 0, 0);
#endif
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
	{
		return true;
	}
	
	//Input::Get()->ProcessMessage(uMsg, wParam, lParam);

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}


DWORD WINAPI MainThread(LPVOID param)
{
	OnDllAttach(param);
	HWND  window = FindWindowA(NULL, windowName);

	oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);


	//Create a D3D9Device so we can hook its VFTABLE
	IDirect3D9* pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (!pD3D)
		return false;

	D3DPRESENT_PARAMETERS d3dpp{ 0 };
	d3dpp.hDeviceWindow = window, d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD, d3dpp.Windowed = TRUE;

	IDirect3DDevice9* Device = nullptr;
	if (FAILED(pD3D->CreateDevice(0, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &Device)))
	{
		pD3D->Release();
		return false;
	}

	void** pVTable = *reinterpret_cast<void***>(Device);

	if (Device)
		Device->Release(), Device = nullptr;

	printf("0x%X\n", pVTable);

	oEndScene = (f_EndScene)endsceneHook.Hook((PBYTE)pVTable[42], (PBYTE)Hooked_EndScene, 7);

	printf("0x%X\n", oEndScene);

	while (!(GetAsyncKeyState(VK_XBUTTON1) & 0x8000))
	{
		Sleep(1);
	}

	//Restore hooks and end thread
	(WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)oWndProc);
	endsceneHook.Unhook();
	
	FreeLibraryAndExitThread((HMODULE)param, 0);
	return false;
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
	{
		HANDLE hThread = nullptr;
		hThread = CreateThread(nullptr, 0, MainThread, hModule, 0, nullptr);
		if (hThread)
		{
			CloseHandle(hThread);
		}
	}
		break;
	case DLL_THREAD_ATTACH: 
		break;
	case DLL_THREAD_DETACH: 
		break;
    case DLL_PROCESS_DETACH:
		Sleep(1000);
		OnDllDetach();
        break;
    }
    return TRUE;
}

