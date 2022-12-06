#include "overlay.h"
#include "memory.h"
#include "utility.h"

int realkey;
int keystatus;
bool GetKey(int key)
{
	realkey = key;
	return true;
}
void ChangeKey(void* blank)
{
	keystatus = 1;
	while (true)
	{
		for (int i = 0; i < 0x87; i++)
		{
			if (GetKeyState(i) & 0x8000)
			{
				settings::aimkey = i;
				keystatus = 0;
				return;
			}
		}
	}
}
static const char* keyNames[] =
{
	"",
	"Left Mouse",
	"Right Mouse",
	"Cancel",
	"Middle Mouse",
	"Mouse 5",
	"Mouse 4",
	"",
	"Backspace",
	"Tab",
	"",
	"",
	"Clear",
	"Enter",
	"",
	"",
	"Shift",
	"Control",
	"Alt",
	"Pause",
	"Caps",
	"",
	"",
	"",
	"",
	"",
	"",
	"Escape",
	"",
	"",
	"",
	"",
	"Space",
	"Page Up",
	"Page Down",
	"End",
	"Home",
	"Left",
	"Up",
	"Right",
	"Down",
	"",
	"",
	"",
	"Print",
	"Insert",
	"Delete",
	"",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"",
	"",
	"",
	"",
	"",
	"Numpad 0",
	"Numpad 1",
	"Numpad 2",
	"Numpad 3",
	"Numpad 4",
	"Numpad 5",
	"Numpad 6",
	"Numpad 7",
	"Numpad 8",
	"Numpad 9",
	"Multiply",
	"Add",
	"",
	"Subtract",
	"Decimal",
	"Divide",
	"F1",
	"F2",
	"F3",
	"F4",
	"F5",
	"F6",
	"F7",
	"F8",
	"F9",
	"F10",
	"F11",
	"F12",
};
static bool Items_ArrayGetter(void* data, int idx, const char** out_text)
{
	const char* const* items = (const char* const*)data;
	if (out_text)
		*out_text = items[idx];
	return true;
}
void HotkeyButton(int aimkey, void* changekey, int status)
{
	const char* preview_value = NULL;
	if (aimkey >= 0 && aimkey < IM_ARRAYSIZE(keyNames))
		Items_ArrayGetter(keyNames, aimkey, &preview_value);

	std::string aimkeys;
	if (preview_value == NULL)
		aimkeys = skCrypt("Select Key");
	else
		aimkeys = preview_value;

	if (status == 1)
	{
		aimkeys = skCrypt("Press key to bind");
	}
	if (ImGui::Button(aimkeys.c_str(), ImVec2(125, 20)))
	{
		if (status == 0)
		{
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)changekey, nullptr, 0, nullptr);
		}
	}
}
#include <windows.h>
#include <iostream>
void make_hack()
{
	std::vector<EnemyPtr> actor = enemy_array;
	if (actor.empty()) {
		return;
	}
	for (int i = 0; i < actor.size(); i++)
	{

		EnemyPtr enemy = actor[i];
		Vector3 vBaseBone = SDK::GetBone(enemy.mesh_ptr, 0);
		Vector3 vBaseBoneOut = SDK::ProjectWorldToScreen(vBaseBone);
		Vector3 vBaseBoneOut2 = SDK::ProjectWorldToScreen(Vector3(vBaseBone.x, vBaseBone.y, vBaseBone.z - 15));
		Vector3 vHeadBone = SDK::GetBone(enemy.mesh_ptr, 8);
		Vector3 vHeadBoneOut = SDK::ProjectWorldToScreen(Vector3(vHeadBone.x, vHeadBone.y, vHeadBone.z));
		Vector3 vHeadBoneOut2 = SDK::ProjectWorldToScreen(Vector3(vHeadBone.x, vHeadBone.y, vHeadBone.z));
		auto LocalRootComponent = driver.read<uintptr_t>(glocalpawn + ROOT_COMPONENT);
		auto EntityRootComponent = driver.read<uintptr_t>(enemy.actor_ptr + ROOT_COMPONENT);
		auto LocalRelativeLocation = driver.read<Vector3>(LocalRootComponent + ROOT_POS);
		auto ActorRelativeLocation = driver.read<Vector3>(enemy.root_component_ptr + ROOT_POS);
		auto distance2 = LocalRelativeLocation.Distance(ActorRelativeLocation);
		auto distance = distance2 / 5;
		float BoxHeight = abs(vHeadBoneOut.y - vBaseBoneOut.y);
		float BoxWidth = BoxHeight * 0.55;
		auto IsVisible = SDK::IsVisible(enemy.mesh_ptr);
		bool IsDormant = driver.read<bool>(enemy.actor_ptr + DORMANT);
		if (settings::Dormant)
		{
			if (!IsDormant)
				continue;
		}
		float Health = driver.read<float>(enemy.damage_handler_ptr + HEALTH);
		auto BoneCount = enemy.bone_count;
		int head_x = vHeadBoneOut.x;
		int head_y = vHeadBoneOut.y;
		int start_x = head_x - 35 / distance;
		int start_y = head_y - 15 / distance;
		int start_x2 = head_x - 35;
		int start_y2 = head_y - 15;
		int hp_x = head_x + 10 / distance;
		int hp_y = head_y + -40 / distance;
		int dis_x = head_x - 50 / distance;
		int dis_y = head_y + -40 / distance;
		int end_x = head_x + 35 / distance;
		int end_y = head_y + 155 / distance;

		Vector3 viewrot = driver.read<Vector3>(EntityRootComponent + ROOT_ROT);
		Vector3 conv_angle = viewrot;

		Vector3 head_bone = SDK::GetBone(enemy.mesh_ptr, 8);

		Vector3 output_angle;
		SDK::angle_vectors(conv_angle, &output_angle);

		output_angle.x *= 125;
		output_angle.y *= 125;
		output_angle.z *= 125;

		Vector3 end_angle = head_bone + output_angle;

		Vector3 head_out = SDK::ProjectWorldToScreen(head_bone);
		Vector3 end_out = SDK::ProjectWorldToScreen(end_angle);

		if (Health <= 0) continue;
		if (distance < 200)
		{
			if (settings::viewrotation)
			{	
				DrawLine(ImVec2(head_out.x, head_out.y), ImVec2(end_out.x, end_out.y), ImGui::ColorConvertFloat4ToU32(ImVec4(255, 255, 255, 255)), 1.5f);
			}
			if (settings::bone_esp)
			{
				SDK::DrawBones(enemy);
			}
			if (settings::headcircle)
			{
				ImGui::GetOverlayDrawList()->AddCircle(ImVec2(vHeadBoneOut.x, vHeadBoneOut.y), 5, ImGui::ColorConvertFloat4ToU32(ImVec4(settings::headcircle_color[0], settings::headcircle_color[1], settings::headcircle_color[2], settings::headcircle_color[3])), 12, 2);
			}
			if (settings::radar)
			{
				SDK::pRadar.x = (GetWindowSize().x / 2) + 680;
				SDK::pRadar.y = GetWindowSize().x / 2 - GetWindowSize().y / 2 - 410;
				DrawRect(SDK::pRadar.x, SDK::pRadar.y, 270, 270, &Col.black, 1);
				DrawBorder(SDK::pRadar.x, SDK::pRadar.y, 270, 270, 1, &Col.SilverWhite);
				auto radar_posX = SDK::pRadar.x + 135;
				auto radar_posY = SDK::pRadar.y + 135;
				DrawLine3(radar_posX, radar_posY, radar_posX, radar_posY + 135, &Col.SilverWhite, 1);
				DrawLine3(radar_posX, radar_posY, radar_posX, radar_posY - 135, &Col.SilverWhite, 1);
				DrawLine3(radar_posX, radar_posY, radar_posX + 135, radar_posY, &Col.SilverWhite, 1);
				DrawLine3(radar_posX, radar_posY, radar_posX - 135, radar_posY, &Col.SilverWhite, 1);
				SDK::DrawCircleFilled2(radar_posX - 0.5f, radar_posY - 0.5f, 3, &Col.yellow);
				FVector pos = driver.read<FVector>(enemy.root_component_ptr + ROOT_POS);
				SDK::DrawRadar(pos);
			}
			if (settings::glow)
			{
				driver.write<float>(enemy.actor_ptr + 0x6b8, 10000);
			}
			if (settings::box_esp)
			{
				if (settings::box_type == 0)
				{
					DrawCorneredBox(vBaseBoneOut2.x - BoxWidth / 2 + 1, vHeadBoneOut2.y - 1, BoxWidth - 1, BoxHeight, ImGui::ColorConvertFloat4ToU32(ImVec4(96, 96, 96, 255)), 1);
					DrawCorneredBox(vBaseBoneOut2.x - BoxWidth / 2 + 1, vHeadBoneOut2.y, BoxWidth, BoxHeight, ImGui::ColorConvertFloat4ToU32(ImVec4(settings::box_color[0], settings::box_color[1], settings::box_color[2], settings::box_color[3])), 1);
					DrawCorneredBox(vBaseBoneOut2.x - BoxWidth / 2 + 1, vHeadBoneOut2.y + 1, BoxWidth + 1, BoxHeight, ImGui::ColorConvertFloat4ToU32(ImVec4(96, 96, 96, 255)), 1);

					//DrawFilledRect((vBaseBoneOut2.x - BoxWidth / 2), vHeadBoneOut2.y, BoxWidth, BoxHeight, &Col.black_);
				}
				if (settings::box_type == 1)
				{
					//DrawNormalBox(vBaseBoneOut2.x - (BoxWidth / 2), vHeadBoneOut2.y, BoxWidth, BoxHeight, 1, ImGui::ColorConvertFloat4ToU32(ImVec4(settings::box_color[0], settings::box_color[1], settings::box_color[2], settings::box_color[3])));
					//DrawFilledRect((vBaseBoneOut2.x - BoxWidth / 2), vHeadBoneOut2.y, BoxWidth, BoxHeight, &Col.black_);
					DrawRectImGui((vBaseBoneOut2.x - BoxWidth / 2) - (BoxWidth / 50) - 1, vHeadBoneOut2.y - 1, BoxWidth + 2, BoxHeight + 2, ImVec4(0, 0, 0, 255.f), 1.3f);
					DrawRectImGui((vBaseBoneOut2.x - BoxWidth / 2) - (BoxWidth / 50), vHeadBoneOut2.y, BoxWidth, BoxHeight, ImVec4(255, 255, 255, 255.f), 1.f);
					DrawRectImGui((vBaseBoneOut2.x - BoxWidth / 2) - (BoxWidth / 50) + 1, vHeadBoneOut2.y + 1, BoxWidth - 2, BoxHeight - 2, ImVec4(0, 0, 0, 255.f), 1.3f);
				}
				if (settings::box_type == 2)
				{
					Vector3 bottom1 = SDK::ProjectWorldToScreen(Vector3(vBaseBone.x + 40, vBaseBone.y - 40, vBaseBone.z));
					Vector3 bottom2 = SDK::ProjectWorldToScreen(Vector3(vBaseBone.x - 40, vBaseBone.y - 40, vBaseBone.z));
					Vector3 bottom3 = SDK::ProjectWorldToScreen(Vector3(vBaseBone.x - 40, vBaseBone.y + 40, vBaseBone.z));
					Vector3 bottom4 = SDK::ProjectWorldToScreen(Vector3(vBaseBone.x + 40, vBaseBone.y + 40, vBaseBone.z));

					Vector3 top1 = SDK::ProjectWorldToScreen(Vector3(vHeadBone.x + 40, vHeadBone.y - 40, vHeadBone.z + 15));
					Vector3 top2 = SDK::ProjectWorldToScreen(Vector3(vHeadBone.x - 40, vHeadBone.y - 40, vHeadBone.z + 15));
					Vector3 top3 = SDK::ProjectWorldToScreen(Vector3(vHeadBone.x - 40, vHeadBone.y + 40, vHeadBone.z + 15));
					Vector3 top4 = SDK::ProjectWorldToScreen(Vector3(vHeadBone.x + 40, vHeadBone.y + 40, vHeadBone.z + 15));

					ImGui::GetOverlayDrawList()->AddLine(ImVec2(bottom1.x, bottom1.y), ImVec2(top1.x, top1.y), ImGui::ColorConvertFloat4ToU32(ImVec4(settings::box_color[0], settings::box_color[1], settings::box_color[2], settings::box_color[3])), 0.1f);
					ImGui::GetOverlayDrawList()->AddLine(ImVec2(bottom2.x, bottom2.y), ImVec2(top2.x, top2.y), ImGui::ColorConvertFloat4ToU32(ImVec4(settings::box_color[0], settings::box_color[1], settings::box_color[2], settings::box_color[3])), 0.1f);
					ImGui::GetOverlayDrawList()->AddLine(ImVec2(bottom3.x, bottom3.y), ImVec2(top3.x, top3.y), ImGui::ColorConvertFloat4ToU32(ImVec4(settings::box_color[0], settings::box_color[1], settings::box_color[2], settings::box_color[3])), 0.1f);
					ImGui::GetOverlayDrawList()->AddLine(ImVec2(bottom4.x, bottom4.y), ImVec2(top4.x, top4.y), ImGui::ColorConvertFloat4ToU32(ImVec4(settings::box_color[0], settings::box_color[1], settings::box_color[2], settings::box_color[3])), 0.1f);

					ImGui::GetOverlayDrawList()->AddLine(ImVec2(bottom1.x, bottom1.y), ImVec2(bottom2.x, bottom2.y), ImGui::ColorConvertFloat4ToU32(ImVec4(settings::box_color[0], settings::box_color[1], settings::box_color[2], settings::box_color[3])), 0.1f);
					ImGui::GetOverlayDrawList()->AddLine(ImVec2(bottom2.x, bottom2.y), ImVec2(bottom3.x, bottom3.y), ImGui::ColorConvertFloat4ToU32(ImVec4(settings::box_color[0], settings::box_color[1], settings::box_color[2], settings::box_color[3])), 0.1f);
					ImGui::GetOverlayDrawList()->AddLine(ImVec2(bottom3.x, bottom3.y), ImVec2(bottom4.x, bottom4.y), ImGui::ColorConvertFloat4ToU32(ImVec4(settings::box_color[0], settings::box_color[1], settings::box_color[2], settings::box_color[3])), 0.1f);
					ImGui::GetOverlayDrawList()->AddLine(ImVec2(bottom4.x, bottom4.y), ImVec2(bottom1.x, bottom1.y), ImGui::ColorConvertFloat4ToU32(ImVec4(settings::box_color[0], settings::box_color[1], settings::box_color[2], settings::box_color[3])), 0.1f);

					ImGui::GetOverlayDrawList()->AddLine(ImVec2(top1.x, top1.y), ImVec2(top2.x, top2.y), ImGui::ColorConvertFloat4ToU32(ImVec4(settings::box_color[0], settings::box_color[1], settings::box_color[2], settings::box_color[3])), 0.1f);
					ImGui::GetOverlayDrawList()->AddLine(ImVec2(top2.x, top2.y), ImVec2(top3.x, top3.y), ImGui::ColorConvertFloat4ToU32(ImVec4(settings::box_color[0], settings::box_color[1], settings::box_color[2], settings::box_color[3])), 0.1f);
					ImGui::GetOverlayDrawList()->AddLine(ImVec2(top3.x, top3.y), ImVec2(top4.x, top4.y), ImGui::ColorConvertFloat4ToU32(ImVec4(settings::box_color[0], settings::box_color[1], settings::box_color[2], settings::box_color[3])), 0.1f);
					ImGui::GetOverlayDrawList()->AddLine(ImVec2(top4.x, top4.y), ImVec2(top1.x, top1.y), ImGui::ColorConvertFloat4ToU32(ImVec4(settings::box_color[0], settings::box_color[1], settings::box_color[2], settings::box_color[3])), 0.1f);
				}
			}	
			if (settings::snapline)
			{
				if (settings::line_type == 0)
				{
					DrawLine(ImVec2(GetWindowSize().x / 2, GetWindowSize().y), ImVec2(vBaseBoneOut.x, vBaseBoneOut.y), ImGui::ColorConvertFloat4ToU32(ImColor(255, 255, 255)), 1.f); // ASAGIDAN
				}
				if (settings::line_type == 1)
				{
					DrawLine(ImVec2(GetWindowSize().x / 2, GetWindowSize().y - GetWindowSize().y), ImVec2(vBaseBoneOut.x, vBaseBoneOut.y), ImGui::ColorConvertFloat4ToU32(ImColor(255, 255, 255)), 1.f); // ASAGIDAN
				}
				if (settings::line_type == 2)
				{
					DrawLine(ImVec2(GetWindowSize().x / 2, GetWindowSize().y / 2), ImVec2(vBaseBoneOut.x, vBaseBoneOut.y), ImGui::ColorConvertFloat4ToU32(ImColor(255, 255, 255)), 1.f); // ASAGIDAN
				}
			}
			if (settings::distance)
			{
				char dist[64];
				sprintf_s(dist, skCrypt("[%.fm]"), distance);
				RGBA col = { settings::distance_color[0], settings::distance_color[1], settings::distance_color[2], settings::distance_color[3] };
				DrawString(15, vBaseBoneOut.x + 1, (vBaseBoneOut.y), &Col.SilverWhite, true, false, dist);
			}
			if (settings::healthbar)
			{
				DrawHealthBarr(Health, vHeadBoneOut2, vBaseBoneOut);
				//DrawLeftProgressBar(vBaseBoneOut2.x, vHeadBoneOut2.y, BoxWidth, BoxHeight, 4, Health);
			}
		}
	}
}

