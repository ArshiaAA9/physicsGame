#include "headers/Renderer.h"

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <array>
#include <iostream>
#include <string>

// public:

void Renderer::update(PhysicsWorld& world) {
    // clear the screen to white
    int objectCount = 0;
    clearScreen();

    // TODO: change this to use shape specific functions
    for (const auto& [obj, color] : m_renderMap) {
        drawColoredRect2(obj, color);
        objectCount++;
    }
    renderObjectCount(objectCount);

    // draw the renderer
    SDL_RenderPresent(m_renderer);
}

void Renderer::addRenderPair(ObjectPtr obj, SDL_FColor color) {
    m_renderMap.insert({obj, color});
} // add a key value pari

void Renderer::deleteRenderPair(ObjectPtr obj) { m_renderMap.erase(obj); } // remove a pair using key

SDL_Window* Renderer::getWindow() const { return m_window; } // return window pointer

SDL_Renderer* Renderer::getRenderer() const { return m_renderer; } // return renderer pointer

int Renderer::getWindowWidth() const { return m_windowWidth; } // return window Width

int Renderer::getWindowHeight() const { return m_windowHeight; } // return window Height

TTF_Font* Renderer::getFont() const { return m_font; } // return font pointer

const std::unordered_map<ObjectPtr, SDL_FColor>& Renderer::getRenderMap() {
    // return a const renference to render map
    return m_renderMap;
}

// private:

void Renderer::clearScreen() {
    // used to clear screen on each frame render
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255); // White background
    SDL_RenderClear(m_renderer);
}

void Renderer::drawColoredRect(const ObjectPtr object, SDL_FColor color) {
    // draws a rectangle using a object pointer and a SDL_Color
    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
    // sdl_rect takes position as topleft point of rect
    float width = object->getDimensions().x;
    float height = object->getDimensions().y;
    Vector2 pos = object->transform.position;
    SDL_FRect rect;
    rect.x = pos.x - width / 2;
    rect.y = m_windowHeight - pos.y - height / 2;
    rect.w = width;
    rect.h = height;
    SDL_RenderFillRect(m_renderer, &rect);
}

void Renderer::drawColoredRect2(const ObjectPtr object, SDL_FColor color) {
    std::array<SDL_Vertex, 4> vertices;
    for (int i = 0; i < 4; i++) {
        float py = m_windowHeight - object->transform.transformedVertices[i].y; // flip cause of sdl3
        SDL_FPoint position = {object->transform.transformedVertices[i].x, py};
        SDL_FPoint textCord = {0.0f, 0.0f};
        SDL_Vertex vertex = {position, color, textCord};
        vertices[i] = vertex;
    }
    const int indices[] = {0, 1, 2, 2, 3, 0};
    SDL_RenderGeometry(m_renderer, nullptr, vertices.data(), 4, indices, 6);
}

bool Renderer::initWindowAndRenderer() {
    // initailizing SDL_ttf
    if (!TTF_Init()) {
        std::cerr << "Error initializing TTF" << SDL_GetError() << std::endl;
    }

    // create font
    m_font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 24);
    if (!m_font) {
        std::cerr << "Failed to load font: " << SDL_GetError() << std::endl;
    }

    // create window
    m_window = SDL_CreateWindow("Physics Simulation", m_windowWidth, m_windowHeight, 0);
    if (!m_window) {
        std::cerr << "Error creating window: " << SDL_GetError() << std::endl;
        return false;
    }

    // create renderer
    m_renderer = SDL_CreateRenderer(m_window, nullptr);
    if (!m_renderer) {
        std::cerr << "Error creating renderer: " << SDL_GetError() << std::endl;
        return false;
    }

    // set renderer color and clear window
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    SDL_RenderClear(m_renderer);

    return true;
}

void Renderer::renderObjectCount(int count) {
    // renders a count for all rendered objects
    std::string countText = std::to_string(count);
    // text surface
    m_text = TTF_RenderText_Solid(m_font, countText.c_str(), countText.length(), m_textColor);
    if (!m_text) {
        std::cerr << "Failed to render text: " << SDL_GetError() << std::endl;
    }

    // text texture
    m_textTexture = SDL_CreateTextureFromSurface(m_renderer, m_text);
    SDL_FRect dest = {10, 10, static_cast<float>(m_text->w), static_cast<float>(m_text->h)};

    SDL_RenderTexture(m_renderer, m_textTexture, nullptr, &dest);
}
