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

static void ImGuiCustomStyle() {
    ImGuiStyle& style = ImGui::GetStyle();
    style.Colors[ImGuiCol_Text]                  = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_TextDisabled]          = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    style.Colors[ImGuiCol_WindowBg]              = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
    style.Colors[ImGuiCol_ChildBg]               = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
    style.Colors[ImGuiCol_PopupBg]               = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
    style.Colors[ImGuiCol_Border]                = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
    style.Colors[ImGuiCol_BorderShadow]          = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_FrameBg]               = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    style.Colors[ImGuiCol_FrameBgHovered]        = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
    style.Colors[ImGuiCol_FrameBgActive]         = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
    style.Colors[ImGuiCol_TitleBg]               = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
    style.Colors[ImGuiCol_TitleBgActive]         = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
    style.Colors[ImGuiCol_TitleBgCollapsed]      = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
    style.Colors[ImGuiCol_MenuBarBg]             = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarBg]           = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
    style.Colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
    style.Colors[ImGuiCol_CheckMark]             = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
    style.Colors[ImGuiCol_SliderGrab]            = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
    style.Colors[ImGuiCol_SliderGrabActive]      = ImVec4(0.08f, 0.50f, 0.72f, 1.00f);
    style.Colors[ImGuiCol_Button]                = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    style.Colors[ImGuiCol_ButtonHovered]         = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
    style.Colors[ImGuiCol_ButtonActive]          = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
    style.Colors[ImGuiCol_Header]                = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
    style.Colors[ImGuiCol_HeaderHovered]         = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    style.Colors[ImGuiCol_HeaderActive]          = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
    style.Colors[ImGuiCol_Separator]             = style.Colors[ImGuiCol_Border];
    style.Colors[ImGuiCol_SeparatorHovered]      = ImVec4(0.41f, 0.42f, 0.44f, 1.00f);
    style.Colors[ImGuiCol_SeparatorActive]       = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
    style.Colors[ImGuiCol_ResizeGrip]            = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_ResizeGripHovered]     = ImVec4(0.29f, 0.30f, 0.31f, 0.67f);
    style.Colors[ImGuiCol_ResizeGripActive]      = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
    style.Colors[ImGuiCol_Tab]                   = ImVec4(0.08f, 0.08f, 0.09f, 0.83f);
    style.Colors[ImGuiCol_TabHovered]            = ImVec4(0.33f, 0.34f, 0.36f, 0.83f);
    style.Colors[ImGuiCol_TabActive]             = ImVec4(0.23f, 0.23f, 0.24f, 1.00f);
    style.Colors[ImGuiCol_TabUnfocused]          = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
    style.Colors[ImGuiCol_TabUnfocusedActive]    = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
    style.Colors[ImGuiCol_PlotLines]             = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    style.Colors[ImGuiCol_PlotLinesHovered]      = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogram]         = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogramHovered]  = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_TextSelectedBg]        = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
    style.Colors[ImGuiCol_DragDropTarget]        = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
    style.Colors[ImGuiCol_NavHighlight]          = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    style.Colors[ImGuiCol_NavWindowingDimBg]     = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    style.Colors[ImGuiCol_ModalWindowDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
    style.GrabRounding                           = style.FrameRounding = 2.3f;
}

namespace VisualEditor {

    bool Window::Initialize(const std::string& title, ImVec2 size) {
        if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
            return false;
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
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
        ImGuiCustomStyle();
        auto& io = ImGui::GetIO();
        (void)io;
        io.Fonts[0];
        mRenderer = SDL_CreateRenderer(mWindow, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (!mRenderer)
            return false;
        SDL_SetWindowHitTest(mWindow, HitTest, 0);
        ImGui_ImplSDL2_InitForOpenGL(mWindow, mContext);
        ImGui_ImplOpenGL3_Init();
        SDL_GL_SetSwapInterval(1);
        mRunning = true;
        glClearDepth(1.f);
        glDepthFunc(GL_LESS);
        glEnable(GL_DEPTH_TEST);
        glShadeModel(GL_FLAT | GL_SMOOTH);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glMatrixMode(GL_MODELVIEW);
        glewInit();
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
        if (!this->Initialize("Редактор", ImVec2(950, 800)))
            std::cout << "Failed to initialize window" << std::endl;
        int tw, th;
        LoadTextureFromFile("../Resources/close.png", &mExitBtnTexture, &tw, &th);
        mEditorController = std::make_shared<EditorController>(mWindow);
        mProjectController = std::make_shared<ProjectController>();

    }

    void Window::Render() {
        while (mRunning) {
            while (SDL_PollEvent(&mEvent)) {
                ImGui_ImplSDL2_ProcessEvent(&mEvent);
                mEditorController->OnEvent(&mEvent);
                mProjectController->OnEvent(&mEvent);
                if (mEvent.type == SDL_QUIT) {
                    this->Shutdown();
                }
            }
            this->BeginFrame(0.19, 0.19, 0.19, 1.);
            RenderMainMenuBar();
            mEditorController->Render(mWindow);
            mProjectController->Render(mWindow);
            mProjectController->OnOpenProjectCallBack([this](std::string proj) {
                mEditorController->Load(proj);
                this->mProjectTitle = proj;
            });
            mProjectController->OnAddProjectCallBack([this](std::string proj) {
                mEditorController->Save(proj);
                this->mProjectTitle = proj;
            });
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
                    mProjectController->Show();
                }
                if (ImGui::MenuItem("Open project")) {
                    mProjectController->Show();
                }
                ImGui::Separator();
                if (ImGui::MenuItem("Save")) {
                    mEditorController->Save(mProjectTitle);
                }
                if (ImGui::MenuItem("Save as")) {
                    mEditorController->Save(mProjectTitle);
                }
                ImGui::Separator();
                if (ImGui::MenuItem("Exit"))
                    mRunning = false;
                ImGui::EndMenu();
            }
            auto textLen = ImGui::CalcTextSize(mProjectTitle.c_str());
            ImGui::SameLine((scrWidth / 2) - textLen.x / 2);
            ImGui::Text(mProjectTitle.c_str());
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