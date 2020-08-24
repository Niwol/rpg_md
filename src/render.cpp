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
    , m_nCurrentAnimation(0)
    , m_currentAnimation(NULL)
    , m_numberOfAnimations(0)
    , m_spriteSheet(window, renderer)
{
}

cRender::~cRender()
{
    for (int i = 0; i < m_numberOfAnimations; i++) {
        delete m_animations[i];
    }
}

bool cRender::load(SDL_Window* window, SDL_Renderer* renderer, std::string path)
{
    std::ifstream file;
    std::string line;

    int nbAnimations = 0;
    int currentHeight = 0;
    std::string pathToSpriteSheet;
    cTexture spriteSheet(window, renderer);

    file.open(path);
    if (file.is_open()) {

        // Searching the render informaitons in file
        while (!file.eof() && line != "< Render") {
            std::getline(file, line);
        }

        // Render informations found
        if (!file.eof()) {

            // Searching the path to the sprite sheet
            do {
                std::getline(file, line);
            } while (line == "" || line[0] == '#');

            pathToSpriteSheet = line;

            if (spriteSheet.loadFromFile(pathToSpriteSheet, true)) {

                // Searching the number of animations
                do {
                    std::getline(file, line);
                } while (line == "" || line[0] == '#');

                nbAnimations = atoi(line.c_str());
                m_numberOfAnimations = nbAnimations;

                // Searching start of animations informations
                do {
                    std::getline(file, line);
                } while (line == "" || line[0] == '#');

                // Setting the animations
                do {
                    SDL_Rect animationClip;

                    std::stringstream stream;

                    int framesPerClip;
                    int numberOfClips;
                    int clipWidth;
                    int clipHeigth;
                    int xOff;
                    int yOff;

                    stream << line;

                    stream >> framesPerClip >> numberOfClips >> clipWidth >> clipHeigth >> xOff >> yOff;

                    m_animations.push_back(new sAnimation(window, renderer, framesPerClip, numberOfClips, clipWidth, clipHeigth, xOff, yOff));

                    animationClip = { 0, currentHeight, clipWidth * numberOfClips, clipHeigth };
                    m_animations.back()->spriteSheet.createFromOtherTexture(spriteSheet, &animationClip);

                    currentHeight += clipHeigth;

                    std::getline(file, line);
                    nbAnimations--;
                } while (nbAnimations > 0);

            } else {

                printf("Could not load the sprite sheet!\n");
                file.close();
                return false;
            }

        } else {
            printf("No rendering informations in %s\n", path.c_str());
            file.close();
            return false;
        }

    } else {
        printf("Could not open %s\n", path.c_str());
        return false;
    }

    file.close();
    return true;
}

void cRender::render(int x, int y)
{
    if (m_currentAnimation->numberOfClips == 1) {
        m_currentAnimation->spriteSheet.render(x, y);
    } else {

        SDL_Rect clip = {
            (m_currentFrame / m_currentAnimation->framesPerClip) * m_currentAnimation->clipWidth,
            0,
            m_currentAnimation->clipWidth,
            m_currentAnimation->clipHeigth
        };

        m_currentAnimation->spriteSheet.render(x, y, &clip);
    }
}

void cRender::startAnimation(int nAnimation)
{
    m_nCurrentAnimation = nAnimation;
    m_currentAnimation = m_animations[nAnimation];
    m_currentFrame = 0;
}

void cRender::nextFrame()
{
    m_currentFrame++;

    if (m_currentFrame >= m_currentAnimation->framesPerClip * m_currentAnimation->numberOfClips)
        m_currentFrame = 0;
}

void cRender::set_animation(int nAimation, int framesPerClip, int numberOfClips, int clipWidth, int clipHeight)
{
    m_animations[nAimation]->framesPerClip = framesPerClip;
    m_animations[nAimation]->numberOfClips = numberOfClips;
    m_animations[nAimation]->clipWidth = clipWidth;
    m_animations[nAimation]->clipHeigth = clipHeight;
}
