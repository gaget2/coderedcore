#include "SplashState.hpp"
#include "CRApp.hpp"

namespace CRE
{
	SplashState::SplashState(App& theApp, const std::string filename, float delay) :
		State("SplashState", theApp),
		_splashFilename(filename),
		_splashDelay(delay)
	{
		_color = _splashSprite.getColor();
		_splashTexture.loadFromFile(_splashFilename);
		_splashSprite.setTexture(_splashTexture);
		_splashSprite.setPosition(0, 0);
	}

	SplashState::~SplashState(void)
	{}

	void SplashState::handle_events(sf::Event theEvent)
	{}

	void SplashState::init(void)
	{
		// Call base class init
		State::init();
	}

	void SplashState::reinit(void)
	{}

	void SplashState::update(void)
	{
		// Drop our state after the delay has elapsed
		if( not is_paused() and get_elapsed_time() > _splashDelay)
			_theApp._stateManager.remove_active_state();
	}

	void SplashState::update_variable(float theElapsedTime)
	{
		// Set alpha value for splash sprite
		// This is an equation for a parabola. No need to fully
		// understand it. The reason this is so fucking clunky
		// is that the parabola varies on the time of the splash delay.
		// y = a(x-h)^2 + k. Well this means that the values of a, h, and k
		// change depending on the delay set. After a little bit of algebra
		// it turns out that a = (255 * 4) / t^2 where t is the splash delay,
		// (h, k) is the vertex (we want the alpha to be its highest during
		// the middle of the delay), so h = t/2 and k = 255.
		_color.a = -1 * ((255 * 4) / (_splashDelay * _splashDelay))
					* (get_elapsed_time() - _splashDelay/2) * (get_elapsed_time() - _splashDelay/2)
					+255;

		_splashSprite.setColor(_color);
	}

	void SplashState::draw(void)
	{
		// Clear the screen with black so we can see the new changes
		// of our splash sprite
		_theApp._window.clear(sf::Color::Black);

		// Draw the splash sprite
		_theApp._window.draw(_splashSprite);

		// App core refreshes window for us
	}

	void SplashState::handle_cleanup(void)
	{}

} // namespace CRE