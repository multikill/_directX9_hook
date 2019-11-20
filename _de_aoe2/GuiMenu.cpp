#include <Windows.h>
#include "imgui.h"
#include <iostream>

void ShowGui()
{
	static bool openOverlay = true;
	if (GetAsyncKeyState(VK_INSERT) & 1) 
	{ 
		openOverlay = !openOverlay; 
	}


	ImGui::SetNextWindowBgAlpha(0.35f);
	if (openOverlay)
	{
		if (ImGui::Begin("Age of Empires 2 DE", &openOverlay, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav))
		{
			ImGui::Text("I am Text");
		}
		ImGui::End();
	}
}