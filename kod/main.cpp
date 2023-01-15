#include "Base.hpp"
#include "MainGame.hpp"
#include "Window.hpp"

int main(){
    std::srand( std::time( nullptr ) );
    tt::Base base;
    base.setFramerate( 30 );
    base.getActor<Window>();
    base.setActiveScene( base.createScene<MainGame>() );
    base.run();
}
