// ImGui - standalone example application for DirectX 9
// If you are new to ImGui, see examples/README.txt and documentation at the top of imgui.cpp.

#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include <d3d9.h>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <tchar.h>
#include "fonts.h"


// Short word from IcePixel. I know this shit couldve been done easier and cleaner but it works so but I wouldnt mind any critisism.


static LPDIRECT3DDEVICE9        g_pd3dDevice = NULL;
static D3DPRESENT_PARAMETERS    g_d3dpp;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            ImGui_ImplDX9_InvalidateDeviceObjects();
            g_d3dpp.BackBufferWidth  = LOWORD(lParam);
            g_d3dpp.BackBufferHeight = HIWORD(lParam);
            HRESULT hr = g_pd3dDevice->Reset(&g_d3dpp);
            if (hr == D3DERR_INVALIDCALL)
                IM_ASSERT(0);
            ImGui_ImplDX9_CreateDeviceObjects();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

// Declearing Voids here for later
void DrawOne();
void DrawTwo();

int main(int, char**)
{
	// Wouldnt mess with this stuff

    // Create application window
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("Menu Creator"), NULL };
    RegisterClassEx(&wc);
    HWND hwnd = CreateWindow(_T("Menu Creator"), _T("Menu Creator"), WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, NULL, NULL, wc.hInstance, NULL);

    // Initialize Direct3D
    LPDIRECT3D9 pD3D;
    if ((pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
    {
        UnregisterClass(_T("Menu Creator"), wc.hInstance);
        return 0;
    }
    ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
    g_d3dpp.Windowed = TRUE;
    g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    g_d3dpp.EnableAutoDepthStencil = TRUE;
    g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE; // Present with vsync
    //g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; // Present without vsync, maximum unthrottled framerate

    // Create the D3DDevice
    if (pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0)
    {
        pD3D->Release();
        UnregisterClass(_T("Menu Creator"), wc.hInstance);
        return 0;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGuiStyle& style = ImGui::GetStyle();




	// Define fonts here!
	ImFont* font;

	// Change font here!
	font = io.Fonts->AddFontFromMemoryCompressedTTF(Ubuntu_compressed_data, Ubuntu_compressed_size, 14.f);

	// Change Style here!
	style.WindowPadding = ImVec2(15, 15);
	style.WindowRounding = 5.0f;
	style.WindowMinSize = ImVec2(32, 32);
	style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
	style.ChildRounding = 0.0f;
	style.FramePadding = ImVec2(5, 5);
	style.FrameRounding = 4.0f;
	style.ItemSpacing = ImVec2(12, 8);
	style.ItemInnerSpacing = ImVec2(8, 6);
	style.IndentSpacing = 25.0f;
	style.ScrollbarSize = 15.0f;
	style.ScrollbarRounding = 9.0f;
	style.GrabMinSize = 5.0f;
	style.GrabRounding = 3.0f;
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
	style.DisplayWindowPadding = ImVec2(22, 22);
	style.DisplaySafeAreaPadding = ImVec2(4, 4);
	style.AntiAliasedLines = true;
	style.AntiAliasedFill = true;
	style.CurveTessellationTol = 1.25f; 


	// Set Colors here!
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.1f, 0.1f, 0.1f, 0.95f);
	style.Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.90f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.70f, 0.70f, 0.70f, 0.40f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.95f, 1.00f, 0.30f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.30f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.00f, 0.95f, 1.00f, 0.30f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.01f, 0.59f, 0.62f, 0.77f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.01f, 0.59f, 0.62f, 0.77f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.01f, 0.59f, 0.62f, 0.77f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.02f, 0.63f, 0.66f, 0.90f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.13f, 0.18f, 0.22f, 0.60f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.20f, 0.70f, 0.75f, 0.30f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.40f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.20f, 0.70f, 0.75f, 0.30f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.99f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.20f, 0.70f, 0.75f, 1.00f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(1.00f, 1.00f, 1.00f, 0.30f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.20f, 0.70f, 0.75f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.00f, 0.56f, 0.57f, 0.61f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.21f, 0.57f, 0.57f, 0.61f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.00f, 0.56f, 0.57f, 0.61f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.01f, 0.59f, 0.62f, 0.77f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.21f, 0.58f, 0.60f, 0.77f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.01f, 0.59f, 0.62f, 0.77f);
	style.Colors[ImGuiCol_Separator] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
	style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.60f, 0.60f, 0.70f, 1.00f);
	style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.70f, 0.70f, 0.90f, 1.00f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.30f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.60f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.90f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.00f, 0.00f, 1.00f, 0.35f);
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);


    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX9_Init(g_pd3dDevice);

	// MenuTab Integer
	int MenuTab = 0;

	// Keeping this bool incase someone wants to use the demo Window
    bool show_demo_window = true;

	// Needs it further down
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    ShowWindow(hwnd, SW_SHOWDEFAULT);
    UpdateWindow(hwnd);
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            continue;
        }
        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        // Code below enables demo window if u need it
   /*     if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window); */

        {

			bool fill; // bool for filling ImGui::Begin
			ImVec2 mainWindowPos;
			ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiSetCond_Appearing);
			style.WindowPadding = ImVec2(8, 8);
			ImGui::SetNextWindowPosCenter(ImGuiSetCond_Appearing);
			ImGui::Begin("!s´window", &fill, ImVec2(828, 450), 0.98f, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar |  ImGuiWindowFlags_NoMove);
			{
				mainWindowPos = ImGui::GetWindowPos();

				if (ImGui::Button("Test", ImVec2(120, 60))) MenuTab = 0;
				ImGui::SameLine();
				if (ImGui::Button("Test2", ImVec2(120, 60))) MenuTab = 1;

				if (MenuTab == 0)
					DrawOne();
				if (MenuTab == 1)
					DrawTwo();
				
			}ImGui::End();
        }

        ImGui::EndFrame();

		// Mess around with this if u want but you dont need too
        g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, false);
        g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
        g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, false);
        D3DCOLOR clear_col_dx = D3DCOLOR_RGBA((int)(clear_color.x*255.0f), (int)(clear_color.y*255.0f), (int)(clear_color.z*255.0f), (int)(clear_color.w*255.0f));
        g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, clear_col_dx, 1.0f, 0);
        if (g_pd3dDevice->BeginScene() >= 0)
        {
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            g_pd3dDevice->EndScene();
        }
        HRESULT result = g_pd3dDevice->Present(NULL, NULL, NULL, NULL);

        if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
        {
            ImGui_ImplDX9_InvalidateDeviceObjects();
            g_pd3dDevice->Reset(&g_d3dpp);
            ImGui_ImplDX9_CreateDeviceObjects();
        }
    }

    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    if (g_pd3dDevice) g_pd3dDevice->Release();
    if (pD3D) pD3D->Release();
    DestroyWindow(hwnd);
    UnregisterClass(_T("ImGui Example"), wc.hInstance);

    return 0;
}

