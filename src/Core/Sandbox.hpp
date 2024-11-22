#pragma once
#include <SFML/Graphics.hpp>

#include <ImGui/imgui.h>
#include <ImGui/imgui-SFML.h>

#include "Camera.hpp"

class Sandbox
{
public :
	Sandbox(sf::RenderWindow* window);
	void handleSettings();
	void update(float dt);
	void render();

	Camera camera;

private :
	sf::RenderWindow* p_window;

	sf::Sprite m_background;
	sf::Texture m_backgroundTex;

};