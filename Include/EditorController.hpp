#pragma once
#include "EditorView.hpp"

namespace VisualEditor {

    class EditorController;
    using EditorControllerPtr = std::shared_ptr<EditorController>;

    class EditorController final {
    public:
        EditorController();
        EditorController(const EditorController& other) = delete;
        void Render(SDL_Window* window);
        void OnEvent(SDL_Event* event);
    private:
        EditorViewPtr mEditorView;
    };

}