static int MenuSayfasi = 1;
static int widthh = 580;
static int heightt = 340;
ImColor cRainbow;
int tab = 1;
void draw_menu()
{
	auto s = ImVec2{}, p = ImVec2{}, gs = ImVec2{ 620, 485 };
	ImGui::SetNextWindowSize(ImVec2(gs));
	ImGui::SetNextWindowBgAlpha(1.0f);
	ImGui::Begin(skCrypt("ALIEN CHEATS - (ver. 0.0.2)"), NULL, ImGuiWindowFlags_::ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_::ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar);
	{

		ImGui::SetCursorPosX(121);
		s = ImVec2(ImGui::GetWindowSize().x - ImGui::GetStyle().WindowPadding.x * 2, ImGui::GetWindowSize().y - ImGui::GetStyle().WindowPadding.y * 2); p = ImVec2(ImGui::GetWindowPos().x + ImGui::GetStyle().WindowPadding.x, ImGui::GetWindowPos().y + ImGui::GetStyle().WindowPadding.y); auto draw = ImGui::GetWindowDrawList();
		draw->AddRectFilled(p, ImVec2(p.x + s.x, p.y + s.y), ImColor(15, 17, 19), 5);
		draw->AddRectFilled(ImVec2(p.x, p.y + 40), ImVec2(p.x + s.x, p.y + s.y), ImColor(18, 20, 21), 5, ImDrawCornerFlags_Bot);

		ImGui::PushFont(icons);
		auto logo_size = ImGui::CalcTextSize(skCrypt("A"));
		draw->AddText(ImVec2(p.x + 28 - logo_size.x / 2, p.y + 29 - (logo_size.y / 2) + 4), cRainbow, skCrypt("A"));
		ImGui::PopFont();

		ImGui::PushFont(main_font2);
		auto logo_size2 = ImGui::CalcTextSize(skCrypt("A"));
		draw->AddText(ImVec2(p.x + 42 - logo_size2.x / 2, p.y + 29 - logo_size2.y), cRainbow, skCrypt("AlienCheats"));
		ImGui::PopFont();
		ImGui::PushFont(main_font);
		draw->AddText(ImVec2(p.x + 42 - logo_size2.x / 2, p.y + 40 - logo_size2.y), cRainbow, "(VALORANT PRIV.)");
		ImGui::PopFont();

		ImGui::PushFont(main_font);
		ImGui::BeginGroup();
		ImGui::SameLine(110);
		if (ImGui::tab(skCrypt("AIMBOT"), tab == 1))tab = 1; ImGui::SameLine();
		if (ImGui::tab(skCrypt("Visuals"), tab == 2))tab = 2;
		ImGui::EndGroup();
		ImGui::PopFont();

		if (tab == 1)
		{
			ImGui::PushFont(main_font);
			{//left upper
				ImGui::SetCursorPosY(50);
				ImGui::BeginGroup();
				ImGui::SetCursorPosX(15);
				ImGui::MenuChild(skCrypt("Aimbot"), ImVec2(285, 415), false);
				{
					ImGui::Checkbox(skCrypt("Aimbot"), &settings::aimbot); ImGui::Text(skCrypt("")); ImGui::SameLine(8);
					HotkeyButton(settings::aimkey, ChangeKey, keystatus); ImGui::SameLine(); ImGui::Text(skCrypt("Aimbot Key"));
					ImGui::SliderFloat(skCrypt("Fov"), &settings::fov, 1, 360);
					ImGui::SliderFloat(skCrypt("Smooth"), &settings::smooth, 1, 30);
					ImGui::Checkbox(skCrypt("RCS"), &settings::rcs); ImGui::Text(skCrypt("")); ImGui::SameLine(8);
					ImGui::Combo(skCrypt("Hitbox"), &settings::hitbox, settings::hitbox2, IM_ARRAYSIZE(settings::hitbox2));
					ImGui::Checkbox(skCrypt("Visible Check"), &settings::visiblecheck);
					ImGui::Checkbox(skCrypt("Team Check"), &settings::teamcheck);
				}
				ImGui::EndChild();
				ImGui::EndGroup();
			}
			{//right
				ImGui::SetCursorPosY(50);
				ImGui::BeginGroup();
				ImGui::SetCursorPosX(320);
				ImGui::MenuChild(skCrypt(" "), ImVec2(285, 415), false);
				{

				}
				ImGui::EndChild();
				ImGui::EndGroup();
				ImGui::PopFont();
			}
		}
		if (tab == 2)
		{
			ImGui::PushFont(main_font);
			{//left upper
				ImGui::SetCursorPosY(50);
				ImGui::BeginGroup();
				ImGui::SetCursorPosX(15);
				ImGui::MenuChild(skCrypt("ESP"), ImVec2(285, 415), false);
				{
					ImGui::Checkbox(skCrypt("Enable ESP"), &settings::esp_enabled);
					ImGui::Checkbox(skCrypt("Bone ESP"), &settings::bone_esp);
					ImGui::Checkbox(skCrypt("Head ESP"), &settings::headcircle);
					ImGui::Checkbox(skCrypt("View Rotation"), &settings::viewrotation);
					ImGui::Checkbox(skCrypt("Box ESP"), &settings::box_esp); ImGui::Text(skCrypt("")); ImGui::SameLine(8);
					ImGui::Combo(skCrypt("Box Type"), &settings::box_type, settings::box, IM_ARRAYSIZE(settings::box));
					ImGui::Checkbox(skCrypt("Snapline ESP"), &settings::snapline); ImGui::Text(skCrypt("")); ImGui::SameLine(8);
					ImGui::Combo(skCrypt("Snapline Type"), &settings::line_type, settings::line, IM_ARRAYSIZE(settings::line));
					ImGui::Checkbox(skCrypt("Healthbar ESP"), &settings::healthbar);
					ImGui::Checkbox(skCrypt("Distance ESP"), &settings::distance);
					ImGui::Checkbox(skCrypt("Dormant Check"), &settings::Dormant);
				}
				ImGui::EndChild();
				ImGui::EndGroup();
			}
			{//right
				ImGui::SetCursorPosY(50);
				ImGui::BeginGroup();
				ImGui::SetCursorPosX(320);
				ImGui::MenuChild(skCrypt("VISUALS"), ImVec2(285, 415), false);
				{
					ImGui::Checkbox(skCrypt("Radar"), &settings::radar);
					ImGui::Checkbox(skCrypt("Glow"), &settings::glow);
				}
				ImGui::EndChild();
				ImGui::EndGroup();
			}
			ImGui::PopFont();
		}
	}
	ImGui::End();
	/*Style();

	ImGui::SetNextWindowSize(ImVec2(widthh, heightt));
	ImGui::Begin(skCrypt("REYMEN CHEATS"));

	ImGui::SetCursorPos(ImVec2(55, 22));
	ImGui::BeginChild(skCrypt("Sayfa 0"), ImVec2(470.0f, 30.0f));
	ImGui::SetCursorPos({ 30.f,5.f });
	if (ImGui::Button(skCrypt("MAIN"), { 125.f,20.f }))
	{
		MenuSayfasi = 1;
	}
	ImGui::SetCursorPos({ 170.f,5.f });
	if (ImGui::Button(skCrypt("MISC"), { 125.f,20.f }))
	{
		MenuSayfasi = 2;
	}
	ImGui::SetCursorPos({ 310.f,5.f });
	if (ImGui::Button(skCrypt("ESP"), { 125.f,20.f }))
	{
		MenuSayfasi = 3;
	}
	ImGui::EndChild();

	if (MenuSayfasi == 1)
	{
		if (ImGui::CollapsingHeader(skCrypt("Aim")))
		{
			ImGui::Checkbox(skCrypt("Aimbot"), &settings::aimbot); ImGui::SameLine();
			HotkeyButton(settings::aimkey, ChangeKey, keystatus); ImGui::SameLine(); ImGui::Text("Aimbot Key");
			if (settings::aimbot)
			{
				ImGui::SliderFloat(skCrypt("Fov"), &settings::fov, 1, 360);
				ImGui::SliderFloat(skCrypt("Smooth"), &settings::smooth, 1, 30);
				ImGui::Checkbox(skCrypt("RCS"), &settings::rcs);
				ImGui::Combo(skCrypt("Hitbox"), &settings::hitbox, settings::hitbox2, IM_ARRAYSIZE(settings::hitbox2));
			}
			ImGui::Checkbox(skCrypt("Visible Check"), &settings::visiblecheck);
			ImGui::Checkbox(skCrypt("Team Check"), &settings::teamcheck);
		}
	}
	if (MenuSayfasi == 2)
	{
		if (ImGui::CollapsingHeader(skCrypt("Misc")))
		{
			ImGui::Checkbox(skCrypt("Radar"), &settings::radar);
			ImGui::Checkbox(skCrypt("Glow"), &settings::glow);
		}
	}
	if (MenuSayfasi == 3)
	{
		if (ImGui::CollapsingHeader(skCrypt("ESP")))
		{
			ImGui::Checkbox(skCrypt("Enable ESP"), &settings::esp_enabled);
			ImGui::Checkbox(skCrypt("Bone ESP"), &settings::bone_esp);
			ImGui::Checkbox(skCrypt("Head ESP"), &settings::headcircle);
			ImGui::Checkbox(skCrypt("View Rotation"), &settings::viewrotation);
			ImGui::Checkbox(skCrypt("Box ESP"), &settings::box_esp);
			ImGui::Combo(skCrypt("Box Type"), &settings::box_type, settings::box, IM_ARRAYSIZE(settings::box));
			ImGui::Checkbox(skCrypt("Snapline ESP"), &settings::snapline);
			ImGui::Combo(skCrypt("Snapline Type"), &settings::line_type, settings::line, IM_ARRAYSIZE(settings::line));
			ImGui::Checkbox(skCrypt("Healthbar ESP"), &settings::healthbar);
			ImGui::Checkbox(skCrypt("Distance ESP"), &settings::distance);
			ImGui::Checkbox(skCrypt("Dormant Check"), &settings::Dormant);
		}
	}
	ImGui::End();*/
}

