#pragma once

#include <d3d11.h>

#include <imgui_impl_win32.h>
#include <imgui_impl_dx11.h>

namespace ImGuiRapper
{
	class ImGuiCtrl
	{
	public:
		static ImGuiCtrl& Instance()
		{
			static ImGuiCtrl instance;
			return instance;
		}

		void Initialize(HWND hWnd, ID3D11Device* device, ID3D11DeviceContext* dc);

		void Finalize();

		void NewFrame();

		void Render();

		LRESULT HandleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	private:
		ID3D11Device* device = nullptr;
		ID3D11DeviceContext* deviceContext = nullptr;
		HWND hWnd;

		ImGuiCtrl() = default;
		~ImGuiCtrl() = default;
	};
}