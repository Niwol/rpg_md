#include "texture.hpp"

cTexture::cTexture(SDL_Window* window, SDL_Renderer* renderer)
    : m_texture(NULL)
    , m_pixels(NULL)
    , m_pitch(0)
    , m_format(SDL_PIXELFORMAT_RGBA8888)
    , m_alpha(false)
    , m_width(0)
    , m_height(0)
    , m_renderer(renderer)
    , m_window(window)
{
}

cTexture::~cTexture()
{
    free();
}

void cTexture::free()
{
    if (m_texture) {
        SDL_DestroyTexture(m_texture);
        m_texture = NULL;

        m_width = 0;
        m_height = 0;
    }
}

bool cTexture::loadFromFile(std::string path, bool alpha)
{
    free();

    SDL_Texture* newTexture = NULL;

    // Load surface
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        printf("Clould not load %s! IMG_ERROR: %s\n", path.c_str(), IMG_GetError());
        return false;
    }

    // Convert to display format
    SDL_Surface* formatedSurface = SDL_ConvertSurfaceFormat(loadedSurface, m_format, 0);
    if (formatedSurface == NULL) {
        printf("Could not convert surface to display format! SDL_ERROR: %s\n", SDL_GetError());

        SDL_FreeSurface(loadedSurface);

        return 0;
    }

    // Create blank texture
    newTexture = SDL_CreateTexture(m_renderer, m_format, SDL_TEXTUREACCESS_STREAMING, formatedSurface->w, formatedSurface->h);
    if (newTexture == NULL) {
        printf("Could not create blank texture! SDL_ERROR: %s\n", SDL_GetError());

        SDL_FreeSurface(loadedSurface);
        SDL_FreeSurface(formatedSurface);

        return false;
    }

    // Fill texture
    SDL_LockTexture(newTexture, NULL, (void**)&m_pixels, &m_pitch);
    memcpy(m_pixels, formatedSurface->pixels, formatedSurface->pitch * formatedSurface->h);
    SDL_UnlockTexture(newTexture);
    m_pixels = NULL;

    if (alpha)
        SDL_SetTextureBlendMode(newTexture, SDL_BLENDMODE_BLEND);

    m_width = formatedSurface->w;
    m_height = formatedSurface->h;
    m_alpha = alpha;
    m_texture = newTexture;

    SDL_FreeSurface(loadedSurface);
    SDL_FreeSurface(formatedSurface);

    return true;
}

bool cTexture::createFromOtherTexture(cTexture& otherTexture, SDL_Rect* clip)
{
    SDL_Texture* newTexture;

    m_format = otherTexture.m_format;

    // Check if the clip is not out of bounce
    if (clip != NULL && (clip->x < 0 || clip->x + clip->w > otherTexture.get_width() || clip->y < 0 || clip->y + clip->h > otherTexture.get_height())) {
        printf("ERROR: clip goes out of bounce of the texture!\n");
    } else {

        if (clip == NULL) {
            newTexture = SDL_CreateTexture(m_renderer, m_format, SDL_TEXTUREACCESS_STREAMING, otherTexture.get_width(), otherTexture.get_height());
        } else {
            newTexture = SDL_CreateTexture(m_renderer, m_format, SDL_TEXTUREACCESS_STREAMING, clip->w, clip->h);
        }

        // Check if texture is succesfully allocated
        if (newTexture == NULL) {
            printf("Could not create new texture! SDL_ERROR: %s\n", SDL_GetError());
        } else {

            // Copying the pixels to the new texture
            otherTexture.lockTexture();
            SDL_LockTexture(newTexture, NULL, (void**)&m_pixels, &m_pitch);

            if (clip == NULL)
                memcpy(m_pixels, otherTexture.get_Pixels(), otherTexture.get_Pitch() * otherTexture.get_height());
            else {
                Uint32* pixels = otherTexture.get_Pixels();

                for (int i = 0; i < clip->h; i++) {
                    for (int j = 0; j < clip->w; j++) {
                        m_pixels[i * clip->w + j] = pixels[(clip->y + i) * otherTexture.get_width() + clip->x + j];
                    }
                }
            }

            SDL_UnlockTexture(newTexture);
            otherTexture.unlockTexture();

            m_pixels = NULL;

            // Setting the other variables
            m_width = clip == NULL ? otherTexture.get_width() : clip->w;
            m_height = clip == NULL ? otherTexture.get_height() : clip->h;

            m_alpha = otherTexture.m_alpha;

            if (m_alpha)
                SDL_SetTextureBlendMode(newTexture, SDL_BLENDMODE_BLEND);

            m_texture = newTexture;
        }
    }

    return m_texture != NULL;
}

void cTexture::render(int x, int y, SDL_Rect* clip)
{
    SDL_Rect renderQuad = { x, y, m_width, m_height };

    if (clip != NULL) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopy(m_renderer, m_texture, clip, &renderQuad);
}

bool cTexture::lockTexture(SDL_Rect* clip)
{
    if (m_pixels != NULL) {
        printf("Texture is already locked!\n");
        return false;
    }

    if (SDL_LockTexture(m_texture, clip, (void**)&m_pixels, &m_pitch) != 0) {
        printf("Could not lock the texture! SDL_ERROR: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

bool cTexture::unlockTexture()
{
    if (m_pixels == NULL) {
        printf("Texture is not locked!\n");
        return false;
    }

    SDL_UnlockTexture(m_texture);
    m_pixels = NULL;
    m_pitch = 0;

    return true;
}

int cTexture::get_width() { return m_width; }
int cTexture::get_height() { return m_height; }

Uint32* cTexture::get_Pixels() { return m_pixels; }
int cTexture::get_Pitch() { return m_pitch; }
