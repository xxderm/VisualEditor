#pragma once
#include "pch.hpp"
#include "ShapeFactory.hpp"
#include "Command.hpp"

namespace VisualEditor {

    class EditorView;
    using EditorViewPtr = std::shared_ptr<EditorView>;

    class EditorView final {
    public:
        EditorView(SDL_Window* window);
        EditorView(const EditorView& other) = delete;
        void Render(SDL_Window* window);
        void OnAddShape(const std::function<void(Graphics::ShapeType)>& fn);
        void OnChangeColor(const std::function<void(float r, float g, float b)>& fn);
        void OnMakeGroup(const std::function<void()>& fn);
        void OnUnGroup(const std::function<void()>& fn);
        void OnDelete(const std::function<void()>& fn);
        void SetEntities(const std::shared_ptr<Storage<std::shared_ptr<Graphics::Shape>>>& entities);
        void SetActions(const std::vector<std::shared_ptr<ICommand>>& actions);
        ImVec2 GetScenePos() const { return mScenePos; }
        ImVec2 GetSceneSize() const { return mSceneSize; }
    private:
        void RenderSceneEntities(SDL_Window* window);
        void RenderEntityList(SDL_Window* window);
        void RenderEntitySettings(SDL_Window* window);
        void RenderActionList(SDL_Window* window);
        void RenderScene(SDL_Window* window);
    private:
        int mScrWidth{};
        int mScrHeight{};
        std::shared_ptr<FrameBuffer> mFrame;
        float mColor[3];
        std::function<void(Graphics::ShapeType)> mOnAddCallBack;
        std::function<void(float r, float g, float b)> mOnChangeColorCallBack;
        std::function<void()> mOnMakeGroup;
        std::function<void()> mOnUnGroup;
        std::function<void()> mOnDelete;
        GLuint mTriangleIcon{};
        GLuint mCircleIcon{};
        GLuint mQuadIcon{};
        GLuint mLineIcon{};
        std::shared_ptr<Storage<std::shared_ptr<Graphics::Shape>>> mEntities;
        std::vector<std::shared_ptr<ICommand>> mActions;
        ImVec2 mScenePos{};
        ImVec2 mSceneSize{};
    };

}