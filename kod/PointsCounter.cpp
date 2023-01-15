//
// Created by Wojtek on 08.06.2019.
//

#include "PointsCounter.hpp"
PointsCounter::PointsCounter():
ocaleni_tekst(dynamic_cast<tt::Scene&>(getGlogalScene()).createActor<Text>(16)),
zgony_tekst(dynamic_cast<tt::Scene&>(getGlogalScene()).createActor<Text>(16)),
liczba_ocalonych(0),
liczba_zgonow(0)
{
    ocaleni_tekst->setCharacterSize(10);
    zgony_tekst->setCharacterSize(10);

    ocaleni_tekst->setFillColor(sf::Color::White);
    zgony_tekst->setFillColor(sf::Color::Red);

    sf::Vector2f pozycja_ocaleni;
    pozycja_ocaleni.x = dynamic_cast<tt::Scene&>(getGlogalScene()).base.getActor<Window>().getSize().x*0.9;
    pozycja_ocaleni.y = dynamic_cast<tt::Scene&>(getGlogalScene()).base.getActor<Window>().getSize().y*0.01;
    ocaleni_tekst->setPosition(pozycja_ocaleni);

    sf::Vector2f pozycja_zabici;
    pozycja_zabici.x = dynamic_cast<tt::Scene&>(getGlogalScene()).base.getActor<Window>().getSize().x*0.9;
    pozycja_zabici.y = dynamic_cast<tt::Scene&>(getGlogalScene()).base.getActor<Window>().getSize().y*0.1;
    ocaleni_tekst->setPosition(pozycja_zabici);

    std::string string_roboczy;
    string_roboczy = "ocaleni : " ;
    string_roboczy += liczba_ocalonych ;
    ocaleni_tekst->setString(string_roboczy);

    string_roboczy = "zmarli : " ;
    string_roboczy += liczba_zgonow ;
    ocaleni_tekst->setString(string_roboczy);
}

void PointsCounter::humanDied()
{
    liczba_zgonow ++;
}
void PointsCounter::humanSave()
{
    liczba_ocalonych ++;
}
void PointsCounter::update()
{
    std::string string_roboczy;
    string_roboczy = "ocaleni : " ;
    string_roboczy += liczba_ocalonych ;
    ocaleni_tekst->setString(string_roboczy);

    string_roboczy = "zmarli : " ;
    string_roboczy += liczba_zgonow ;
    ocaleni_tekst->setString(string_roboczy);
}