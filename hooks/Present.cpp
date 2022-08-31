#include <pch.h>
#include <base.h>
#include "../configs/Configs.h"

extern Config cfg;

ImFont* msyhbd = nullptr;


HRESULT PRESENT_CALL Base::Hooks::Present(IDXGISwapChain* thisptr, UINT SyncInterval, UINT Flags)
{
	if (!Data::InitImGui)
	{
		Data::pSwapChain = thisptr;
		if (SUCCEEDED(Data::pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&Data::pDxDevice11)))
		{
			Data::pDxDevice11->GetImmediateContext(&Data::pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			Data::pSwapChain->GetDesc(&sd);
			Data::hWindow = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			Data::pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			Data::pDxDevice11->CreateRenderTargetView(pBackBuffer, NULL, &Data::pMainRenderTargetView);
			pBackBuffer->Release();
			Data::oWndProc = (WNDPROC)SetWindowLongPtr(Data::hWindow, GWLP_WNDPROC, (LONG_PTR)WndProc);
		}
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();

		static constexpr ImWchar rangesTX[]{ 0x0020, 0xFFFF, 0 };
		msyhbd = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\msyhbd.ttc", 16.0f, NULL, rangesTX);
		io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;

		ImGui_ImplWin32_Init(Data::hWindow);
		ImGui_ImplDX11_Init(Data::pDxDevice11, Data::pContext);
		Data::InitImGui = true;
	}

	if (!Data::InitImGui)
		return Data::oPresent(thisptr, SyncInterval, Flags);

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	//这里开始写功能

	ImGui::ShowDemoWindow();

	ImGui::EndFrame();
	ImGui::Render();

	Data::pContext->OMSetRenderTargets(1, &Data::pMainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	return Data::oPresent(thisptr, SyncInterval, Flags);
}
