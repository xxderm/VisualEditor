#include "GroupShape.hpp"

namespace VisualEditor::Graphics {

    void GroupShape::Render() {
        auto points = GetQuadSize();
        mPosition = ImVec2(points.x, points.y);
        mSize = ImVec2(points.z, points.w);
        if (mHovered)
            GraphicUtility::Grid(mPosition, mSize);
        if (mEntities.Size() > 0) {
            for (uint32_t i = 0; i < mEntities.Size(); i++)
                (mEntities)[i]->Render();
        }
    }

    void GroupShape::Add(Shape* shape) {
        mEntities.Push(shape);
    }

    Quad GroupShape::GetBounds(ImVec2 pos) {
        auto points = GetQuadSize();
        auto width = points.z;
        auto height = points.w;
        Quad quad;
        quad.TopLeft = ImVec2(pos.x - (width / 2. + 0.01), pos.y + (height / 2. + 0.01));
        quad.TopRight = ImVec2(pos.x + (width / 2. + 0.01), pos.y + (height / 2. + 0.01));
        quad.BtmLeft = ImVec2(pos.x - (width / 2. + 0.01), pos.y - (height / 2. + 0.01));
        quad.BtmRight = ImVec2(pos.x + (width / 2. + 0.01), pos.y - (height / 2. + 0.01));
        return quad;
    }

    bool GroupShape::IsMouseHover(ImVec2 mousePos) {
        for (uint32_t i = 0; i < mEntities.Size(); i++) {
            if ((mEntities)[i]->IsMouseHover(mousePos))
                return true;
        }
        return false;
    }

    ImVec4 GroupShape::GetQuadSize() {
        float xMin = 1.f, xMax = -1.f;
        float yMin = 1.f, yMax = -1.f;
        for (uint32_t i = 0; i < mEntities.Size(); i++) {
            auto bounds = (mEntities)[i]->GetBounds((mEntities)[i]->GetPosition());
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
        return ImVec4(xMax / 2. + xMin / 2., yMax / 2. + yMin / 2., width, height);
    }

}