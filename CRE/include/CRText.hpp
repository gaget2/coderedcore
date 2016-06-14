#ifndef CRTEXT_HPP
#define CRTEXT_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>

namespace CRE
{
	class Text
	{
		public:

			/**
			*
			*/
			Text(const std::string textID, std::string textString, const sf::Font& font,
					unsigned int charSize = 30) :
				_textID(textID),
				_text(textString, font, charSize)

			{}

			/**
			*
			*/
			std::string get_ID()
			{
				return _textID;
			}

			// The font used for this text
			sf::Font _textFont;

			// The actual text
			sf::Text _text;

		private:

			//////////////////////////////
            /* Private member variables */
            //////////////////////////////

            // The string identifier for this text
            const std::string _textID;

	};

}

#endif