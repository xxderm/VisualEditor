#include "GroupShape.hpp"

namespace VisualEditor::Graphics {

    void GroupShape::Render() {
        auto points = GetQuadSize();
        if (mHovered || mSelected)
            GraphicUtility::Grid(ImVec2(points.x, points.y), ImVec2(points.z, points.w));
        if (mEntities.Size() > 0) {
            for (uint32_t i = 0; i < mEntities.Size(); i++)
                (mEntities)[i]->Render();
        }
    }

    void GroupShape::Add(Shape* shape) {
        mEntities.Push(shape);
        auto points = GetQuadSize();
        mPosition = ImVec2(points.x, points.y);
        mSize = ImVec2(points.z, points.w);
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

    void GroupShape::Move(ImVec2 delta) {
        for (uint32_t i = 0; i < mEntities.Size(); i++) {
            auto currentPosition = mEntities[i]->GetPosition();
            auto deltaDiff = ImVec2(currentPosition.x - mPosition.x, currentPosition.y - mPosition.y);
            mEntities[i]->Move(ImVec2(delta.x + deltaDiff.x, delta.y + deltaDiff.y));
        }
        // TODO: исправить тремор
        auto points = GetQuadSize();
        mPosition = ImVec2(points.x, points.y);
        mSize = ImVec2(points.z, points.w);
    }

    GroupShape::~GroupShape() {
        // TODO: проверять на необходимость освобождения
        //for (int i = 0; i < mEntities.Size(); ++i)
            //delete mEntities[i];
    }

    Shape *GroupShape::Copy() {
        GroupShape* copy = new GroupShape();
        copy->mPosition = this->mPosition;
        copy->mColor = this->mColor;
        copy->mSize = this->mSize;
        copy->mEntities = this->mEntities;
        return copy;
    }

}