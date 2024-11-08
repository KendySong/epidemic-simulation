#include "Sandbox.hpp"

Sandbox::Sandbox(sf::RenderTarget* render)
{
	p_render = render;

	m_backgroundTex.loadFromFile("../assets/img.jpg");
	m_background.setTexture(m_backgroundTex);
}

void Sandbox::handleSettings()
{
	//ImGui::Text("Data");
}

void Sandbox::update(float dt)
{

}

void Sandbox::render()
{
	p_render->draw(m_background);
}