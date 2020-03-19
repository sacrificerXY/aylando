#include <iostream>
#include <cmath>
#include <random>
#include <ctime>

#include <SFML/Graphics.hpp>

#include <imgui.h>
#include <imgui-SFML.h>

#include <FastNoise.h>

#include <aylando/game/World.h>

namespace ay = aylando;



float simplex(FastNoise &n, float x, float y, int octaves = 1)
{
    float value = 0;
    for (int i = 0; i < octaves; i++) {
        value += n.GetNoise(
            x * std::pow(2, i),
            y * std::pow(2, i)
        ) / 2 + 0.5;
    }
    // return value;
    return value / octaves;
}

int main()
{
    std::srand(std::time(nullptr));
    FastNoise myNoise;
    myNoise.SetSeed(std::rand());
    myNoise.SetNoiseType(FastNoise::Simplex);
    
    FastNoise n1;
    n1.SetSeed(std::rand());
    n1.SetNoiseType(FastNoise::Simplex);

    FastNoise n2;
    n2.SetSeed(std::rand());
    n2.SetNoiseType(FastNoise::Simplex);

    FastNoise n3;
    n3.SetSeed(std::rand());
    n3.SetNoiseType(FastNoise::Simplex);

    ay::game::World world;
    reset(world.tiles, 0);
    for (int x = 0; x < world.tiles.width; x++) {
        for (int y = 0; y < world.tiles.height; y++) {
            float xr = (float)x / world.tiles.width;
            float yr = 1 - (float)y / world.tiles.height;
            auto plateau = 0.f;
            if (yr <= 0.8) plateau = 1;
            else if (0.8 < yr && yr < 0.9) plateau = 1 - (yr - 0.8) * 10;

            auto center = 0.1 / (
                std::pow((xr - 0.5) * 1.5, 2) +
                std::pow((yr - 1) * 0.8, 2)
            );
            

            float density = simplex(n2, x*3, y*3, 5);
            density *= center * plateau;
            density *= std::pow(
                simplex(n3, xr*3, yr*3) + 0.4, 1.8f
            );

            if (density > 0.5) {
                world.tiles(x, y) = 1;
                auto cave = std::pow(simplex(n1, x*8, y*8, 5) + 0.4, 2);
                if (cave < 0.5) {
                    world.tiles(x, y) = 2;
                }
            }
        }
    }
    for (int x = 0; x < world.tiles.width; x++) {
        for (int y = 1; y < world.tiles.height; y++) {
            if (world.tiles(x,y) == 1 && world.tiles(x, y-1) == 0) {
                world.tiles(x, y) = 3;
            }
        }
    }
    
    constexpr int screen_width = 800;
    constexpr int screen_height = 800;
    constexpr float tile_size = (float)screen_width / world.tiles.width;
    constexpr int tile_padding = 1;

    sf::RenderWindow window(sf::VideoMode(screen_width, screen_height), "aylando");
    ImGui::SFML::Init(window);

    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(tile_size, tile_size));
    // rect.setSize(sf::Vector2f(tile_size - 2 * tile_padding, tile_size - 2 * tile_padding));
    // rect.setOutlineColor(sf::Color(0, 255, 0, 50));
    // rect.setOutlineThickness(0);

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
                    rect.setFillColor(sf::Color::Black);
                }
                else if (world.tiles(x, y) == 2) {
                    rect.setFillColor(sf::Color(220, 220, 220));
                }
                else if (world.tiles(x, y) == 3) {
                    rect.setFillColor(sf::Color(30, 180, 30));
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