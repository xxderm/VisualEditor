#include "EditorWindow.hpp"

namespace VisualEditor {

    EditorWindow::EditorWindow() {
        if (!this->Initialize("Редактор", ImVec2(800, 600)))
            std::cout << "Failed to initialize window" << std::endl;
    }

    void EditorWindow::Render() {
        while (mRunning) {
            while (SDL_PollEvent(&mEvent)) {
                ImGui_ImplSDL2_ProcessEvent(&mEvent);
                if (mEvent.type == SDL_QUIT)
                    this->Shutdown();
            }
            this->BeginFrame(0.19, 0.19, 0.19, 1);
            this->EndFrame();
        }
    }

    EditorWindow::~EditorWindow() {
        this->Shutdown();
    }

}
