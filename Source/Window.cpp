#include "Window.hpp"

namespace VisualEditor {

    bool Window::Initialize(const std::string& title, ImVec2 size, SDL_HitTest hitTest) {
        if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
            return false;
        mWindow = SDL_CreateWindow(
                title.c_str(),
                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                size.x, size.y,
                SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS);
        if (mWindow == 0)
            return false;
        mContext = SDL_GL_CreateContext(mWindow);
        if (mContext == 0)
            return false;
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        auto& io = ImGui::GetIO();
        (void)io;
        io.Fonts[0];
        ImGui::StyleColorsDark();
        mRenderer = SDL_CreateRenderer(mWindow, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (!mRenderer)
            return false;
        if (hitTest)
            SDL_SetWindowHitTest(mWindow, hitTest, 0);
        ImGui_ImplSDL2_InitForOpenGL(mWindow, mContext);
        ImGui_ImplOpenGL3_Init();
        SDL_GL_SetSwapInterval(1);
        return true;
    }

    void Window::Shutdown() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
        SDL_DestroyWindow(mWindow);
        SDL_DestroyRenderer(mRenderer);
        SDL_Quit();
    }

    void Window::BeginFrame(GLclampf r, GLclampf g, GLclampf b, GLclampf a) {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(mWindow);
        ImGui::NewFrame();

        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Window::EndFrame() {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(mWindow);
    }

}