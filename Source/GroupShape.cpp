#include "GroupShape.hpp"

namespace VisualEditor::Graphics {

    void GroupShape::Render() {
        if (mEntities.GetSize() > 0) {
            for (auto begin = mEntities.Begin(); begin != mEntities.End(); ++begin)
                (*begin)->Render();
        }
    }

    void GroupShape::Add(std::shared_ptr<Shape> shape) {
        mEntities.Push(shape);
    }

}