void render()
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImVec2 curPos = ImGui::GetCursorPos();
	ImVec2 curWindowPos = ImGui::GetWindowPos();
	curPos.x += curWindowPos.x;
	curPos.y += curWindowPos.y;
	static float flRainbow;
	float flSpeed = 0.0025f;
	flRainbow += flSpeed;
	if (flRainbow > 1.f) flRainbow = 0.f;
	for (int i = 0; i < 485; i++)
	{
		float hue = (1.f / (float)485) * i;
		hue -= flRainbow;
		if (hue < 0.f) hue += 1.f;

		cRainbow = ImColor::HSV(hue, 1.f, 1.f);
		//ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(curPos.x + i, 10), ImVec2(curPos.x + 485, curPos.y - 3), cRainbow);
	}

	if (GetAsyncKeyState(VK_INSERT) & 1) { showmenu = !showmenu; }
	make_hack();
	if (showmenu) { draw_menu(); }

	if (settings::aimbot)
	{
		ImGui::GetOverlayDrawList()->AddCircle(ImVec2(ScreenCenterX, ScreenCenterY), settings::fov, IM_COL32_WHITE, 10000, 1);
	}

	if (GetAsyncKeyState(VK_END) & 1) { exit(0); }

	ImGui::EndFrame();
	p_Device->SetRenderState(D3DRS_ZENABLE, false);
	p_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	p_Device->SetRenderState(D3DRS_SCISSORTESTENABLE, false);
	p_Device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);

	if (p_Device->BeginScene() >= 0)
	{
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		p_Device->EndScene();
	}

	HRESULT result = p_Device->Present(NULL, NULL, NULL, NULL);

	if (result == D3DERR_DEVICELOST && p_Device->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
	{
		ImGui_ImplDX9_InvalidateDeviceObjects();
		p_Device->Reset(&d3dpp);
		ImGui_ImplDX9_CreateDeviceObjects();
	}
}

