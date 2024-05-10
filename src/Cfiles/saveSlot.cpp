#include "saveSlot.hpp"

saveSlot::saveSlot(float x, float y, SDL_Texture *texture, int h, int w, const char *font, RenderWindow **renderer, int id) : Entity(x, y, texture, h, w)
{
    this->renderer = *renderer;
    this->font = this->renderer->loadFont(font, 50);
    Savedstate = savedState::empty;
    state = ButtonState::normal;
    srcRect = {
        0,
        0,
        105, 90};
    this->texture = this->renderer->loadTexture("assets/ui/save.png");

    this->id = id;
    this->text = (std::string("Save Slot ") + std::to_string(id)).c_str();
}
saveSlot::saveSlot()
{
    this->renderer = NULL;
    this->text = NULL;
    this->font = NULL;
    state = ButtonState::normal;
}
saveSlot::~saveSlot()
{
}
bool saveSlot::handleEvents(SDL_Event event, bool flag, BlocksList *list)
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    if (x > position.getX() && x < position.getX() + destRect.w && y > position.getY() && y < position.getY() + destRect.h)
    {
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            state = ButtonState::Clicked;
            if (flag)
                saveTo(list);

            else
            {
                list->loadList("save" + std::to_string(id) + ".bin");
                if (Savedstate == savedState::saved)
                {
                    return true;
                }
            }
        }
        else
        {
            state = ButtonState::Hover;
        }
    }
    else
    {
        state = ButtonState::normal;
    }
    return false;
}
void saveSlot::update(int cycle, double deltaTime)
{
    switch (state)
    {
    case ButtonState::normal:

        break;
    case ButtonState::Hover:
        break;
    case ButtonState::Clicked:

        break;
    }
}
void saveSlot::render()
{
    renderer->render(this);
    renderSaveState();
}
savedState saveSlot::getState()
{
    return Savedstate;
}

const char *saveSlot::loadSaveState(savedState state)
{
    std::string filePath = "saves/save" + std::to_string(id) + ".bin";
    std::ifstream file(filePath, std::ios::in | std::ios::binary);
    if (file.good())
    {
        if (file.is_open())
        {
            int score;
            file.read(reinterpret_cast<char *>(&score), sizeof(int));
            file.close();
            Savedstate = savedState::saved;
            string text = "Score: " + std::to_string(score);
            return text.c_str();
        }
    }
    else
    {
        Savedstate = savedState::empty;
        return "Empty";
    }
}
void saveSlot::renderSaveState()
{
    const char *text = loadSaveState(Savedstate);
    renderer->renderText(text, font, (SDL_Color){255, 255, 255, 255}, position.getX() + 7, position.getY() + 18, 15, 35);
}
void saveSlot::saveTo(BlocksList *list)
{
    std::string filePath = "save" + std::to_string(id) + ".bin";
    list->saveList(filePath);
}
