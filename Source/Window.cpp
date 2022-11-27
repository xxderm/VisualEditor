#include "Window.hpp"

static SDL_HitTestResult SDLCALL HitTest(SDL_Window *window, const SDL_Point *pt, void *data) {
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    const SDL_Rect dragArea[] =  {
            { 150, 0, w - 180, 20}
    };
    for (const auto & i : dragArea) {
        if (SDL_PointInRect(pt, &i))
            return SDL_HITTEST_DRAGGABLE;
    }
    return SDL_HITTEST_NORMAL;
}

namespace VisualEditor {

    bool Window::Initialize(const std::string& title, ImVec2 size) {
        if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
            return false;
        mWindow = SDL_CreateWindow(
                title.c_str(),
                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                size.x, size.y,
                SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS | SDL_WINDOW_RESIZABLE);
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
        SDL_SetWindowHitTest(mWindow, HitTest, 0);
        ImGui_ImplSDL2_InitForOpenGL(mWindow, mContext);
        ImGui_ImplOpenGL3_Init();
        SDL_GL_SetSwapInterval(1);
        mRunning = true;
        return true;
    }

    void Window::Shutdown() {
        mRunning = false;
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

    Window::Window() {
        if (!this->Initialize("Редактор", ImVec2(800, 600)))
            std::cout << "Failed to initialize window" << std::endl;
        int tw, th;
        LoadTextureFromFile("../Resources/close.png", &mExitBtnTexture, &tw, &th);
    }

    void Window::Render() {
        while (mRunning) {
            while (SDL_PollEvent(&mEvent)) {
                ImGui_ImplSDL2_ProcessEvent(&mEvent);
                if (mEvent.type == SDL_QUIT) {
                    this->Shutdown();
                }
            }
            this->BeginFrame(0.19, 0.19, 0.19, 1.);
            RenderMainMenuBar();
            this->EndFrame();
        }
    }

    void Window::RenderMainMenuBar() {
        int scrWidth, scrHeight;
        SDL_GetWindowSize(mWindow, &scrWidth, &scrHeight);
        ImGui::PushStyleColor(ImGuiCol_MenuBarBg,
                              ImGui::ColorConvertFloat4ToU32(ImVec4(0.1, 0.1, 0.1, 1.)));
        if (ImGui::BeginMainMenuBar()) {
            ImGui::Text("Visual Editor");
            ImGui::SameLine();
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("New project")) {

                }
                if (ImGui::MenuItem("Open project")) {

                }
                ImGui::Separator();
                if (ImGui::MenuItem("Save")) {

                }
                if (ImGui::MenuItem("Save as")) {

                }
                ImGui::Separator();
                if (ImGui::MenuItem("Exit"))
                    mRunning = false;
                ImGui::EndMenu();
            }
            ImGui::SameLine(scrWidth - 30);
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);
            if (ImGui::ImageButton(
                    (ImTextureID)mExitBtnTexture, ImVec2(15, 15),
                    ImVec2(0, 0), ImVec2(1, 1), 0,
                    ImVec4(0, 0, 0,  0.55))) {
                mRunning = false;
            }
            ImGui::EndMainMenuBar();
        }
        ImGui::PopStyleColor();
    }

}