// Here are the voids were u can do all the things you want.

void DrawOne()
{

	ImGui::Text("I know this shit couldve been done cleaner and easier to use but it works\nmake the menu of your wish - Thanks for using this shit programm IcePixel");

}

void DrawTwo()
{
	bool fill2; // bool for checkbox fill

	ImGui::Text("Some Examples from my old Menu how to use it and how it looks.");

	ImGui::Checkbox("Friendly Fire", &fill2);
	ImGui::SameLine(180);
	ImGui::Checkbox("Legit AA", &fill2);
	ImGui::Checkbox("Silent Aim", &fill2);
	ImGui::SameLine(180);
	ImGui::Checkbox("Legit AA Anti Silent", &fill2);
	ImGui::Checkbox("Auto Wall", &fill2);
	ImGui::SameLine(180);
	ImGui::Checkbox("Backtrack", &fill2);
	ImGui::Checkbox("Check Smoke", &fill2);
	ImGui::SameLine(180);
	ImGui::Checkbox("Draw Backtrack Ticks", &fill2);
	ImGui::Checkbox("Anti Jump", &fill2);
	ImGui::SameLine(180);
	ImGui::PushItemWidth(155.f);
	ImGui::PopItemWidth();
	ImGui::Checkbox("Draw Fov", &fill2);
	ImGui::Checkbox("Draw Spot", &fill2);
}

