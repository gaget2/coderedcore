#ifndef CRAPP_HPP // lol
#define CRAPP_HPP

#include <string.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "CRTypes.hpp"
#include "CRConstants.hpp"
#include "CRStateManager.hpp"

namespace CRE
{
    class App
    {
        public:
            ///////////////
            /* Variables */
            ///////////////

            // Title used for window
            std::string _windowTitle;

            // Dimensions for the render window
            int _windowWidth, _windowHeight;

            // Render window to draw to
            sf::RenderWindow _window;

            // State Manger for managing game states
            StateManager _stateManager;

            /////////////////////////////
            /* Public member functions */
            /////////////////////////////

            /**
            * App deconstructor
            */
            virtual ~App();

            /**
            * get_app will return the most recent App based class that was created
            * so it can be used to access the App interface for retrieving assets,
            * exiting the program, etc. NULL will be returned if none is available.
            */
            static App * get_app(void);

            /**
            * Run is called after the App is created and will call the init, loop, and
            * cleanup functions that are defined by the derived class.
            * @return the value of _exitCode as set by the quit function.
            */
            int run(void);

            /**
            * is_running will return true if the App is still running.
            * @return true if App is running, false otherwise
            */
            bool is_running(void) const;

            /**
            * get_update_rate will return the current game loop update rate being
            * used.
            * @return update rate in Hz (updates per second)
            */
            float get_update_rate(void) const;

            /**
            * set_update_rate will set the game loop update rate to a newRate
            * specified (from 1 Hz to 200 Hz, any other value outside this range
            * will not be accepted). The update rate is always fixed to provide
            * a deterministic game loop. But the actual updates per second is
            * affected by the performance of the system and the complexity of
            * the update game logic. Use set_max_updates to improve the frames
            * per second on lower performing systems.
            * @param[in] newRate in Hz (updates per second) range is [1,200]
            */
            void set_update_rate(float newRate);

            /**
            * set_max_updates will set the maximum number of sequential
            * updates allowed in any given game loop. If your frames per
            * second rate is struggling, you should set _maxUpdates to 1.
            * @param[in] maxUpdates range is [1,200]
            */
            void set_max_updates(uint32_t maxUpdates);

            /**
            * quit will signal the App to stop running.
            * @param[in] exitCode to use when the run function returns
            */
            void quit(int exitCode = STATUS_OK);

        protected:

            ////////////////////////////////
            /* Protected member functions */
            ////////////////////////////////

            /**
            * App constructor
            * @param[in] windowTitle is the title of the window
            * @param[in] windowWidth is the window width
            * @param[in] windowHeight is the window height
            */
            App(const std::string windowTitle = "CRE Application", int windowWidth = 800, int windowHeight = 600);

            /**
            * init_asset_handlers is responsible for registering custom AssetHandler
            * derived classes for a specific game application
            */
            virtual void init_asset_handlers(void) = 0;

            /**
            * init_screen_factory is responsible for initializing any Screen
            * derived classes with the ScreenManager class that will be used
            * to create new Screen derived classes as requested.
            */
            virtual void init_screen_factory(void) = 0;

            /**
            * game_loop is responsible for monitoring is_rinniong and exiting when
            * the App is done.
            */
            virtual void game_loop(void);

            /**
            * process_input is responsible for performing all input processing for the game loop
            */
            virtual void process_input(State& theState);

            /**
            * handle_cleanup is responsible for perfomring any custom last minute
            * App cleanup steps before exiting the App.
            */
            virtual void handle_cleanup(void) = 0;

        private:

            //////////////////////////////
            /* Private member variables */
            //////////////////////////////

            // Instance variable assigned at construction time
            static App * _gApp;

            // Maximum sequential update fixed calls
            uint32_t _maxUpdates;

            // The exit code value that will be returned by the app
            int _exitCode;

            // Update rate in seconds used to fix the update rate in gameloop
            sf::Int32 _updateRate;

            // Is the application running?
            bool _running;

            //////////////////////////////
            /* Private member functions */
            //////////////////////////////

            /**
            * init_renderer is responsible for initializing the RenderWindow
            * used by the App.
            */
            void init_renderer(void);

            /**
            * cleanup is responsible for perfomring any last minute App
            * cleanup steps before exiting the App
            */
            void cleanup(void);

            /**
            * App copy constructor is private because we do not allow copies
            * of our singleton class.
            */
            App(const App&); // intentionally undefined

            /**
            * App assignment operator is private because we do not allow copies
            * of our singleton class
            */
            App & operator=(const App&); // intentionally undefined
    }; // Class App
} // namespace CRE

#endif