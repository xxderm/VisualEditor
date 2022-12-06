#include "TriangleShape.hpp"

namespace VisualEditor {
    namespace Graphics {

        void TriangleShape::Render() {
            GraphicUtility::TriangleEdge(mPosition, mSize, mColor);
            if (mHovered)
                GraphicUtility::TriangleEdge(mPosition, mSize + 0.01, ImVec4(1, 1, 0.6, 1));
            if (mSelected)
                GraphicUtility::Grid(mPosition, mSize * 2.02);
        }

        float TriangleShape::Sign(ImVec2 p1, ImVec2 p2, ImVec2 p3) {
            return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
        }

        Quad TriangleShape::GetBounds(ImVec2 pos) {
            Quad quad;
            quad.TopLeft = ImVec2(pos.x - (mSize + 0.01), (pos.y + (mSize + 0.01)));
            quad.TopRight = ImVec2(pos.x + (mSize + 0.01), (pos.y + (mSize + 0.01)));
            quad.BtmLeft = ImVec2(pos.x - (mSize + 0.01), (pos.y - (mSize + 0.01)));
            quad.BtmRight = ImVec2(pos.x + (mSize + 0.01), (pos.y - (mSize + 0.01)));
            return quad;
        }

        bool TriangleShape::IsMouseHover(ImVec2 mousePos) {
            auto topPoint = ImVec2(mPosition.x, mPosition.y - mSize);
            auto leftPoint = ImVec2(mPosition.x - mSize, mPosition.y + mSize);
            auto rightPoint = ImVec2(mPosition.x + mSize, mPosition.y + mSize);
            float d1, d2, d3;
            bool hasNeg, hasPos;
            d1 = Sign(mousePos, leftPoint, topPoint);
            d2 = Sign(mousePos, topPoint, rightPoint);
            d3 = Sign(mousePos, rightPoint, leftPoint);
            hasNeg = (d1 < 0) || (d2 < 0) || (d3 < 0);
            hasPos = (d1 > 0) || (d2 > 0) || (d3 > 0);
            return !(hasNeg && hasPos);
        }

        Shape* TriangleShape::Copy() {
            TriangleShape* copy = new TriangleShape();
            copy->mSize = this->mSize;
            copy->mPosition = this->mPosition;
            copy->mColor = this->mColor;
            return copy;
        }

        void TriangleShape::Move(ImVec2 delta) {
            mPosition = delta;
        }

        bool TriangleShape::IsInFlexBorder(ImVec2 mouse) {
            auto topPoint = ImVec2(mPosition.x, mPosition.y - mSize);
            auto leftPoint = ImVec2(mPosition.x - mSize, mPosition.y + mSize);
            auto rightPoint = ImVec2(mPosition.x + mSize, mPosition.y + mSize);
            return (mouse.x >= topPoint.x - 0.05 && mouse.x <= topPoint.x + 0.05) &&
                   (mouse.y >= topPoint.y - 0.05 && mouse.y <= topPoint.y + 0.05);
        }

        void TriangleShape::Amplify(ImVec2 mouse) {
            auto dist = sqrt( ((mPosition.x - mouse.x) * (mPosition.x - mouse.x))
                              + ((mPosition.y - mouse.y) * (mPosition.y - mouse.y)) );
            //mSize = dist - 0.025;
            Flex(dist - 0.025);
        }

        void TriangleShape::Flex(double dist) {
            mSize = dist;
        }

        TriangleShape::TriangleShape(const TriangleShape &other) : Shape(other) {
            this->mSize = other.mSize;
        }

        void TriangleShape::Save(nlohmann::json *data, uint32_t* index) {
            Shape::Save(data, index);
            (*data)[std::to_string(*index)]["Name"] = GetName();
            (*data)[std::to_string(*index)]["Size"] = mSize;
        }

        void TriangleShape::Load(nlohmann::json *data, uint32_t *index) {
            Shape::Load(data, index);
            mSize = (*data)[std::to_string(*index)]["Size"];
        }

    }
}