#pragma once
#include "pch.hpp"

namespace VisualEditor {

    class Window {
    public:
        Window() = default;
        Window(const Window& other) = delete;
        bool Initialize(const std::string& title, ImVec2 size, SDL_HitTest hitTest = nullptr);
        virtual void Render() = 0;
        void Shutdown();
        virtual ~Window() = default;
    protected:
        void BeginFrame(GLclampf r, GLclampf g, GLclampf b, GLclampf a);
        void EndFrame();
    protected:
        SDL_Event mEvent{};
    private:
        SDL_Renderer* mRenderer{};
        SDL_Window* mWindow{};
        SDL_GLContext mContext{};
    };

}