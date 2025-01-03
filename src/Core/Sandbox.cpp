#include <iostream>

#include "Sandbox.hpp"
#include "../Settings.hpp"
#include "../Simulation/Math.hpp"

Sandbox::Sandbox(sf::RenderWindow* window)
{
	p_window = window;
	//m_backgroundTex.loadFromFile("../assets/img.jpg");
	//m_background.setTexture(m_backgroundTex);
	camera = Camera(window);

	l1 = sf::VertexArray(sf::PrimitiveType::LineStrip, 2);
	l1[0] = sf::Vertex(sf::Vector2f(100, 100));
	l1[1] = sf::Vertex(sf::Vector2f(1000, 600));

	l2 = sf::VertexArray(sf::PrimitiveType::LineStrip, 2);
	coline = sf::RectangleShape(sf::Vector2f(20, 20));
	coline.setFillColor(sf::Color::Green);
}

void Sandbox::handleSettings()
{
	ImGui::Checkbox("DrawLine", &drawLine);
}

void Sandbox::update(float dt)
{
	if (!ImGui::GetIO().WantCaptureMouse)
	{
		camera.move();
	}	

	if (drawLine)
	{
		sf::Vector2f collisionPos;
		if (Math::lineIntersect(l1[0].position, l1[1].position, l2[0].position, l2[1].position, &collisionPos))
		{
			l2Color = sf::Color::Red;
			coline.setPosition(collisionPos);
		}
		else
		{
			l2Color = sf::Color::White;
		}

		l2[0] = sf::Vertex(sf::Vector2f(100, 600), l2Color);
		l2[1] = sf::Vertex(Math::toVec2f(sf::Mouse::getPosition(*p_window)), l2Color);
	}
	
	
}

void Sandbox::render()
{
	p_window->setView(camera.view);
	//p_window->draw(m_background);

	
	//p_window->draw(m_city.s);
	//p_window->draw(m_city.lines);

	for (size_t i = 0; i < m_city.building.size(); i++)
	{
		//p_window->draw(m_city.building[i].rect);
	}

	for (size_t i = 0; i < m_city.roads.size(); i++)
	{
		//p_window->draw(m_city.roads[i]);
	}

	if (drawLine)
	{
		p_window->draw(l1);
		p_window->draw(l2);
		p_window->draw(coline);		
	}
}