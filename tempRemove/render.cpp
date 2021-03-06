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
    : m_window(window)
    , m_renderer(renderer)
    , m_pause(true)
    , m_currentFrame(0)
    , m_currentAnimation(NULL)
{
}

cRender::~cRender()
{
    /*while(!m_animations.empty()) {
        
    }*/
}

bool cRender::load(std::string path)
{
    std::ifstream file;
    std::string line;

    int nbAnimations = 0;
    int currentHeight = 0;
    std::string pathToSpriteSheet;
    cTexture spriteSheet(m_window, m_renderer);

    file.open(path);
    if (file.is_open()) {

        // Searching the render informaitons in file
        while (!file.eof() && line != "< Render") {
            std::getline(file, line);
        }

        // Render informations found
        if (!file.eof()) {

            while (line[0] != '>') {

                currentHeight = 0;

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

                    // Searching start of animations informations
                    do {
                        std::getline(file, line);
                    } while (line == "" || line[0] == '#');

                    // Setting the animations
                    do {
                        SDL_Rect animationClip;

                        std::stringstream stream;

                        sAnimation* newAimation = NULL;

                        int framesPerClip;
                        int numberOfClips;
                        int clipWidth;
                        int clipHeigth;
                        int xOff;
                        int yOff;
                        int enumKey;

                        stream << line;

                        stream >> framesPerClip >> numberOfClips >> clipWidth >> clipHeigth >> xOff >> yOff >> enumKey;

                        newAimation = new sAnimation(m_window, m_renderer, framesPerClip, numberOfClips, clipWidth, clipHeigth, xOff, yOff);

                        animationClip = { 0, currentHeight, clipWidth * numberOfClips, clipHeigth };
                        newAimation->spriteSheet.createFromOtherTexture(spriteSheet, &animationClip);

                        m_animations.insert(std::pair<int, sAnimation*>(enumKey, newAimation));

                        currentHeight += clipHeigth;

                        std::getline(file, line);
                        nbAnimations--;
                    } while (nbAnimations > 0);

                } else {

                    printf("Could not load the sprite sheet!\n");
                    file.close();
                    return false;
                }

                // Searching next info
                do {
                    std::getline(file, line);
                } while (line == "" || line[0] == '#');
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
    if (m_currentAnimation != NULL) {

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
}

void cRender::startAnimation(int animationKey)
{
    if (m_animations.count(animationKey)) {
        m_pause = false;
        m_currentAnimation = m_animations.at(animationKey);
        m_currentFrame = 0;
    } else {
        printf("Warning: this instance don't has %d animations!\n", animationKey);
    }
}

void cRender::restartAnimation()
{
    m_pause = false;
    m_currentFrame = 0;
}

void cRender::pauseAnimation(bool set)
{
    m_pause = set;
}

void cRender::stopAnimation()
{
    m_pause = true;
    m_currentFrame = 0;
    m_currentAnimation = NULL;
}

void cRender::nextFrame()
{
    if (m_pause == false) {

        m_currentFrame++;

        if (m_currentFrame >= m_currentAnimation->framesPerClip * m_currentAnimation->numberOfClips)
            m_currentFrame = 0;
    }
}

void cRender::set_animation(int nAimation, int framesPerClip, int numberOfClips, int clipWidth, int clipHeight)
{
    m_animations[nAimation]->framesPerClip = framesPerClip;
    m_animations[nAimation]->numberOfClips = numberOfClips;
    m_animations[nAimation]->clipWidth = clipWidth;
    m_animations[nAimation]->clipHeigth = clipHeight;
}
