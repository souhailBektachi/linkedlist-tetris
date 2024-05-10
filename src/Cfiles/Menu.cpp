#include "Menu.hpp"

Menu::Menu(RenderWindow **renderer)
{
    this->renderer = *renderer;

    this->fonts[0] = this->renderer->loadFont(FONTS[0], 10);
    this->fonts[1] = this->renderer->loadFont(FONTS[1], 50);
    CreateMenu(this->renderer);
}

void Menu::handleEvents(SDL_Event event)
{
    for (int i = 0; i < 3; i++)
    {
        uiElements.buttons[i].handleEvents(event);
    }
}
void Menu::update(int cycle, double deltaTime)
{
    animateBackground(cycle, deltaTime);
    for (int i = 0; i < 3; i++)
    {
        uiElements.buttons[i].update(cycle, deltaTime);
    }
    this->deltaTime = deltaTime;
}
void Menu::render()
{
    renderer->clear();

    renderer->render(&uiElements.Background);
    // menuWindow.render();
    renderer->render(&uiElements.Logo);
    renderText();
    for (int i = 0; i < 3; i++)
    {
        uiElements.buttons[i].render();
    }
    // renderer->renderText("TETRIS", font, (SDL_Color){255, 255, 255, 255}, 205, 40);

    renderer->display();
}
void Menu::renderText()
{
    renderer->renderText("TETRIS", fonts[1], (SDL_Color){253, 226, 148, 255}, 223, 80, 35, 165);
}

void Menu::animateBackground(int cycle, double deltaTime)
{
    int x = uiElements.Background.getSrcRect().x;
    static int sign = 1;
    if (x >= 5120 / 2)
    {
        sign = -1;
    }
    else if (x <= 0)
    {
        sign = 1;
    }
    if (cycle % 2)
    {
        uiElements.Background.setSrcRect((SDL_Rect){
            x + (200 * deltaTime * sign),
            600,
            5120 / 2,
            2880 - 1000});
    }
}
void Menu::CreateMenu(RenderWindow *renderer)
{

    SDL_Texture *background = this->renderer->loadTexture("assets/ui/background.png");
    SDL_Texture *logo = this->renderer->loadTexture("assets/ui/menu.png");
    this->uiElements.Background = Entity(0, 0, background, SCREEN_HEIGHT, SCREEN_WIDTH);
    this->uiElements.Background.setSrcRect((SDL_Rect){
        0,
        650,
        5120 / 2,
        2880 - 1000});
    this->uiElements.Logo = Entity(152, 20, logo, SCREEN_HEIGHT - 50, SCREEN_WIDTH / 2);
    this->uiElements.Logo.setSrcRect((SDL_Rect){
        0,
        0,
        653,
        835});
    uiElements.buttons[0] = button(152 + 101, 20 + 128, nullptr, 40, 107, FONTS[1], &this->renderer, "Play");
    uiElements.buttons[1] = button(152 + 101, 20 + 211, nullptr, 40, 107, FONTS[1], &this->renderer, "Load");
    uiElements.buttons[2] = button(152 + 101, 20 + 323, nullptr, 40, 107, FONTS[1], &this->renderer, "Exit");
}
GameState Menu::buttonsEvents()
{
    if (uiElements.buttons[0].getState() == ButtonState::Clicked)
    {
        return GameState::Playing;
    }
    else if (uiElements.buttons[2].getState() == ButtonState::Clicked)
    {
        return GameState::Exit;
    }
    else if (uiElements.buttons[1].getState() == ButtonState::Clicked)
    {
        return GameState::Saves;
    }
    else
    {
        return GameState::MainMenu;
    }
}