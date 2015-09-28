/*
file: floating_frame.cpp
*/

#include "floating_frame.h"

const MATH::Vector2 FloatingFrame::innerVertices[] = {
	MATH::Vector2(140, 60), MATH::Vector2(1140, 60),
	MATH::Vector2(1140, 660), MATH::Vector2(140, 660)
};

FloatingFrame::FloatingFrame(void) {
	MATH::Vector2 frameCenter(640, 360);
	for(int i = 0; i < 4; ++i) {
		_floatingVertices[i].direction =
			MATH::Normalize(innerVertices[i] - frameCenter);
		float rand = sf::Randomizer::Random(10.0f, 20.0f);
		_floatingVertices[i].velocity = rand;
		_floatingVertices[i].distance = 0.0f;
	}
}

void FloatingFrame::Move(float secsPassed) {
	for(int i = 0; i < 4; ++i) {
		_floatingVertices[i].distance +=
			_floatingVertices[i].velocity * secsPassed;
		float dist = _floatingVertices[i].distance;
		float vel = _floatingVertices[i].velocity;
		if(0.0f > dist && 0.0f > vel) {
			_floatingVertices[i].velocity = sf::Randomizer::Random(10.0f, 20.0f);
		}
		if(30.0f < dist && 0.0f < vel) {
			_floatingVertices[i].velocity = sf::Randomizer::Random(-20.0f, -10.0f);
		}
	}
}

void FloatingFrame::Draw(sf::RenderTarget& renderTarget) {
	sf::Shape innerFrame = sf::Shape::Rectangle(
		innerVertices[UPPER_LEFT].sfVec(),
		innerVertices[LOWER_RIGHT].sfVec(),
		sf::Color(0, 0, 0, 70));
	renderTarget.Draw(innerFrame);

	for(int i = 0; i < 4; ++i) {
		sf::Shape polygon;

		int j = i + 1 > 3 ? 0 : i + 1;

		MATH::Vector2 floatingVertex0 = innerVertices[i] + 
			_floatingVertices[i].direction * _floatingVertices[i].distance;
		MATH::Vector2 floatingVertex1 = innerVertices[j] +
			_floatingVertices[j].direction * _floatingVertices[j].distance;

		polygon.AddPoint(innerVertices[i].sfVec());
		polygon.AddPoint(innerVertices[j].sfVec());
		polygon.AddPoint(floatingVertex1.sfVec());
		polygon.AddPoint(floatingVertex0.sfVec());

		if(i < 2) polygon.SetColor(sf::Color(100, 100, 100));
		else polygon.SetColor(sf::Color(150, 150, 150));
		polygon.SetBlendMode(sf::Blend::Multiply);
		renderTarget.Draw(polygon);
	}
}