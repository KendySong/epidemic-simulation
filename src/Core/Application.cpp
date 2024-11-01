#include <iostream>

#include <ImGui/imgui.h>
#include <ImGui/imgui-SFML.h>

#include "Application.hpp"
#include "../Settings.hpp"

Application* Application::s_app = nullptr;
Application::Application()
{
    p_window = new sf::RenderWindow(sf::VideoMode(Settings::instance.width, Settings::instance.height), "Epidemic simulation");
    ImGui::SFML::Init(*p_window);
}

Application* Application::instance() noexcept
{
    if (s_app == nullptr)
    {
        s_app = new Application();
    }
    return s_app;
}

int Application::run()
{
    while (p_window->isOpen())
    {
        while (p_window->pollEvent(m_event))
        {
            ImGui::SFML::ProcessEvent(*p_window, m_event);
            if (m_event.type == sf::Event::Closed)
            {
                ImGui::DestroyContext();
                p_window->close();
            }           
        }      

        m_deltaTime = m_deltaClock.restart();
        ImGui::SFML::Update(*p_window, m_deltaTime);

        p_window->clear();
        p_window->draw(m_sprite);

        ImGui::Begin("Settings");      
        ImGui::End();
        ImGui::SFML::Render(*p_window);

        p_window->display();
    }

    return 0;
}