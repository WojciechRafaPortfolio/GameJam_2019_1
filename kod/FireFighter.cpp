//
// Created by Wojtek on 07.06.2019.
//
#include "FireFighter.hpp"

FireFighter::FireFighter():

woz_strzazacki(scene.createActor<Sprite>(18)),
Drabina(scene.createActor<Sprite>(16)),
Strazak(scene.createActor<Sprite>(16)),
gasnica(scene.createActor<AAnimatedSprite>(15)),
predkosc_max(10),
pogorzelec(scene.createActor<AAnimatedSprite>(17)),
ktos_jest_ewakuowany(false),
predkosc_pogorzelca(5)
{
    //ustalanie "pozycji - miejsce to będzie zawsze podążało za kursorem
    sf::Vector2f pozycja_poczatkowa;
    pozycja_poczatkowa.x = scene.base.getActor<Window>().getSize().x*0.2;
    pozycja_poczatkowa.y = scene.base.getActor<Window>().getSize().y*0.2;
    pozycja = pozycja_poczatkowa;

    //ustawienie parametrów ścian czyli maksymalnych ruchów drabiny
    up = scene.base.getActor<Window>().getSize().y*0.1;
    down = scene.base.getActor<Window>().getSize().y*0.8;
    left = scene.base.getActor<Window>().getSize().x*0.2;
    right = scene.base.getActor<Window>().getSize().x*0.8;


    //ustawienie"Orgin" na połowę górnego boku
    Drabina->setOrigin(Drabina->getTexture()->getSize().x*0.5,0);
    woz_strzazacki->setOrigin(woz_strzazacki->getTexture()->getSize().x*0.5,0);
    Strazak->setOrigin(Strazak->getTexture()->getSize().x*0.5,Strazak->getTexture()->getSize().y);

    //ustaw wóz stażacki
    woz_strzazacki->setPosition(pozycja.x,scene.base.getActor<Window>().getSize().y*0.8);

    //ustawainie pozycji gaśnicy
    //orgin ustawiony jest w dolnym, prawym rogu
    sf::Vector2f orgin_roboczy;
    orgin_roboczy.y = gasnica->getAnimation()->getFrame(1).height;
    orgin_roboczy.x = gasnica->getAnimation()->getFrame(1).width;
    gasnica->setOrigin(orgin_roboczy);
    //wywalam gaśnice za ekran
    sf::Vector2f pozycja_gasnicy ;
    pozycja_gasnicy.x = scene.base.getActor<Window>().getSize().x*2;
    pozycja_gasnicy.y = scene.base.getActor<Window>().getSize().y*2;
    gasnica->setPosition(pozycja_gasnicy);

    //ustawianie pogorzelca
    sf::Vector2f orgin_pogorzelca;
    orgin_pogorzelca.y =  pogorzelec->getAnimation()->getFrame(1).height;
    orgin_pogorzelca.x =  pogorzelec->getAnimation()->getFrame(1).width*0.5;
    //wywalenie pogorzelca za ekran
    sf::Vector2f pozycja_pogorzelca;
    pozycja_pogorzelca.x = scene.base.getActor<Window>().getSize().x*2;
    pozycja_pogorzelca.y = scene.base.getActor<Window>().getSize().y*2;
    pogorzelec->setPosition(pozycja_pogorzelca);
}

void FireFighter::update()
{
    //przemieszczanie "pozycji"
    if(ktos_jest_ewakuowany == false)
        ustaw_punkt_pozycja();

    Drabina->setPosition(pozycja);
    sf::Vector2f pozycja_wozu ;
    pozycja_wozu.y = woz_strzazacki->getPosition().y ;
    pozycja_wozu.x = pozycja.x ;
    woz_strzazacki->setPosition(pozycja_wozu);
    //czy strażak jest w oknie
    if(scene.getActor<Building >( ).getRoomByPosition(pozycja)->isPointInWindow(pozycja))
   {
       auto mousePosi = sf::Mouse::getPosition();
       auto mousePosf = sf::Vector2f(mousePosi.x, mousePosi.y);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                  scene.getActor<Building>().getRoomByPosition(mousePosf)->breakWindow();
            }
           if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
            {
           scene.getActor<Building>().getRoomByPosition(mousePosf)->killFire();
               //gasnica->setAnimation();//ta animacja czeka na lepsze dni ...
                gasnica->setPosition(pozycja);
            }else
           {
                //wywalam gaśnice za ekran
                auto windowSize = scene.base.getActor<Window>().getSize();
                gasnica->setPosition(sf::Vector2f(windowSize.x*2, windowSize.y*2));

                sf::Vector2f polozenie_gasnicy ;
                polozenie_gasnicy.x = scene.base.getActor<Window>().getSize().x*2 ;
                polozenie_gasnicy.y = scene.base.getActor<Window>().getSize().y*2 ;
                gasnica->setPosition(polozenie_gasnicy);
           }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::X))
            {
                auto room = scene.getActor<Building>().getRoomByPosition(mousePosf);

                if(room != nullptr )
                {
                    if(room->ifIsSomeone())
                    {
                        room->saveHuman();
                        ktos_jest_ewakuowany = true ;
                        pogorzelec->setPosition(pozycja);

                    }
                }

            }

    }else

    {
        //wywalam gaśnice za ekran
        sf::Vector2f polozenie_gasnicy ;
        polozenie_gasnicy.x = scene.base.getActor<Window>().getSize().x*2 ;
        polozenie_gasnicy.y = scene.base.getActor<Window>().getSize().y*2 ;
        gasnica->setPosition(polozenie_gasnicy);
    }

    if(ktos_jest_ewakuowany == true )
    {
        //jeżeli pogorzelec nie wyszedł poza scenę
        if(pogorzelec->getPosition().y <= scene.base.getActor<Window>().getSize().y)
        {
            pogorzelec->move(sf::Vector2f(0,predkosc_pogorzelca));
        }else
        {
            ktos_jest_ewakuowany = false;
            //wywalam pogorzelca za ekran
            sf::Vector2f pozycja_pogorzelca;
            pozycja_pogorzelca.x = scene.base.getActor<Window>().getSize().x;
            pozycja_pogorzelca.y = scene.base.getActor<Window>().getSize().y;
            pogorzelec->setPosition(pozycja_pogorzelca);

        }

    }

}
void  FireFighter::ustaw_punkt_pozycja()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        pozycja.y -= predkosc_max;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        pozycja.y += predkosc_max;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        pozycja.x -= predkosc_max;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        pozycja.x += predkosc_max;


    //sprawdzanie czy nie wyjechał
    if(pozycja.x < left)
        pozycja.x = left ;
    if(pozycja.x > right)
        pozycja.x = right ;
    if(pozycja.y < up)
        pozycja.y = up ;
    if(pozycja.y > down)
        pozycja.y = down ;
}
