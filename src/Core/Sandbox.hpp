#pragma once
#include <SFML/Graphics.hpp>

#include <ImGui/imgui.h>
#include <ImGui/imgui-SFML.h>

class Sandbox
{
public :
	Sandbox(sf::RenderTarget* render);
	void handleSettings();
	void update(float dt);
	void render();

private :
	sf::RenderTarget* p_render;

	sf::Sprite m_background;
	sf::Texture m_backgroundTex;
};