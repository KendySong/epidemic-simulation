#include <iostream>

#include <ImGui/imgui.h>
#include <ImGui/imgui-SFML.h>

#include "Application.hpp"
#include "../Settings.hpp"

Application* Application::s_app = nullptr;
Application::Application()
{
    p_window = new sf::RenderWindow(sf::VideoMode(Settings::width, Settings::height), "Epidemic simulation");
    ImGui::SFML::Init(*p_window);
    p_sandbox = new Sandbox(p_window);
    m_fpsDisplay = 0;
    m_fps = 0;  
    m_zoomFactor = 0;
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
        //Events
        while (p_window->pollEvent(m_event))
        {
            ImGui::SFML::ProcessEvent(*p_window, m_event);
            switch (m_event.type)
            {
            case sf::Event::Closed:
                p_window->close();
                break;

            case sf::Event::MouseWheelMoved:
                m_zoomFactor = 1 - m_event.mouseWheel.delta * 0.1;
                Settings::zoom *= m_zoomFactor;
                Settings::sensitivity = Settings::base_zoom * Settings::zoom;
                p_sandbox->camera.view.zoom(m_zoomFactor);
                break;
            }
        }

        //Deltatime & FPS
        m_fps++;
        m_deltaTime = m_deltaClock.restart();
        ImGui::SFML::Update(*p_window, m_deltaTime);
        p_sandbox->update(m_deltaTime.asSeconds());
        if (m_fpsClock.getElapsedTime().asSeconds() >= 1)
        {
            m_fpsDisplay = m_fps;
            m_fps = 0;
            m_fpsClock.restart();
        }

        //Render
        p_window->clear(Settings::clear_color);
        p_sandbox->render();

        ImGui::Begin("Settings");
        ImGui::Text("FPS : %i", m_fpsDisplay);
        p_sandbox->handleSettings();
        ImGui::End();

        ImGui::SFML::Render(*p_window);
        p_window->display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}