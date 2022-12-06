#pragma once
#include "EditorView.hpp"

namespace VisualEditor {

    class EditorController;
    using EditorControllerPtr = std::shared_ptr<EditorController>;

    class EditorController final {
    public:
        EditorController(SDL_Window* window);
        EditorController(const EditorController& other) = delete;
        void Render(SDL_Window* window);
        void OnEvent(SDL_Event* event);
        void Save(std::string project);
    private:
        EditorViewPtr mEditorView;
        std::shared_ptr<Storage<std::shared_ptr<Graphics::Shape>>> mEntities;
        std::vector<std::shared_ptr<ICommand>> mActions;
        std::vector<uint32_t> mIndicesToErase;
        ImVec2 mScrSize;
    };

}