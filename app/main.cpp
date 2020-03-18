#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include <imgui.h>
#include <imgui-SFML.h>

#include <aylando/utils/Array2d.h>

namespace ay = aylando;

int main()
{
    ay::utils::Array2d<int, 10, 10> arr;
    reset(arr);
    arr(0, 0) = 123;
    for (int x = 0; x < arr.width; x++) {
        for (int y = 0; y < arr.height; y++) {
            std::cout << x << ',' << y << " = " << arr(x, y) << '\n';
        }
    }
    sf::RenderWindow window(sf::VideoMode(640, 480), "ImGui + SFML = <3");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    sf::CircleShape shape(100);
    shape.setFillColor(sf::Color::Green);

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
        window.draw(shape);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}