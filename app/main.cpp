#include <iostream>

#include <SFML/Graphics.hpp>

#include <imgui.h>
#include <imgui-SFML.h>

#include <aylando/game/World.h>

namespace ay = aylando;

int main()
{
    constexpr int tile_size = 16;
    constexpr int tile_padding = 1;
    ay::game::World world;
    reset(world.tiles);
    world.tiles(0, 0) = 3232;
    int screen_width = world.tiles.width * tile_size;
    int screen_height = world.tiles.height * tile_size;

    sf::RenderWindow window(sf::VideoMode(screen_width, screen_height), "aylando");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(tile_size - 2 * tile_padding, tile_size - 2 * tile_padding));
    rect.setOutlineColor(sf::Color::Green);
    rect.setOutlineThickness(tile_padding);

    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Sample Project");
        ImGui::Button("Click Me!");
        ImGui::End();

        window.clear();

        for (int x = 0; x < world.tiles.width; x++) {
            for (int y = 0; y < world.tiles.height; y++) {
                rect.setPosition(x * tile_size, y * tile_size);
                if (world.tiles(x, y) == 0) {
                    rect.setFillColor(sf::Color::White);
                }
                else if (world.tiles(x, y) == 1) {
                    rect.setFillColor(sf::Color::White);
                }
                else {
                    rect.setFillColor(sf::Color::Magenta);
                }
                window.draw(rect);
            }
        }
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}