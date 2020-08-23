#include "render.hpp"

sAnimation::sAnimation(SDL_Window* window, SDL_Renderer* renderer, int framesPerClip, int numberOfClips, int clipWidth, int clipHeight, int xOff, int yOff)
    : framesPerClip(framesPerClip)
    , numberOfClips(numberOfClips)
    , clipWidth(clipWidth)
    , clipHeigth(clipHeight)
    , xOff(xOff)
    , yOff(yOff)
    , spriteSheet(window, renderer)
{
}

cRender::cRender(SDL_Window* window, SDL_Renderer* renderer)
    : m_renderer(renderer)
    , m_currentFrame(0)
    , m_numberOfAnimations(0)
    , m_spriteSheet(window, renderer)
{
}

cRender::~cRender()
{
}

bool cRender::load(SDL_Window* window, SDL_Renderer* renderer, std::string path)
{
    std::ifstream file;
    std::string line;

    int nbAnimations = 0;

    file.open(path);
    if (file.is_open()) {

        // Searching the render informaitons in file
        while (!file.eof() && line != "< Render") {
            std::getline(file, line);
        }

        // Render informations found
        if (!file.eof()) {

            // Serching first info
            do {
                std::getline(file, line);
            } while (line == "" || line[0] == '#');

            printf("%s\n", line.c_str());

            nbAnimations = atoi(line.c_str());

            do {
                std::getline(file, line);
            } while (line == "" || line[0] == '#');

            do {
                std::stringstream stream;

                int framesPerClip;
                int numberOfClips;
                int clipWidth;
                int clipHeigth;
                int xOff;
                int yOff;

                cTexture spriteSheet(window, renderer);

                stream << line;

                stream >> framesPerClip >> numberOfClips >> clipWidth >> clipHeigth >> xOff >> yOff;

                printf("%s\n", line.c_str());
                printf("fpc = %d ; nbClips = %d ; clipW = %d ; clipH = %d ; xOff = %d ; yOff = %d\n\n", framesPerClip, numberOfClips, clipWidth, clipHeigth, xOff, yOff);

                m_animations.push_back(new sAnimation(window, renderer, framesPerClip, numberOfClips, clipWidth, clipHeigth, xOff, yOff));

                std::getline(file, line);
                nbAnimations--;
            } while (nbAnimations > 0);

            printf("nbAnimations = %d\n", nbAnimations);
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

    //SDL_Rect clip;
}

void cRender::set_animation(int nAimation, int framesPerClip, int numberOfClips, int clipWidth, int clipHeight)
{
    m_animations[nAimation]->framesPerClip = framesPerClip;
    m_animations[nAimation]->numberOfClips = numberOfClips;
    m_animations[nAimation]->clipWidth = clipWidth;
    m_animations[nAimation]->clipHeigth = clipHeight;
}
