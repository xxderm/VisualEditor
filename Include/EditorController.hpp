#pragma once
#include "pch.hpp"

namespace VisualEditor {

    class EditorController final {
    public:
        EditorController();
        EditorController(const EditorController& other) = delete;
        void Render(SDL_Window* window);
    private:
    };

}