void aimbot()
{
	try
	{
		if (settings::aimbot)
		{
			int hitboxid;
			float aimfov = settings::fov;
			int dwIndex = SDK::ActorLoop(aimfov);
			if (dwIndex < 0) return;
			if (settings::hitbox == 0)
				hitboxid = 8;
			else if (settings::hitbox == 1)
				hitboxid = 7;
			else if (settings::hitbox == 2)
				hitboxid = 5;
			if (GetAsyncKeyState(settings::aimkey))
			{
				EnemyPtr enemy = enemy_array[dwIndex];
				FMinimalViewInfo2 camera = driver.read<FMinimalViewInfo2>(gcameramanager + 0x1FE0 + 0x10);
				FVector neck_position = SDK::GetBone2(enemy.mesh_ptr, hitboxid);
				FVector root_position = driver.read<FVector>(enemy.root_component_ptr + ROOT_POS);
				if (neck_position.z <= root_position.z)
				{
					return;
				}
				FVector localView = driver.read<FVector>(glocalplayercontroller + CONTROL_ROT);
				FVector vecCaclculatedAngles = SDK::fhgfsdhkfshdghfsd205(camera.Location, neck_position);
				FVector angleEx = SDK::CaadadalcAngle(camera.Location, neck_position);
				FVector fin = FVector(vecCaclculatedAngles.y, angleEx.y, 0);
				if (settings::Dormant)
				{
					float Health = driver.read<float>(enemy.damage_handler_ptr + HEALTH);
					if (Health <= 0)
						return;
					bool IsDormant = driver.read<bool>(enemy.actor_ptr + DORMANT);
					if (!IsDormant)
						return;
				}
				if (settings::rcs) {
					FVector delta = fin - localView;
					FVector TargetAngle = localView + delta;
					SDK::Clamp(TargetAngle);
					SDK::RCS(TargetAngle, camera.Rotation, settings::smooth);
					float temp = SDK::GetFov(camera.Rotation, vecCaclculatedAngles);
				}
				else {
					FVector delta = fin - localView;
					SDK::NormalizeAngles(delta);
					FVector TargetAngle = localView + (delta / settings::smooth);
					SDK::NormalizeAngles(TargetAngle);
					driver.write<FVector>(glocalplayercontroller + CONTROL_ROT, TargetAngle);
					float temp = SDK::GetFov(camera.Rotation, vecCaclculatedAngles);
				}
			}
		}



	}
	catch (std::exception e)
	{
	}
}


