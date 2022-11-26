#pragma once
#include "pch.hpp"

namespace VisualEditor {

    class Window {
    public:
        Window() = default;
        Window(const Window& other) = delete;
        bool Initialize(const std::string& title, ImVec2 size);
        virtual void Render() = 0;
        void Shutdown();
        virtual ~Window() = default;
    protected:
        void BeginFrame(GLclampf r, GLclampf g, GLclampf b, GLclampf a);
        void EndFrame();
    protected:
        SDL_Event mEvent{};
        SDL_Window* mWindow{};
        bool mRunning = false;
    private:
        SDL_Renderer* mRenderer{};
        SDL_GLContext mContext{};
    };

}