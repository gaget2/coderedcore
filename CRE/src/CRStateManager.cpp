
#include <assert.h>
#include <stddef.h>
#include "CRConstants.hpp"
#include "CRStateManager.hpp"
#include "CRApp.hpp"
#include "CRState.hpp"

namespace CRE
{

    StateManager::StateManager() :
        _theApp(NULL)
    {

    }

    StateManager::~StateManager()
    {
        // Drop all active states
        while( not _activeStack.empty() )
        {
            State * aState = _activeStack.back();

            _activeStack.pop_back();

            aState->pause();

            aState->deinit();

            aState->cleanup();

            delete aState;

            aState = NULL;
        }

        // Delete all our dropped states
        while( not _deadStack.empty() )
        {
            State * aState = _deadStack.back();

            _deadStack.pop_back();

            aState->pause();

            aState->deinit();

            aState->cleanup();

            delete aState;

            aState = NULL;
        }

        _theApp = NULL;
    }

    void StateManager::register_app( App * theApp )
    {
        // Check that our pointer is good
        assert(NULL != theApp and "StateManager::register_app() theApp pointer provided is bad");

        // Make a note of the pointer
        assert(NULL == _theApp and "StateManager::register_app() theApp pointer was already registered");

        _theApp = theApp;
    }

    bool StateManager::is_empty(void)
    {
        return _activeStack.empty();
    }

    void StateManager::add_active_state(State * theState)
    {
        if( not _activeStack.empty() )
            _activeStack.back()->pause();

        _activeStack.push_back(theState);

        _activeStack.back()->init();
    }

    void StateManager::add_inactive_state(State * theState)
    {
        _activeStack.insert(_activeStack.begin(), theState);
    }

    State& StateManager::get_active_state(void)
    {
        return *_activeStack.back();
    }

    void StateManager::deactivate_active_state(void)
    {
        if( not _activeStack.empty() )
        {
            State * aState = _activeStack.back();

            aState->pause();

            _activeStack.pop_back();

            _activeStack.insert(_activeStack.begin(), aState);

            aState = NULL;
        }
        else
        {
            if(NULL != _theApp)
                _theApp->quit(STATUS_APP_STACK_EMPTY);

            return;
        }

        // Is there another state to activate? Then call resume to activate it
        if( not _activeStack.empty() )
        {
            // Has the state ever been initialized?
            if( _activeStack.back()->is_init_complete() )
                _activeStack.back()->resume();
            else
                _activeStack.back()->init();
        }
        else
        {
            // There are no states on the stack, exit the program
            if( NULL != _theApp )
                _theApp->quit(STATUS_OK);
        }
    }

    void StateManager::drop_active_state(void)
    {
        if( not _activeStack.empty() )
        {
            State * aState = _activeStack.back();

            aState->pause();

            aState->deinit();

            _activeStack.pop_back();

            _activeStack.insert(_activeStack.begin(), aState);

            aState = NULL;
        }
        else
        {
            if( NULL != _theApp )
                _theApp->quit(STATUS_APP_STACK_EMPTY);

            return;
        }

        // is there another stack to activate?
        if( not _activeStack.empty() )
        {
            // Has that state ever been initialized?
            if( _activeStack.back()->is_init_complete() )
                _activeStack.back()->resume();
            else
                _activeStack.back()->init();
        }
        else
        {
            if( NULL != _theApp )
                _theApp->quit(STATUS_OK);
        }
    }

    void StateManager::reset_active_state(void)
    {
        if( not _activeStack.empty() )
        {
            State * aState = _activeStack.back();

            aState->pause();

            aState->reinit();

            aState->resume();

            aState = NULL;
        }
        else
        {
            if( NULL != _theApp )
                _theApp->quit(STATUS_APP_STACK_EMPTY);

            return;
        }
    }

    void StateManager::remove_active_state(void)
    {
        if( not _activeStack.empty() )
        {
            State * aState = _activeStack.back();

            aState->pause();

            aState->deinit();

            _activeStack.pop_back();

            _deadStack.push_back(aState);

            aState = NULL;
        }
        else
        {
            if( NULL != _theApp )
                _theApp->quit(STATUS_APP_STACK_EMPTY);

            return;
        }

        // is there another state to activate?
        if( not _activeStack.empty() )
        {
            // Has that state ever been initialized?
            if( _activeStack.back()->is_init_complete() )
                _activeStack.back()->resume();
            else
                _activeStack.back()->init();
        }
        else
        {
            if( NULL != _theApp )
                _theApp->quit(STATUS_OK);
        }
    }

    void StateManager::set_active_state(std::string theStateID)
    {
        // Iterator
        std::vector<State*>::iterator it;

        // Find the state that matches the stateID
        for( it = _activeStack.begin(); it < _activeStack.end(); it++ )
        {
            // Does this state match the ID? Then activate as the new
            // currently active state
            if( (*it)->get_ID() == theStateID )
            {
                // Get a pointer to soon to be currently active state
                State * aState = *it;

                // Remove this state from the stack
                _activeStack.erase(it);

                // Pause the currently active state
                if( not _activeStack.empty() )
                    _activeStack.back()->pause();

                // Add the found state to the top of the stack
                _activeStack.push_back(aState);

                // Remove pointer
                aState = NULL;

                // Has the new found state ever been initialized?
                if( _activeStack.back()->is_init_complete() )
                    _activeStack.back()->resume();
                else
                    _activeStack.back()->init();

                // Break loop
                break;
            } // if
        } //for
    }

    void StateManager::cleanup(void)
    {
        // Remove one of our dead states
        if( not _deadStack.empty() )
        {   
            // Retrieve the dead state
            State * aState = _deadStack.back();
            assert(NULL != aState and "StateManager::cleanup() invalid dropped state pointer");

            // Remove it from the dead stack
            _deadStack.pop_back();

            // Deinitialize the state if needed
            if( aState->is_init_complete() )
                aState->deinit();

            // Cleanup the state
            aState->cleanup();

            // Delete the state
            delete aState;

            // Nullify pointer
            aState = NULL;

        }

        // Quit the app if we have no more active States
        if( NULL == _activeStack.back() )
            if( NULL != _theApp )
                _theApp->quit(STATUS_OK);
    }
    
} //namespace CRE