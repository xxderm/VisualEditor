#include "TriangleShape.hpp"

namespace VisualEditor {
    namespace Graphics {

        void TriangleShape::Render() {
            GraphicUtility::TriangleEdge(mPosition, mSize, mColor);
            if (mHovered || mSelected)
                GraphicUtility::TriangleEdge(mPosition, mSize + 0.01);
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

    }
}