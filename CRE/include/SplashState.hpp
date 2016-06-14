#ifndef SPLASHSTATE_HPP
#define SPLASHSTATE_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include "CRState.hpp"
#include "CRTypes.hpp"

namespace CRE
{
	class SplashState : public State
	{
		public:

			/**
			*
			*/
			SplashState(App& theApp, const std::string filename = "resources/splash.png", 
				float delay = 5.0f);

			/**
			*
			*/
			virtual ~SplashState();

			/**
			*
			*/
			virtual void init(void);

			/**
			*
			*/
			virtual void reinit(void);

			/**
			*
			*/
			virtual void handle_events(sf::Event theEvent);

			/**
			*
			*/
			virtual void update(void);

			/**
			*
			*/
			virtual void update_variable(float theElapsedTime);

			/**
			*
			*/
			virtual void draw(void);
		protected:

			/**
			*
			*/
			virtual void handle_cleanup(void);

		private:

			std::string _splashFilename;

			sf::Texture _splashTexture;

			sf::Sprite _splashSprite;

			sf::Color _color;

			float _splashDelay;
	};
}

#endif