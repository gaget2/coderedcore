#include "CRApp.hpp"
#include "CRState.hpp"
#include "CRConstants.hpp"

namespace CRE
{
	// Single instance of the most recently created App class
	App * App::_gApp = NULL;

	
	App::App(const std::string windowTitle, int windowWidth, int windowHeight) :
		_windowTitle(windowTitle),
		_windowWidth(windowWidth),
		_windowHeight(windowHeight),
		_window(),
		_stateManager(),
		_maxUpdates(5),
		_exitCode(0),
		_updateRate((uint32_t)(1000.0f / 60.0f)), // 60 updates per second
		_running(false)
	{
		_gApp = this;
	}

	App::~App()
	{
		// Make sure our running flag is false
		_running = false;

		// Remove static pointer if going out of scope
		if( _gApp == this ) _gApp = NULL;
	}

	App * App::get_app(void)
	{
		return _gApp;
	}

	int App::run(void)
	{
		// First set the running flag
		_running = true;

		// Link the app pointer to the state manager
		_stateManager.register_app(this);

		// Give derived class a time to register custom AssetHandlers
		init_asset_handlers();

		// Create window
		init_renderer();

		// Give derived app a chance to register ScreenFactory class
		init_screen_factory();

		// gameloopdedoo
		game_loop();

		// Give derived app a chance to cleanup
		handle_cleanup();

		// Perform our own internal cleanup
		cleanup();

		// Set running flag before exiting
		_running = false;

		// Return exit code
		return _exitCode;
	}

	bool App::is_running(void) const
	{
		return _running;
	}

	float App::get_update_rate(void) const
	{
		return (1000.0f / (float)_updateRate);
	}

	void App::set_update_rate(float newRate)
	{
		if( 200.0f >= newRate and 1.0f <= newRate )
			_updateRate = (uint32_t)(1000.0f / newRate);
	}

	void App::set_max_updates(uint32_t maxUpdates)
	{
		if( 200 >= maxUpdates and 1 <= maxUpdates )
			_maxUpdates = maxUpdates;
	}

	void App::quit(int theExitCode)
	{
		_exitCode = theExitCode;
		_running = false;
	}

	void App::init_renderer(void)
	{
		// Create window
		_window.create(sf::VideoMode(_windowWidth, _windowHeight), _windowTitle);

		// Use vertical sync
		_window.setVerticalSyncEnabled(true);

	}

	
	void App::game_loop(void)
	{
		// Clock used in restricting update loop to a fixed rate
		sf::Clock updateClock;

		// Clock used in calculating the time elapsed since the last frame
		sf::Clock frameClock;

		// Restart our update clock
		updateClock.restart();

		// When do we need to update next in milliseconds?
		sf::Int32 updateNext = updateClock.getElapsedTime().asMilliseconds();

		// Make sure we have at least one state active
		if( _stateManager.is_empty() )
			quit(STATUS_APP_INIT_FAILED);

		// Loop while the app is running
		while( is_running() and not _stateManager.is_empty() and _window.isOpen() )
		{
			// Get current active state
			State & aState = _stateManager.get_active_state();

			// Count the number of sequential update loop calls
			uint32_t updatesCount = 0;

			// Process any available input
			process_input(aState);

			// Make note of the current update time
			sf::Int32 updateTime = updateClock.getElapsedTime().asMilliseconds();

			// Process our update portion of the game loop
			while( (updateTime - updateNext) >= _updateRate and updatesCount++ < _maxUpdates)
			{
				// Let the current active state perform fixed updates
				aState.update();

				// Compute the next appropriate update time
				updateNext += _updateRate;

			} // while( (updateTime - updateNext) >= _updateRate and updatesCount++ < _maxUpdates)

			// Let the current active state perform its variable update
			aState.update_variable(frameClock.restart().asSeconds());

			// Let the current active state draw the items it needs to
			aState.draw();

			// Refresh the render window
			_window.display();

			// Give the state manager a chance to delete any pending states
			_stateManager.cleanup();

		}// while( is_running() and not _stateManager.is_empty() and _window.isOpen() )
	}

	void App::process_input(State & theState)
	{
		// The SFML event object used to process event
		sf::Event event;

		while(_window.pollEvent(event))
		{
			// Test event types
			switch(event.type)
			{
				case sf::Event::Closed:      // window closed
					quit(STATUS_OK);
					break;
				case sf::Event::GainedFocus: // window clicked on
					theState.resume();
					break;
				case sf::Event::LostFocus:   // window clicked off
					theState.pause();
				case sf::Event::Resized:     // window resized
					break;
				default:                     // current active state will handle
					theState.handle_events(event);

			} //switch(event.type)
		} //while(_window.pollEvent(event))
	}

	void App::cleanup(void)
	{
		// Close the render window if it is still open
		if( _window.isOpen() )
		{
			// Show mouse cursor if it was hidden
			_window.setMouseCursorVisible(true);

			// Close the render window
			_window.close();
		}
	}
} //namespace CRE
