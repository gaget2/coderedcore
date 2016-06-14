#include <assert.h>
#include "CRState.hpp"
#include "CRApp.hpp"
#include "CRConstants.hpp"

namespace CRE
{

    State::State(const std::string theStateID, App & theApp) :
        _theApp(theApp),
        _stateID(theStateID),
        _elapsedTime(0.0f),
        _pausedTime(0.0f),
        _elapsedClock(),
        _pausedClock(),
        _initialized(false),
        _paused(false),
        _cleanup(false)
    {}

    State::~State()
    {}

    const std::string State::get_ID(void) const
    {
        return _stateID;
    }

    void State::init(void)
    {
        // If cleanup hasn't yet been called, do it now
        if( _cleanup )
            handle_cleanup();

        // Initialize if necessary
        if( not _initialized )
        {
            _initialized = true;
            _paused = false;
            _elapsedTime = 0.0f;
            _elapsedClock.restart();
            _pausedClock.restart();
        }
    }

    void State::deinit(void)
    {
        if( _initialized )
        {
            _cleanup = true;
            _initialized = false;
            _elapsedTime += _elapsedClock.getElapsedTime().asSeconds();

            if( _paused )
                _pausedTime += _pausedClock.getElapsedTime().asSeconds();
        }
    }

    bool State::is_init_complete(void)
    {
        return _initialized;
    }

    bool State::is_paused(void)
    {
        return _paused;
    }

    void State::pause(void)
    {
        if( not _paused )
        {
            _paused = true;
            _pausedClock.restart();
        }

    }

    void State::resume()
    {
        if( _paused )
        {
            _paused = false;
            _pausedTime += _pausedClock.getElapsedTime().asSeconds();
        }
    }

    void State::handle_events(sf::Event theEvent)
    {
        // Exit the program if the window is closed
        if( theEvent.type == sf::Event::Closed )
            _theApp.quit(STATUS_OK);
    }

    float State::get_elapsed_time(void) const
    {
        float result = _elapsedClock.getElapsedTime().asSeconds();

        if( not _initialized)
            result = _elapsedTime;

        return result;
    }

    void State::cleanup(void)
    {
        // This will be true if this state is about to be deleted soon
        if( _cleanup )
        {
            // Call our handle cleanup virtual function
            handle_cleanup();

            _cleanup = false;
        }
    }
    
} // Namespace CRE