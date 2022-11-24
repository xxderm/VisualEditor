#include "EditorWindow.hpp"

int main(int argc, char** argv) {
    VisualEditor::EditorWindow editorWindow;
    while (true) {
        editorWindow.Render();
    }
    return 0;
}