#include "EditorView.hpp"

namespace VisualEditor {

    EditorView::EditorView() {

    }

    void EditorView::Render(SDL_Window *window) {
        SDL_GetWindowSize(window, &mScrWidth, &mScrHeight);
        RenderSceneEntities(window);
        RenderEntityList(window);
        RenderEntitySettings(window);
        RenderActionList(window);
        RenderScene(window);
    }

    void EditorView::RenderSceneEntities(SDL_Window *window) {
        ImGui::SetNextWindowPos(ImVec2(5, 20));
        ImGui::SetNextWindowSize(ImVec2(mScrWidth * 0.2, mScrHeight * 0.25));
        ImGui::Begin("Objects", 0,
                     ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus);
        // TODO: for each entity, create selectable table
        ImGui::End();
    }

    void EditorView::RenderEntityList(SDL_Window *window) {
        ImGui::SetNextWindowPos(ImVec2(5, mScrHeight * 0.25 + 20));
        ImGui::SetNextWindowSize(ImVec2(mScrWidth * 0.2, mScrHeight * 0.2));
        ImGui::Begin("Object list", 0,
                     ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus);
        // TODO: for each entity, create selectable table
        ImGui::End();
    }

    void EditorView::RenderEntitySettings(SDL_Window *window) {
        ImGui::SetNextWindowPos(ImVec2(5, mScrHeight * 0.45 + 20));
        ImGui::SetNextWindowSize(ImVec2(mScrWidth * 0.2, mScrHeight * 0.3));
        ImGui::Begin("Settings", 0,
                     ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus);
        // TODO: for each entity, create selectable table
        ImGui::End();
    }

    void EditorView::RenderActionList(SDL_Window *window) {
        ImGui::SetNextWindowPos(ImVec2(5, mScrHeight * 0.75 + 20));
        ImGui::SetNextWindowSize(ImVec2(mScrWidth * 0.2, mScrHeight * 0.22));
        ImGui::Begin("Actions", 0,
                     ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus);
        // TODO: for each entity, create selectable table
        ImGui::End();
    }

    void EditorView::RenderScene(SDL_Window *window) {
        ImGui::SetNextWindowPos(ImVec2(mScrWidth * 0.204, 20));
        ImGui::SetNextWindowSize(ImVec2(mScrWidth * 0.793, mScrHeight * 0.97));
        ImGui::Begin("Scene", 0,
                ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus);
        // TODO: for each entity, create selectable table
        ImGui::End();
    }

}