void stylemenu2()
{
	ImGuiStyle& style = ImGui::GetStyle();
	//style.WindowRounding = 5.0f;
	//style.WindowBorderSize = 2.0f;

	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 0.85f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.17f, 0.17f, 0.17f, 0.85f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
	colors[ImGuiCol_Border] = ImVec4(0.19f, 0.19f, 0.19f, 0.29f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
	colors[ImGuiCol_Button] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
	colors[ImGuiCol_Separator] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
	colors[ImGuiCol_Tab] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.20f, 0.20f, 0.36f);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_TableHeaderBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	colors[ImGuiCol_TableBorderStrong] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	colors[ImGuiCol_TableBorderLight] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
	colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
	colors[ImGuiCol_NavHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 0.70f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.20f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.35f);
}

void cache()
{
	while (true)
	{
		uintptr_t UWorld = driver.read_guarded<uintptr_t>(driver.VirtualAddress + 0x60);
		printf("UWorld %p\n", UWorld);
		uintptr_t GameInstance = driver.read_guarded<uintptr_t>(UWorld + GAME_INSTANCE);
		printf("GameInstance %p\n", GameInstance);
		uintptr_t PersistentLevel = driver.read_guarded<uintptr_t>(UWorld + PERSISTENT_LEVEL);
		printf("PersistentLevel %p\n", PersistentLevel);
		uintptr_t LocalPlayers_Array = driver.read_guarded<uintptr_t>(GameInstance + LOCALPLAYERS_ARRAY);
		printf("LocalPlayers_Array %p\n", LocalPlayers_Array);
		uintptr_t LocalPlayer = driver.read_guarded<uintptr_t>(LocalPlayers_Array);
		printf("LocalPlayer %p\n", LocalPlayer);
		glocalplayercontroller = driver.read_guarded<uintptr_t>(LocalPlayer + PLAYER_CONTROLER);
		glocalpawn = driver.read_guarded<uintptr_t>(glocalplayercontroller + LOCALPLAYERPAWN);
		glocaldamagehandler = driver.read_guarded<uintptr_t>(glocalpawn + DAMAGE_HANDLER);
		uintptr_t LocalPlayerState = driver.read_guarded<uintptr_t>(glocalpawn + PLAYER_STATE);
		uintptr_t LocalTeamComponent = driver.read_guarded<uintptr_t>(LocalPlayerState + TEAM_COMP);
		glocalteamid = driver.read_guarded<int>(LocalTeamComponent + TEAM_ID);
		gcameramanager = driver.read_guarded<uintptr_t>(glocalplayercontroller + CAMERA_MANAGER);
		uintptr_t ActorArray = driver.read_guarded<uintptr_t>(PersistentLevel + ACTOR_ARRAY);
		int ActorCount = driver.read_guarded<int>(PersistentLevel + ACTOR_COUNT);
		enemy_array = SDK::GetEnemyArray(ActorArray, ActorCount);
		std::this_thread::sleep_for(std::chrono::milliseconds(2500));
	}
}
#include "auth.hpp"

