#pragma once
#include "Window.hpp"

namespace VisualEditor {

    class EditorWindow final : public Window {
    public:
        EditorWindow();

        EditorWindow(const EditorWindow& other) = delete;

        void Render() override;

        ~EditorWindow();
    };

}