#include "QuadShape.hpp"

namespace VisualEditor{
    namespace Graphics {

        void QuadShape::Render() {
            GraphicUtility::QuadEdge(mPosition, mSize, mColor);
            if (mHovered || mSelected)
                GraphicUtility::QuadEdge(mPosition, ImVec2(mSize.x + 0.015, mSize.y + 0.015));
        }

        void QuadShape::OnEvent(SDL_Event *event, ImVec2 mousePos) {
            auto normPoint = ImVec2(mousePos.x, -mousePos.y);
            mHovered = ((normPoint.x >= mPosition.x - mSize.x / 2.) && (normPoint.x <= mPosition.x + mSize.x / 2.)) &&
                       ((normPoint.y >= mPosition.y - mSize.y / 2.) && (normPoint.y <= mPosition.y + mSize.y / 2.));
            if (event->type == SDL_MOUSEBUTTONDOWN &&
                ((normPoint.x > -1 && normPoint.x < 1) && (normPoint.y > -1 && normPoint.y < 1))
                    ) {
                mSelected = mHovered;
                mMousePressed = true;
            }
            if (event->type == SDL_MOUSEBUTTONUP)
                mMousePressed = false;
            if (event->type == SDL_MOUSEMOTION) {
                if (mMousePressed && mHovered && !CheckBounds(ImVec2(mousePos.x, -mousePos.y)))
                    mPosition = ImVec2(mousePos.x, -mousePos.y);
            }
        }

        bool QuadShape::CheckBounds(ImVec2 pos) {
            auto nsize = ImVec2(mSize.x + 0.01, mSize.y + 0.01);
            if (pos.x + nsize.x / 2 > 1)
                return true;
            if (pos.x - nsize.x / 2 < -1)
                return true;
            if (pos.y + nsize.y / 2 > 1)
                return true;
            if (pos.y - nsize.y / 2 < -1)
                return true;
            return false;
        }

    }
}