#include "CRTextManager.hpp"
#include "CRApp.hpp"

namespace CRE

{
	TextManager::TextManager() :
		_theApp(NULL),
		_texts(),
		_defaultFont()
	{}

	TextManager::~TextManager()
	{}

	void TextManager::register_app(App * theApp)
	{
		// Check that our pointer is good
        assert(NULL != theApp and "TextManager::register_app() theApp pointer provided is bad");

        // Make a note of the pointer
        assert(NULL == _theApp and "TextManager::register_app() theApp pointer was already registered");

        _theApp = theApp;
	}

	void TextManager::set_font(std::string fontResource)
	{
		if( not _defaultFont.loadFromFile(fontResource) )
			_theApp->quit(STATUS_FONT_COULDNT_BE_LOADED);
	}

	void TextManager::add_text(std::string textID, std::string textString, sf::Vector2f coordinate)
	{

	}

	void TextManager::add_text(std::string textID, std::string textString, sf::Font theFont, 
				sf::Vector2f coordinate)
	{

	}

	void TextManager::draw_all_texts()
	{
		for( CRE::Text text : _texts )
			_theApp->_window.draw(text._text);
	}

	void TextManager::draw_text(std::string textID)
	{

	}

	void TextManager::draw_text(std::string textID, sf::Vector2f coordinate)
	{

	}

	void TextManager::remove_text(std::string textID)
	{

	}

	bool TextManager::is_empty()
	{
		return _texts.empty();
	}

	sf::Text* TextManager::get_text(std::string textID)
	{

	}
}