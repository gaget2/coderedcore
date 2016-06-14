#include "SplashState.hpp"
#include "CRApp.hpp"

namespace CRE
{
	SplashState::SplashState(App& theApp, const std::string filename, float delay) :
		State("SplashState", theApp),
		_splashFilename(filename),
		_splashDelay(delay),
		_frameCount(0)
	{
		_color = _splashSprite.getColor();
		_splashTexture.loadFromFile(_splashFilename);
		_splashSprite.setTexture(_splashTexture);
		_splashSprite.setPosition(0, 0);

		_parabolaAlphaOffsetX = int(theApp.get_update_rate() * _splashDelay);
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
		// understand it
		_color.a = (-1 * (_frameCount - _parabolaAlphaOffsetX / 2) * 
			(_frameCount - _parabolaAlphaOffsetX / 2) / 90) + 255;

		_splashSprite.setColor(_color);

		_frameCount++;
	}

	void SplashState::draw(void)
	{
		// Clear the screen with black so we can see the new changes
		// of our splash sprite
		_theApp._window.clear(sf::Color::Black);

		// Draw the splash sprite
		_theApp._window.draw(_splashSprite);
	}

	void SplashState::handle_cleanup(void)
	{}

} // namespace CRE