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
        void Load(std::string project);
    private:
        EditorViewPtr mEditorView;
        std::shared_ptr<Storage<std::shared_ptr<Graphics::Shape>>> mEntities;
        //std::vector<std::shared_ptr<ICommand>> mActions;
        CommandDispatcher mCmdDispatcher;
        ImVec2 mScrSize;
        SDL_SystemCursor mCursor = SDL_SYSTEM_CURSOR_ARROW;
        EntitiesModel mEntityModel;
        std::shared_ptr<TreeView> mTreeView;
    };

}