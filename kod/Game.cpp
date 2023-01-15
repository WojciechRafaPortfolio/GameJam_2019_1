#include "Game.hpp"

#include "GameConfig.hpp"
#include "WindowEvents.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

// Global <GameConfig> config( [](){ return std::make_unique<GameConfig>( "conf.txt" ); } );

void warning(const std::string& messageStr){
    message( "Warning", "Warning:\n" + messageStr );
}

[[noreturn]] void fatalError(const std::string& messageStr){
    message( "FatalError", "FatalError:\n" + messageStr + "\nClosing program." );
    std::exit( EXIT_FAILURE );
}

void message(std::string windowName, const std::string& message){
    auto* text = new sf::Text; // dziwny błąd pojawia się przy bezpośrednim sf::Text
    // auto text = std::make_unique<sf::Text>();
    static auto font = []() -> std::unique_ptr<sf::Font>{
        auto font = std::make_unique<sf::Font>();
        if( !font->loadFromFile( "/usr/share/fonts/truetype/noto/NotoSans-Regular.ttf" ) )
            if( !font->loadFromFile( "font.ttf" ) )
                if( !font->loadFromFile( R"(C:\Windows\Fonts\arial.ttf)" ) )
                    return nullptr;
        return font;
    }();

    if( font == nullptr )
        windowName = message;

    sf::RenderWindow errorWindow( {500, 200}, windowName, sf::Style::Close );
    errorWindow.setFramerateLimit( 10 );

    text->setString( message );
    text->setFillColor( sf::Color::White );
    text->setFont( *font );
    text->setCharacterSize( 12 );

    while(text->getGlobalBounds().width>errorWindow.getSize().x)
        text->setCharacterSize(text->getCharacterSize()-1);

    while( errorWindow.isOpen() ){
        sf::Event event{};
        while( errorWindow.pollEvent( event ) )
            if( event.type == sf::Event::Closed )
                errorWindow.close();
        errorWindow.clear( sf::Color::Black );
        errorWindow.draw( *text );
        errorWindow.display();
    }
}
