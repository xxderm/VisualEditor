#include "EditorWindow.hpp"
#include <iostream>

namespace VisualEditor {

    static SDL_HitTestResult SDLCALL EditorWindowHitTest(SDL_Window *window, const SDL_Point *pt, void *data) {
        int w, h;
        SDL_GetWindowSize(window, &w, &h);
        const SDL_Rect dragArea[] =  {
                { 0, 0, w - 50, 20}
        };
        for (const auto & i : dragArea) {
            if (SDL_PointInRect(pt, &i))
                return SDL_HITTEST_DRAGGABLE;
        }
        return SDL_HITTEST_NORMAL;
    }

    EditorWindow::EditorWindow() {
        if (!this->Initialize("Редактор", ImVec2(800, 600), EditorWindowHitTest))
            std::cout << "Failed to initialize window" << std::endl;
    }

    void EditorWindow::Render() {
        while (SDL_PollEvent(&mEvent)) {
            ImGui_ImplSDL2_ProcessEvent(&mEvent);
            if (mEvent.type == SDL_QUIT)
                this->Shutdown();
        }
        this->BeginFrame(0, 0, 0, 1);
        this->EndFrame();
    }

    EditorWindow::~EditorWindow() {
        this->Shutdown();
    }

}
