#ifndef CRSTATE_HPP
#define CRSTATE_HPP

#include <string>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "CRTypes.hpp"

namespace CRE
{
    class State
    {
        public:

            /**
            *
            */
            State(const std::string stateID, App& theApp);

            /**
            *
            */
            virtual ~State();

            /**
            *
            */
            const std::string get_ID(void) const;

            /**
            *
            */
            virtual void init(void);

            /**
            *
            */
            virtual void reinit(void) = 0;

            /**
            *
            */
            void deinit(void);

            /**
            *
            */
            bool is_init_complete(void);

            /**
            *
            */
            bool is_paused(void);

            /**
            *
            */
            virtual void pause(void);

            /**
            *
            */
            virtual void resume(void);

            /**
            *
            */
            virtual void handle_events(sf::Event theEvent);

            /**
            *
            */
            virtual void update(void) = 0;

            /**
            *
            */
            virtual void update_variable(float elapsedTime) = 0;

            /**
            *
            */
            virtual void draw(void) = 0;

            /**
            *
            */
            void cleanup(void);

            /**
            *
            */
            float get_elapsed_time(void) const;

        protected:

            // The address to the App class
            App& _theApp;

            /**
            *
            */
            virtual void handle_cleanup(void) = 0;

        private:
            
            // The state ID
            const std::string _stateID;

            // Total time since init() was called
            float _elapsedTime;

            // Total time paused since init() was called
            float _pausedTime;

            // Clock will keep track of running and paused elapsed
            sf::Clock _elapsedClock;

            // Clock will keep track of time paused
            sf::Clock _pausedClock;

            // Bool that indicates that init() has been called
            bool _initialized;

            // State is currently paused
            bool _paused;

            // State needs to be cleaned up
            bool _cleanup;

            /**
            *
            */
            State(const State&); // intentionally undefined

            /**
            *
            */
            State & operator=(const State&); // intentionally undefined

    }; // class State
} // namespace CRE

#endif