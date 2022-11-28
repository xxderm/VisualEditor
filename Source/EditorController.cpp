#include "EditorController.hpp"

namespace VisualEditor {

    EditorController::EditorController() {
        mEditorView = std::make_shared<EditorView>();
    }

    void EditorController::Render(SDL_Window* window) {
        mEditorView->Render(window);
    }

    void EditorController::OnEvent(SDL_Event *event) {

    }

}
