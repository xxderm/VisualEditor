#include "EditorWindow.hpp"

namespace VisualEditor {

    EditorWindow::EditorWindow() {
        if (!this->Initialize("Редактор", ImVec2(800, 600)))
            std::cout << "Failed to initialize window" << std::endl;
        int tw, th;
        LoadTextureFromFile("../Resources/close.png", &mExitBtnTexture, &tw, &th);
    }

    void EditorWindow::Render() {
        while (mRunning) {
            while (SDL_PollEvent(&mEvent)) {
                ImGui_ImplSDL2_ProcessEvent(&mEvent);
                if (mEvent.type == SDL_QUIT) {
                    this->mRunning = false;
                    this->Shutdown();
                }
            }
            this->BeginFrame(0.19, 0.19, 0.19, 1);
            RenderMenuBar();
            this->EndFrame();
        }
    }

    EditorWindow::~EditorWindow() {
        this->Shutdown();
    }

    void EditorWindow::RenderMenuBar() {
        int scrWidth, scrHeight;
        SDL_GetWindowSize(this->mWindow, &scrWidth, &scrHeight);
        ImGui::PushStyleColor(ImGuiCol_MenuBarBg,
                ImGui::ColorConvertFloat4ToU32(ImVec4(0.1, 0.1, 0.1, 1.)));
        if (ImGui::BeginMainMenuBar()) {
            ImGui::Text("Visual Editor");
            ImGui::SameLine();
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("New project")) {

                }
                if (ImGui::MenuItem("Open project")) {

                }
                ImGui::Separator();
                if (ImGui::MenuItem("Save")) {

                }
                if (ImGui::MenuItem("Save as")) {

                }
                ImGui::Separator();
                if (ImGui::MenuItem("Exit"))
                    this->mRunning = false;
                ImGui::EndMenu();
            }
            ImGui::SameLine(scrWidth - 30);
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);
            if (ImGui::ImageButton(
                    (ImTextureID)mExitBtnTexture, ImVec2(15, 15),
                    ImVec2(0, 0), ImVec2(1, 1), 0,
                    ImVec4(0, 0, 0,  0.55))) {
                this->mRunning = false;
            }
            ImGui::EndMainMenuBar();
        }
        ImGui::PopStyleColor();
    }

}
