#pragma once

using namespace ImGui;

void SetupImGui() {
    IMGUI_CHECKVERSION();
    CreateContext();
    ImGuiIO &io = GetIO();
    io.DisplaySize = ImVec2((float) glWidth, (float) glHeight);
    ImGui_ImplOpenGL3_Init("#version 100");
    StyleColorsDark();

    GetStyle().ScaleAllSizes(4.0f); // Change this to scale everything
}

void DrawMenu() {
    static bool showMenu = true;
    SetNextWindowSize(ImVec2(400, 400), ImGuiCond_FirstUseEver);
    if (Begin("Menu", &showMenu)) {
        Checkbox("Free Shopping", &Features::freeShop::isEnabled);
        Checkbox("Set 0 Prices", &Features::set0Prices::isEnabled);
    }
    End();
}