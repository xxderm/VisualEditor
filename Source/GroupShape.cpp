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

    Quad GroupShape::GetBounds(ImVec2 pos) {
        float xMin = 1.f, xMax = -1.f;
        float yMin = 1.f, yMax = -1.f;
        for (auto begin = mEntities.Begin(); begin != mEntities.End(); ++begin) {
            auto bounds = (*begin)->GetBounds((*begin)->GetPosition());
            if (bounds.TopLeft.x < xMin)
                xMin = bounds.TopLeft.x;
            if (bounds.TopRight.x > xMax)
                xMax = bounds.TopRight.x;
            if (bounds.TopRight.y > yMax)
                yMax = bounds.TopRight.y;
            if (bounds.BtmRight.y < yMin)
                yMin = bounds.BtmRight.y;
        }
        auto width = xMax - xMin;
        auto height = yMax - yMin;
        Quad quad;
        quad.TopLeft = ImVec2(pos.x - (width / 2. + 0.01), pos.y + (height / 2. + 0.01));
        quad.TopRight = ImVec2(pos.x + (width / 2. + 0.01), pos.y + (height / 2. + 0.01));
        quad.BtmLeft = ImVec2(pos.x - (width / 2. + 0.01), pos.y - (height / 2. + 0.01));
        quad.BtmRight = ImVec2(pos.x + (width / 2. + 0.01), pos.y - (height / 2. + 0.01));
        return quad;
    }

    bool GroupShape::IsMouseHover(ImVec2 mousePos) {
        for (auto begin = mEntities.Begin(); begin != mEntities.End(); ++begin) {
            if ((*begin)->IsMouseHover(mousePos))
                return true;
        }
        return false;
    }

}