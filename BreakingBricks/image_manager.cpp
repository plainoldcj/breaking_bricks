/*
file: image_manager.cpp
*/

#include "log.h"
#include "image_manager.h"

sf::Sprite ImageManager::CreateSprite(const std::string& filename, const sf::Vector2f& position,
									  const sf::Vector2f& scale, float rotation, const sf::Color& color) 
{
	imageMapIt_t imageMapIt(_images.find(filename));
	if(_images.end() == imageMapIt) {
		sf::Image image;
		if(!image.LoadFromFile(filename)) {
			Log::Instance().Error() << "unable to load image " << filename;
			throw std::exception("unable to load image");
		}
		_images[filename] = image;
		imageMapIt = _images.find(filename);
	}
	return sf::Sprite(imageMapIt->second, position, scale, rotation, color);
}