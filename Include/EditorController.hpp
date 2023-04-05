#pragma once
#include "EditorView.hpp"
#include <Storage.hpp>
#include "SelectedShape.hpp"

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
        void UnselectAll();
        void DeleteSelected();
    private:
        EditorViewPtr mEditorView;
        std::shared_ptr<Storage<std::shared_ptr<Graphics::Shape>>> mEntities;
        CommandDispatcher mCmdDispatcher;
        ImVec2 mScrSize;
        SDL_SystemCursor mCursor = SDL_SYSTEM_CURSOR_ARROW;
        EntitiesModel mEntityModel;
        EntitiesModel mStickyEntitiesObserverModel;
        std::shared_ptr<TreeView> mTreeView;
        bool mMousePressed = false;
        bool mShift = false;
        bool mCtrl = false;
        ImVec2 mBeginMousePos{};
        ImVec2 mMotionPrev {-1, -1};
    };

}