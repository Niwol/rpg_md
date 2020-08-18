#include "render.hpp"

cRender::cRender(SDL_Window* window, SDL_Renderer* renderer, int numberOfAnimations)
    : m_renderer(renderer)
    , m_currentFrame(0)
    , m_numberOfAnimations(numberOfAnimations)
    , m_animations(new sAnimation[numberOfAnimations])
    , m_spriteSheet(window, renderer)
{
    for (int i = 0; i < numberOfAnimations; i++) {
        m_animations[i].framesPerClip = 0;
        m_animations[i].numberOfClips = 0;
    }
}

cRender::~cRender()
{
}

bool cRender::load(std::string path)
{
    std::ifstream file;
    std::string line;

    file.open(path);
    if (file.is_open()) {
        while (!file.eof()) {
            std::getline(file, line);

            if (line == "< Render") {
                while (line[0] != '>') {

                    std::getline(file, line);
                    if (line[0] != '#')
                        printf("%s\n", line.c_str());
                }
            }
        }
    } else {
        return false;
    }

    file.close();
    return true;
}

void cRender::render(int x, int y)
{
    SDL_SetRenderDrawColor(m_renderer, 255, 0, 255, 255);

    for (int i = 0; i < 10; i++) {
        SDL_Rect rect = { x + i, y + i, 20 - i * 2, 20 - i * 2 };
        SDL_RenderDrawRect(m_renderer, &rect);
    }

    SDL_Rect clip;
}

void cRender::set_animation(int nAimation, int framesPerClip, int numberOfClips, int clipWidth, int clipHeight)
{
    m_animations[nAimation].framesPerClip = framesPerClip;
    m_animations[nAimation].numberOfClips = numberOfClips;
    m_animations[nAimation].clipWidth = clipWidth;
    m_animations[nAimation].clipHeigth = clipHeight;
}
