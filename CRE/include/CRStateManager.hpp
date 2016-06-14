#ifndef CRSTATEMANAGER_HPP
#define CRSTATEMANAGER_HPP

#include <string>
#include <vector>
#include "CRTypes.hpp"

namespace CRE
{
    class StateManager
    {
        public:

            /////////////////////////////
            /* Public member functions */
            /////////////////////////////

            /**
            *
            */
            StateManager();

            /**
            *
            */
            virtual ~StateManager();

            /**
            *
            */
            void register_app(App * theApp);

            /**
            *
            */
            bool is_empty(void);

            /**
            *
            */
            void add_active_state(State * newState);

            /**
            *
            */
            void add_inactive_state(State * newState);

            /**
            *
            */
            State & get_active_state(void);

            /**
            *
            */
            void deactivate_active_state(void);

            /**
            *
            */
            void drop_active_state(void);

            /**
            *
            */
            void reset_active_state(void);

            /**
            *
            */
            void remove_active_state(void);

            /**
            *
            */
            void set_active_state(std::string stateID);

            /**
            *
            */
            void cleanup();

        private:

            //////////////////////////////
            /* Private member variables */
            //////////////////////////////

            // Pointer to the App class for error handling and logging
            App * _theApp;

            // Stack to store the current and previously active game states
            std::vector<State*> _activeStack;

            // Stack to store the dead states until they are properly cleaned
            std::vector<State*> _deadStack;

            //////////////////////////////
            /* Private member functions */
            //////////////////////////////

            /**
            * Copy constructor is private because we do not allow
            * copies of our class.
            */
            StateManager(const StateManager&); // intentionally undefined

            /**
            * Assignment operator is private because we do not allow
            * copies of our class.
            */
            StateManager & operator=(const StateManager&); // intentionally undefined

    }; // class StateManager
} // namespace CRE

#endif