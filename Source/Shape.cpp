#pragma once

#include <Shape.hpp>

namespace VisualEditor::Graphics {

    bool Graphics::Shape::CheckBounds(ImVec2 pos) {
        auto quad = this->GetBounds(pos);
        if (quad.TopLeft.x < -1. || quad.TopRight.x > 1.)
            return true;
        if (quad.TopRight.y > 1.)
            return true;
        if (quad.BtmLeft.x < -1. || quad.BtmRight.x > 1.)
            return true;
        if (quad.BtmRight.y < -1.)
            return true;
        return false;
    }

    void Shape::OnEvent(SDL_Event *event, ImVec2 mousePos) {
        if (mIsFlex && mMousePressed)
            Amplify(mousePos);
        if (event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP) {
            if (event->button.button == SDL_BUTTON_RIGHT)
                return;
        }
        if (event->type == SDL_KEYDOWN)
            if (event->key.keysym.sym == SDLK_LSHIFT)
                mShift = true;
            if (event->key.keysym.sym == SDLK_ESCAPE)
                mSelected = false;
        if (event->type == SDL_KEYUP)
            if (event->key.keysym.sym == SDLK_LSHIFT)
                mShift = false;
        mHovered = IsMouseHover(mousePos);
        if (event->type == SDL_MOUSEBUTTONDOWN &&
            ((mousePos.x > -1 && mousePos.x < 1) && (mousePos.y > -1 && mousePos.y < 1))
                ) {
            mIsFlex = IsInFlexBorder(mousePos);
            if (mShift && mHovered)
                mSelected = mHovered;
            mMousePressed = true;
            if (mHovered)
                mDeltaDiff = ImVec2(mPosition.x - mousePos.x, mPosition.y - mousePos.y);
        }
        if (event->type == SDL_MOUSEBUTTONUP) {
            mMousePressed = false;
            mDeltaDiff = {};
        }
        if (event->type == SDL_MOUSEMOTION) {
            auto normalizePosition = ImVec2(mousePos.x + mDeltaDiff.x, mousePos.y + mDeltaDiff.y);
            if (mMousePressed && mHovered && !CheckBounds(normalizePosition) ) {
                this->Move(normalizePosition);
            }
        }
    }

}