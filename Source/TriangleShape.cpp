#include "TriangleShape.hpp"

namespace VisualEditor {
    namespace Graphics {

        void TriangleShape::Render() {
            GraphicUtility::TriangleEdge(mPosition, mSize, mColor);
            if (mHovered || mSelected)
                GraphicUtility::TriangleEdge(mPosition, mSize + 0.01);
        }

        void TriangleShape::OnEvent(SDL_Event *event, ImVec2 mousePos) {
            Shape::OnEvent(event, mousePos);
            auto pt = ImVec2(mousePos.x, -mousePos.y);
            auto topPoint = ImVec2(mPosition.x, mPosition.y - mSize);
            auto leftPoint = ImVec2(mPosition.x - mSize, mPosition.y + mSize);
            auto rightPoint = ImVec2(mPosition.x + mSize, mPosition.y + mSize);
            float d1, d2, d3;
            bool hasNeg, hasPos;
            d1 = Sign(pt, leftPoint, topPoint);
            d2 = Sign(pt, topPoint, rightPoint);
            d3 = Sign(pt, rightPoint, leftPoint);
            hasNeg = (d1 < 0) || (d2 < 0) || (d3 < 0);
            hasPos = (d1 > 0) || (d2 > 0) || (d3 > 0);
            mHovered = !(hasNeg && hasPos);
            auto normPoint = ImVec2(mousePos.x, -mousePos.y);
            if (event->type == SDL_MOUSEBUTTONDOWN &&
                ((normPoint.x > -1 && normPoint.x < 1) && (normPoint.y > -1 && normPoint.y < 1))
                    ) {
                if (!mHovered && mShift && mSelected) {

                }
                else mSelected = mHovered;
                mMousePressed = true;
            }
            if (event->type == SDL_MOUSEBUTTONUP)
                mMousePressed = false;
            if (event->type == SDL_MOUSEMOTION) {
                if (mMousePressed && mHovered && !CheckBounds(ImVec2(mousePos.x, -mousePos.y)))
                    mPosition = ImVec2(mousePos.x, -mousePos.y);
            }
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

    }
}