using namespace KeyAuth;

std::string namee = "Valorant Cheat"; // application name. right above the blurred text aka the secret on the licenses tab among other tabs
std::string ownerid = "jHHXUBClti"; // ownerid, found in account settings. click your profile picture on top right of dashboard and then account settings.
std::string secret = "881d85a37f45da805cc6db7c40af382398b7b5e1e8adebfa8ca172bcbfa2cf41"; // app secret, the blurred text on licenses tab and other tabs
std::string version = "1.0"; // leave alone unless you've changed version on website
std::string url = "https://auth.aliencheats.com/api/1.1/"; // change if you're self-hosting
std::string sslPin = "ssl pin key (optional)"; // don't change unless you intend to pin public certificate key. you can get here in the "Pin SHA256" field https://www.ssllabs.com/ssltest/analyze.html?d=keyauth.win&latest. If you do this you need to be aware of when SSL key expires so you can update it
api KeyAuthApp(namee, ownerid, secret, version, url, sslPin);

int main()
{
	SetConsoleTitleA(skCrypt("  "));
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handle, &info);
	COORD new_size =
	{
		info.srWindow.Right - info.srWindow.Left + 1,
		info.srWindow.Bottom - info.srWindow.Top + 1
	};
	SetConsoleScreenBufferSize(handle, new_size);

	HWND hwnd = GetConsoleWindow();
	if (hwnd != NULL) { MoveWindow(hwnd, 200, 100, 320, 550, TRUE); }
	SetLayeredWindowAttributes(hwnd, 1000, 1000, LWA_ALPHA);

	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);

	SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

	SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);

	KeyAuthApp.init();

	SetConsoleTitleA(skCrypt("  "));

	KeyAuthApp.init();
	std::string key;
	system(skCrypt("cls"));
	std::cout << skCrypt("\n\n  [+] Connecting..");
	std::cout << skCrypt("\n\n  [+] License: ");
	std::cin >> key;
	KeyAuthApp.license(key);
	if (!KeyAuthApp.data.success)
	{
		std::cout << "\n Status: " + KeyAuthApp.data.message;
		Sleep(1500);
		exit(0);
	}

