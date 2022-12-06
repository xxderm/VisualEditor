#pragma once
#include "ProjectView.hpp"

namespace VisualEditor {

    class ProjectController;
    using ProjectControllerPtr = std::shared_ptr<ProjectController>;

    class ProjectController final {
    public:
        ProjectController();
        ProjectController(const ProjectController& other) = delete;
        void OnOpenProjectCallBack(const std::function<void(std::string)>& fn);
        void OnAddProjectCallBack(const std::function<void(std::string)>& fn);
        void Render(SDL_Window* window);
        void OnEvent(SDL_Event* event);
        void Update();
        void Show();
    private:
        void ReadProjectListFile();
        void AddProjectToList(const std::string& name);
    private:
        ProjectViewPtr mProjectView;
        std::shared_ptr<nlohmann::json> mJsonData;
        std::function<void(std::string)> mOnOpenProjectCallBack;
        std::function<void(std::string)> mOnAddProjectCallBack;
    };

}