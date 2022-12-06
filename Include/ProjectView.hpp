#pragma once
#include "pch.hpp"

namespace VisualEditor {

    class ProjectView;
    using ProjectViewPtr = std::shared_ptr<ProjectView>;

    class ProjectView final {
    public:
        ProjectView();
        ProjectView(const ProjectView& other) = delete;
        void Render(SDL_Window* window);
        void OnAddProjectCallBack(const std::function<void(std::string)>& fn);
        void OnOpenProjectCallBack(const std::function<void(std::string)>& fn);
        void SetData(std::shared_ptr<nlohmann::json> data);
        void Hide();
        void Show();
    private:
        void RenderProjectTable(std::string projName, std::string projNum);
        void RenderProjectAdd();
        void ClearName();
    private:
        int mScrWidth{};
        int mScrHeight{};
        bool mOpened = true;
        bool mProjectAddProcess = false;
        GLuint mProjectIcon{};
        GLuint mProjectAddIcon{};
        GLuint mCancelProjectAddIcon{};
        GLuint mSuccesProjectAddIcon{};
        ImVec4 mBtnColor = ImVec4(0.129, 0.141, 0.149, 1.0);
        std::string mProjectAddName;
        std::function<void(std::string)> mAddProjectCallBack;
        std::function<void(std::string)> mOnOpenProjectCallBack;
        std::shared_ptr<nlohmann::json> mData;
    };

}