r8:
	if (!driver.init())
	{
	r7:
		if (FindWindowA(skCrypt("UnityWndClass"), NULL))
		{
			printf(skCrypt("[>] close game please...\n"));
			Sleep(1000);
			goto r7;
		}
		if (LoadDriver())
		{
			printf(skCrypt("[>] driver loaded!\n"));
			Sleep(1000);
			system("cls");
			goto r8;
		}
	}
	HWND Entryhwnd = NULL;
	while (Entryhwnd == NULL)
	{
		printf(skCrypt("[>] waiting for game\n"));
		Sleep(1);
		driver.pid = get_pid();
		printf(skCrypt("[>] pid: %d\n"), driver.pid);
		Entryhwnd = get_process_wnd(driver.pid);
		Sleep(1);
	}
	driver.attach(driver.pid);
	setup_window();
	init_wndparams(MyWnd);
	g_base = driver.get_process_base();
	driver.VirtualAddress = driver.get_guarded_base();
	if (!g_base) { printf(skCrypt("[>] g_base can't found!\n")); return 0; }
	printf("[>] G_Base: 0x%p\n[>] VirtualAddress: 0x%p\n", g_base, driver.VirtualAddress);
	static RECT old_rc;
	ZeroMemory(&Message, sizeof(MSG));
	std::thread(cache).detach();
	//::SetWindowPos(GetConsoleWindow(), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_HIDEWINDOW);
	stylemenu2();
	while (Message.message != WM_QUIT)
	{
		if (PeekMessage(&Message, MyWnd, 0, 0, PM_REMOVE)) {
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

		HWND hwnd_active = GetForegroundWindow();


		if (hwnd_active == GameWnd) {
			HWND hwndtest = GetWindow(hwnd_active, GW_HWNDPREV);
			SetWindowPos(MyWnd, hwndtest, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		}
		RECT rc;
		POINT xy;

		ZeroMemory(&rc, sizeof(RECT));
		ZeroMemory(&xy, sizeof(POINT));
		GetClientRect(GameWnd, &rc);
		ClientToScreen(GameWnd, &xy);
		rc.left = xy.x;
		rc.top = xy.y;

		ImGuiIO& io = ImGui::GetIO();
		io.ImeWindowHandle = GameWnd;
		io.DeltaTime = 1.0f / 60.0f;

		POINT p;
		GetCursorPos(&p);
		io.MousePos.x = p.x - xy.x;
		io.MousePos.y = p.y - xy.y;
		if (GetAsyncKeyState(0x1)) {
			io.MouseDown[0] = true;
			io.MouseClicked[0] = true;
			io.MouseClickedPos[0].x = io.MousePos.x;
			io.MouseClickedPos[0].x = io.MousePos.y;
		}
		else io.MouseDown[0] = false;

		if (rc.left != old_rc.left || rc.right != old_rc.right || rc.top != old_rc.top || rc.bottom != old_rc.bottom) {

			old_rc = rc;

			Width = rc.right;
			Height = rc.bottom;

			p_Params.BackBufferWidth = Width;
			p_Params.BackBufferHeight = Height;
			SetWindowPos(MyWnd, (HWND)0, xy.x, xy.y, Width, Height, SWP_NOREDRAW);
			p_Device->Reset(&p_Params);
		}
		render();
		std::thread(aimbot).detach();
		Sleep(10);
	}

	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	cleanup_d3d();
	DestroyWindow(MyWnd);
	return Message.wParam;
}