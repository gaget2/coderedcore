/**
* Text Manager class handles all the text for the game.
* @author Jake Shepherd
* @date 06/13/16
*/

#ifndef CRTEXTMANAGER_HPP
#define CRTEXTMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>
#include <vector>
#include <assert.h>
#include "CRTypes.hpp"
#include "CRText.hpp"
#include "CRConstants.hpp"

namespace CRE
{
	class TextManager
	{
		public:

			/////////////////////////////
            /* Public member functions */
            /////////////////////////////

			/**
			* Default constructor for the TextManager class. Sets theApp pointer to null.
			*/
			TextManager();

			/**
			* Deconstructor for the TextManager class.
			*/
			virtual ~TextManager();

			/**
			* Sets theApp pointer so the TextManager can reference the App.
			*/
			void register_app(App * theApp);

			/**
			* Sets the default font from a supplied path to the resource.
			*/
			void set_font(std::string fontResource);

			/**
			* Creates a new text object at a specified location. Uses the default font.
			*/
			void add_text(std::string textID, std::string textString, sf::Vector2f coordinate, unsigned int charSize = 30);

			/**
			* Creates a new text object like the function above, but uses a supplied font
			* instead of the default font.
			*/
			void add_text(std::string textID, std::string textString, sf::Font theFont, 
				sf::Vector2f coordinate, unsigned int charSize = 30);

			/**
			* Draws all the texts to the App window.
			*/
			void draw_all_texts();

			/**
			* Draws only the text supplied by the string identifier.
			*/
			void draw_text(std::string textID);

			/**
			* Draws only the text supplied by the string identifier and draws it
			* at the specified coordinate.
			*/
			void draw_text(std::string textID, sf::Vector2f coordinate);

			/**
			* Removes the text supplied by the string identifier from the texts vector.
			*/
			void remove_text(std::string textID);

			/**
			* Returns true if there are no texts
			*/
			bool is_empty();

			/**
			* Returns a text by reference specified by the ID in case the text item
			* needs to be modified in some way.
			*/
			sf::Text* get_text(std::string textID);

		private:

			//////////////////////////////
            /* Private member variables */
            //////////////////////////////

            // Pointer to the app class for error handling and logging
			App * _theApp;

			// Vector stores the texts
			std::vector<CRE::Text *> _texts;

			// The default font all new texts will used unless specified otherwise
			sf::Font _defaultFont;

			//////////////////////////////
            /* Private member functions */
            //////////////////////////////

            /**
            * Copy constructor is private because we do not allow
            * copies of our class.
            */
            TextManager(const TextManager&); // intentionally undefined

            /**
            * Assignment operator is private because we do not allow
            * copies of our class.
            */
            TextManager & operator=(const TextManager&); // intentionally undefined

	};
}

#endif