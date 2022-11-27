#pragma once
#include "EditorController.hpp"

namespace VisualEditor {

    class EditorController;

    class Window final {
    public:
        Window();
        Window(const Window& other) = delete;
        void Render();
        void Shutdown();
        ~Window() = default;
    private:
        bool Initialize(const std::string& title, ImVec2 size);
        void BeginFrame(GLclampf r, GLclampf g, GLclampf b, GLclampf a);
        void RenderMainMenuBar();
        void EndFrame();
    private:
        SDL_Event mEvent{};
        SDL_Window* mWindow{};
        bool mRunning = false;
        SDL_Renderer* mRenderer{};
        SDL_GLContext mContext{};
        GLuint mExitBtnTexture{};
    };

}