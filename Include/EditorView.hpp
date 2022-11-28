#pragma once
#include "pch.hpp"

namespace VisualEditor {

    class EditorView;
    using EditorViewPtr = std::shared_ptr<EditorView>;

    class EditorView final {
    public:
        EditorView();
        EditorView(const EditorView& other) = delete;
        void Render(SDL_Window* window);
    private:
        void RenderSceneEntities(SDL_Window* window);
        void RenderEntityList(SDL_Window* window);
        void RenderEntitySettings(SDL_Window* window);
        void RenderActionList(SDL_Window* window);
        void RenderScene(SDL_Window* window);
    private:
        int mScrWidth{};
        int mScrHeight{};
    };

}