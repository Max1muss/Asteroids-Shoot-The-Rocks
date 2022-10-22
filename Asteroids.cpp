#pragma once
#include <SFML/Graphics.hpp>
#include <Iostream>
#include "Player.h"
#include "bigAsteroid.h"
#include "SmallAsteroid.h"
#include "Bullet.h"
#include <list>
#include "generateBigAsteroid.h"
#include "Shield.h"
#include "Aim.h"
#include "Missile.h"
#include "AutoShooter.h"
#include <cmath>

using namespace sf;

int main()
{
    sf::RenderWindow window(sf::VideoMode(848, 477), "Asteroids", Style::None);
    Image background;
    background.loadFromFile("images/background.png");
    Texture backgroundTexture;
    backgroundTexture.loadFromImage(background);
    Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);

  
    

    Player p("player", window.getSize().x / 2.0f, window.getSize().y / 2.0f, 0, 20, 20); // creating a player

    Clock clock;
    float timer = 0;
    int spawnTime = 0;
    float immunityTimer = 0;
    float blinkTimer = 0;
    bool blinkState = false;
    int randomNumber = 0;
    float bonusTime = 0;
    bool isUnderShield = false;
    bool shieldBlinkState = false;
    float shieldBlinkTimer = 0;
    int shieldCount = 0;
    bool isAimed = false;
    bool isMissileExist = false;
    int bulletCount = 0;
    bool pareFound = false;
    
    

    std::list<Object*> objects;
    std::list<Object*>::iterator it;
    std::list<Object*>::iterator it2;//второй итератор.для взаимодействия между объектами списка




    while (window.isOpen())
    {
     
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;

        Vector2i pixelPos = Mouse::getPosition(window);// get cursor's coordinates
        Vector2f pos = window.mapPixelToCoords(pixelPos);// turn them into global 

        timer += time;
        if (p.isPlayerImmune() && (!isUnderShield)) // give player immunity for 5 sec after revival 
        {
            immunityTimer += time;
            blinkTimer += time;
            if (blinkTimer > 500) // make player blink each 0.5 sec
            {
                if (blinkState)
                    blinkState = false;
                else
                    blinkState = true;

                blinkTimer = 0;
            }

            if (immunityTimer > 5000) // remove immunity
            {
                p.setVulnerable();
                immunityTimer = 0;
                blinkState = false;
            }
        }

        if (timer > (spawnTime * 1000)) // spawn a random asteroid 
        {
            int randAsteroid = genRandAsteroid();
            int randNum = genRandNum();
            int randX = genRandX();
            int randY = genRandY();
            int randDir = genRandDir();
            int randIndex = genRandIndex();
            float randSpeed = genRandImpulse();

            if (randAsteroid)
            {
                switch (randNum)
                {
                case 0: objects.push_back(new BigAsteroid("bigAsteroid", 0, randY, randDir + 4, 60, 60, 0.05 + randSpeed)); break;
                case 1: objects.push_back(new BigAsteroid("bigAsteroid", 848, randY, randDir + 4, 60, 60, 0.05 + randSpeed)); break;
                case 2: objects.push_back(new BigAsteroid("bigAsteroid", randX, 0, randDir + 4, 60, 60, 0.05 + randSpeed)); break;
                case 3: objects.push_back(new BigAsteroid("bigAsteroid", randX, 477, randDir + 4, 60, 60, 0.05 + randSpeed)); break;
                }
            }
            else
            {
                switch (randNum)
                {
                case 0: objects.push_back(new SmallAsteroid("smallAsteroid", 0, randY, randDir + 4, 40, 40, randIndex, 0.05 + randSpeed)); break;
                case 1: objects.push_back(new SmallAsteroid("smallAsteroid", 848, randY, randDir + 4, 40, 40, randIndex, 0.05 + randSpeed)); break;
                case 2: objects.push_back(new SmallAsteroid("smallAsteroid", randX, 0, randDir + 4, 40, 40, randIndex, 0.05 + randSpeed)); break;
                case 3: objects.push_back(new SmallAsteroid("smallAsteroid", randX, 477, randDir + 4, 40, 40, randIndex, 0.05 + randSpeed)); break;
                }
            }

            timer = 0;
            spawnTime = getRandomSpawnTime(); 
        }


        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed) // if left mouse button clicked, spawn a bullet
                if (event.key.code == Mouse::Left)
                    objects.push_back(new Bullet("bullet", p.getX() + 11, p.getY() + 11, p.getDirection(), 5, 5, false, 0));

            if (event.type == Event::MouseButtonPressed)// create aim and launch a missile
                if (event.key.code == Mouse::Right)
                {
                    for (it = objects.begin(); it != objects.end();)
                    {
                        Object* b = *it;
                        if (((b->getName() == "smallAsteroid" || b->getName() == "bigAsteroid")))
                        {
                            if (b->isRockAimed())
                                break;
                        }


                        if (((b->getName() == "smallAsteroid" || b->getName() == "bigAsteroid")
                            && b->getSprite().getGlobalBounds().contains(pos.x, pos.y)))
                        { 
                            b->putAim();
                            isAimed = true;
                            objects.push_back(new Missile("missile", p.getX(), p.getY(), 0, 15, 25, 1));
                        }

                        ++it;
                    }
                }
        }

        p.update(window, time); // player update

        for (it = objects.begin(); it != objects.end();)// update all objects
        {
            Object* b = *it;
            if ((b->getName() == "shield") && (b->isShieldActive()))
            {
                b->update(p.getX(), p.getY());
                p.paintBlue();
            }
            else
            b->update(time);
            if (b->isDestroyed() == true) {  it = objects.erase(it); delete b;}// delete all dead objects
            else 
            it++;
        }
        for (it = objects.begin(); it != objects.end(); it++)//проходимся по эл-там списка
        {
            if ((((*it)->getName() == "bigAsteroid") || ((*it)->getName() == "smallAsteroid")) && ((*it)->getRect().intersects(p.getRect()) && (!p.isPlayerImmune())))//если игрок столкнулся с объектом списка и имя этого объекта movingplatform
            {
                p.explode(); // explode player if they get hit by an asteroid
            }

            if (((*it)->getName() == "shield") && ((*it)->getRect().intersects(p.getRect()))
                && (!(*it)->isShieldActive()) && isUnderShield == true) // renew shield in case if already have one
            {
                (*it)->kill();
                bonusTime = 0;
                shieldBlinkState = false;
                shieldBlinkTimer = 0;
            }
            else if (((*it)->getName() == "shield") && ((*it)->getRect().intersects(p.getRect()))
                && (!(*it)->isShieldActive()) && isUnderShield == false)//using shield after picking it
            {     
                (*it)->activate();
                isUnderShield = true;
                p.setImmune();
                immunityTimer = 0;
                blinkTimer = 0;
                blinkState = false;
            }
            
            if (((*it)->getName() == "missile") && (*it)->getRect().intersects(p.getRect())
                && (!(*it)->isMissilePicked())) // picking missile 
            {
                objects.push_back(new Aim("aim", pos.x, pos.y, 0, 25, 25)); // spawning aim 
                (*it)->pickUp();
                if (!(*it)->getState()) // remove the missile from the screen
                {
                    (*it)->setX(-100);
                    (*it)->setY(-100);
                }

            }

            if (((*it)->getName() == "shield") && ((*it)->isShieldActive())) // removing shield if time is gone
            {
                bonusTime += time;
                if (bonusTime > 15000)
                {
                    (*it)->deactivateShield();
                    bonusTime = 0;
                    p.setVulnerable();
                    shieldBlinkTimer = 0;
                    shieldBlinkState = false;
                    isUnderShield = false;
                    p.removeBlue();
                }
                else if (bonusTime > 10000) // blink shield before 5 sec to the end of the effect
                {
                    shieldBlinkTimer += time;
                    if (shieldBlinkTimer > 500)
                    {
                        if (shieldBlinkState)
                            shieldBlinkState = false;
                        else
                            shieldBlinkState = true;

                        shieldBlinkTimer = 0;
                    }
                }
            }


            if (((*it)->getName() == "bullet") && ((*it)->isBulletAuto())) // if a bullet didn't reach the target, destroy it
            {
                for (it2 = objects.begin(); it2 != objects.end(); it2++)
                {
                    if ((*it2)->getName() == "smallAsteroid" || (*it2)->getName() == "bigAsteroid")
                        if ((*it2)->getMarkIndex() == (*it)->getMarkIndex())
                        {
                            pareFound = true;
                            break;
                        }
                }

                if (!pareFound)
                    (*it)->kill();

            }

            if ((*it)->getName() == "missile" && (!isMissileExist)) // if missile is destroyed, remove from the list
            {
                (*it)->kill();
            }

            if ((*it)->getName() == "aim" && (!isMissileExist)) 
            {
                (*it)->kill();
            }

           

 
        
            for (it2 = objects.begin(); it2 != objects.end(); it2++)
            {
                if ((*it)->getRect() != (*it2)->getRect()) // assert that objects are different
                {
                    if (((*it)->getRect().intersects((*it2)->getRect())) // if bullet hits a big asteroid
                        && ((*it)->getName() == "bigAsteroid")
                        && ((*it2)->getName() == "bullet"))
                    {
                        (*it2)->kill();
                        (*it)->kill();
                        objects.push_back(new SmallAsteroid("smallAsteroid", (*it)->getX(), (*it)->getY(), (*it)->getDirection(), 40, 40, 0, (*it)->getSpeed())); // spawn two small asteroids
                        objects.push_back(new SmallAsteroid("smallAsteroid", (*it)->getX(), (*it)->getY(), (*it)->getDirection(), 40, 40, 1, (*it)->getSpeed()));
                        randomNumber = genRandomNumber();
                        std::cout << randomNumber << "\n";
                        if (randomNumber < 8 && randomNumber > 5) // spawn bonuses with some probability
                            objects.push_back(new Shield("shield", (*it)->getX(), (*it)->getY(), 0, 30, 30));
                        else if (randomNumber < 6 && (!isMissileExist))
                        {
                            objects.push_back(new Missile("missile", (*it)->getX(), (*it)->getY(), 0, 15, 25, 0));
                            isMissileExist = true;
                        }
                        else if (randomNumber == 8 || randomNumber == 9)
                        {
                            objects.push_back(new AutoShooter("autoShooter", (*it)->getX(), (*it)->getY(), 0, 28, 25));
                        }

                    }

                    if (((*it)->getRect().intersects((*it2)->getRect())) // if bullet hits a small asteroid
                        && ((*it)->getName() == "smallAsteroid")
                        && ((*it2)->getName() == "bullet") && (!(*it2)->isDestroyed()))
                    {
                        (*it)->kill();
                        (*it2)->kill();
                        randomNumber = genRandomNumber();
                        std::cout << randomNumber << "\n";
                        if (randomNumber == 3)
                            objects.push_back(new Shield("shield", (*it)->getX(), (*it)->getY(), 0, 30, 30));
                        else if (randomNumber < 3 && (!isMissileExist))
                        {
                            objects.push_back(new Missile("missile", (*it)->getX(), (*it)->getY(), 0, 15, 25, 0));
                            isMissileExist = true;
                        }
                        else if (randomNumber == 4)
                        {
                            objects.push_back(new AutoShooter("autoShooter", (*it)->getX(), (*it)->getY(), 0, 28, 25));
                        }
                    }

                    if (((*it)->getRect().intersects((*it2)->getRect())) // destroy both missile and the hit rock on collision
                        && ((*it)->getName() == "smallAsteroid" || ((*it)->getName() == "bigAsteroid"))
                            && ((*it2)->getName() == "missile") && (*it2)->isMissileLaunched() && (*it)->isRockAimed())
                    {
                        std::cout << "here\n";
                        (*it)->kill();
                        (*it2)->kill();
                        isAimed = false;
                        isMissileExist = false;
                    }

                    if (((*it)->getRect().intersects((*it2)->getRect())) //push rocks with the shield implementation
                        && (((*it)->getName() == "smallAsteroid") || ((*it)->getName() == "bigAsteroid"))
                        && (((*it2)->getName() == "shield") && ((*it2)->isShieldActive())))
                    {
                        if (((*it)->getDirection()) == 7 && (p.getX() >= (*it)->getX() && p.getY() >= (*it)->getY()))
                        {
                            while ((*it)->getRect().intersects((*it2)->getRect()))
                                (*it)->push(7, 4, 0);
                        }
                        else if (((*it)->getDirection()) == 7 && (p.getX() <= (*it)->getX() && p.getY() >= (*it)->getY()))
                        {
                            while ((*it)->getRect().intersects((*it2)->getRect()))
                                (*it)->push(7, 4, 1);
                        }
                        else if (((*it)->getDirection()) == 7 && (p.getX() >= (*it)->getX() && p.getY() <= (*it)->getY()))
                        {
                            while ((*it)->getRect().intersects((*it2)->getRect()))
                                (*it)->push(7, 4, 2);
                        }
                        else if ((((*it)->getDirection()) == 4) && ((p.getX() <= (*it)->getX()) && (p.getY() <= (*it)->getY())))
                        {
                            while ((*it)->getRect().intersects((*it2)->getRect()))
                                (*it)->push(4, 7, 0);
                        }
                        else if ((((*it)->getDirection()) == 4) && ((p.getX() <= (*it)->getX()) && (p.getY() >= (*it)->getY())))
                        {
                            while ((*it)->getRect().intersects((*it2)->getRect()))
                                (*it)->push(4, 7, 1);
                        }
                        else if ((((*it)->getDirection()) == 4) && ((p.getX() >= (*it)->getX()) && (p.getY() <= (*it)->getY())))
                        {
                            while ((*it)->getRect().intersects((*it2)->getRect()))
                                (*it)->push(4, 7, 2);
                        }
                        else if (((*it)->getDirection()) == 6 && ((p.getX() <= (*it)->getX()) && (p.getY() >= (*it)->getY())))
                        {
                            while ((*it)->getRect().intersects((*it2)->getRect()))
                                (*it)->push(6, 5, 0);
                        }
                        else if (((*it)->getDirection()) == 6 && ((p.getX() <= (*it)->getX()) && (p.getY() <= (*it)->getY())))
                        {
                            while ((*it)->getRect().intersects((*it2)->getRect()))
                                (*it)->push(6, 5, 1);
                        }
                        else if (((*it)->getDirection()) == 6 && ((p.getX() >= (*it)->getX()) && (p.getY() >= (*it)->getY())))
                        {
                            while ((*it)->getRect().intersects((*it2)->getRect()))
                                (*it)->push(6, 5, 2);
                        }
                        else if (((*it)->getDirection()) == 5 && (((p.getX() >= (*it)->getX()))))
                        {
                            while ((*it)->getRect().intersects((*it2)->getRect()))
                                (*it)->push(5, 4, 0);
                        }
                        else if (((*it)->getDirection()) == 5 && (((p.getX() <= (*it)->getX()) && (p.getY() <= (*it)->getY()))))
                        {
                            while ((*it)->getRect().intersects((*it2)->getRect()))
                                (*it)->push(5, 7, 0);
                        }
                        else if (((*it)->getDirection()) == 7 && (((p.getX() <= (*it)->getX() && (p.getY() <= (*it)->getY())))))
                        {
                            while ((*it)->getRect().intersects((*it2)->getRect()))
                                (*it)->push(7, 7, 0);
                        }
                        else if (((*it)->getDirection()) == 6 && (((p.getX() >= (*it)->getX() && (p.getY() <= (*it)->getY())))))
                        {
                            while ((*it)->getRect().intersects((*it2)->getRect()))
                                (*it)->push(6, 6, 0);
                        }
                        else if (((*it)->getDirection()) == 5 && (((p.getX() <= (*it)->getX() && (p.getY() >= (*it)->getY())))))
                        {
                            while ((*it)->getRect().intersects((*it2)->getRect()))
                                (*it)->push(5, 5, 0);
                        }
                        else if (((*it)->getDirection()) == 4 && (((p.getX() >= (*it)->getX() && (p.getY() >= (*it)->getY())))))
                        {
                            while ((*it)->getRect().intersects((*it2)->getRect()))
                                (*it)->push(4, 4, 0);
                        }
                    }
                    if (((*it)->getRect().intersects((*it2)->getRect())) // rocks collision handling
                        && (((*it)->getName() == "smallAsteroid") || ((*it)->getName() == "bigAsteroid"))
                        && (((*it2)->getName() == "smallAsteroid") || ((*it2)->getName() == "bigAsteroid")))
                    {
                        if (((*it)->getDirection()) == 7 && ((*it2)->getDirection()) == 4)
                        {
                            while ((*it)->getRect().intersects((*it2)->getRect()))
                            {
                                (*it)->push(7, 4, 3);
                                (*it2)->push(7, 4, 4);
                            }

                            (*it)->setDirection(4);
                            (*it2)->setDirection(7);
                        }
                        else if (((*it)->getDirection()) == 6 && ((*it2)->getDirection()) == 5)
                        {
                            while ((*it)->getRect().intersects((*it2)->getRect()))
                            {
                                (*it)->push(6, 5, 3);
                                (*it2)->push(6, 5, 4);
                            }

                            (*it)->setDirection(5);
                            (*it2)->setDirection(6);
                        }
                        else if (((*it)->getDirection()) == 7 && ((*it2)->getDirection()) == 5)
                        {
                            while ((*it)->getRect().intersects((*it2)->getRect()))
                            {
                                (*it)->push(7, 5, 3);
                                (*it2)->push(7, 5, 4);
                            }

                            (*it)->setDirection(5);
                            (*it2)->setDirection(7);
                        }
                        else if (((*it)->getDirection()) == 6 && ((*it2)->getDirection()) == 4)
                        {
                            while ((*it)->getRect().intersects((*it2)->getRect()))
                            {
                                (*it)->push(6, 4, 3);
                                (*it2)->push(6, 4, 4);
                            }

                            (*it)->setDirection(4);
                            (*it2)->setDirection(6);
                        }
                        else if (((*it)->getDirection()) == 5 && ((*it2)->getDirection()) == 4)
                        {
                            while ((*it)->getRect().intersects((*it2)->getRect()))
                            {
                                (*it)->push(5, 4, 3);
                                (*it2)->push(5, 4, 4);
                            }

                            (*it)->setDirection(4);
                            (*it2)->setDirection(5);
                        }
                        else if (((*it)->getDirection()) == 7 && ((*it2)->getDirection()) == 6)
                        {
                            while ((*it)->getRect().intersects((*it2)->getRect()))
                            {
                                (*it)->push(7, 6, 3);
                                (*it2)->push(7, 6, 4);
                            }

                            (*it)->setDirection(6);
                            (*it2)->setDirection(7);
                        }
                        else if (((*it)->getDirection()) == 7 && ((*it2)->getDirection()) == 7
                            && ((*it)->getX() <= (*it2)->getX() && (*it)->getY() <= (*it2)->getY()))
                        {
                            while ((*it)->getRect().intersects((*it2)->getRect()))
                            {
                                (*it2)->push(7, 7, 3);
                            }
                        }
                        else if (((*it)->getDirection()) == 7 && ((*it2)->getDirection()) == 7
                            && ((*it)->getX() >= (*it2)->getX() && (*it)->getY() <= (*it2)->getY()))
                        {
                            while ((*it)->getRect().intersects((*it2)->getRect()))
                            {
                                (*it2)->push(7, 7, 4);
                            }
                        }
                        else if (((*it)->getDirection()) == 7 && ((*it2)->getDirection()) == 7
                            && ((*it)->getX() <= (*it2)->getX() && (*it)->getY() >= (*it2)->getY()))
                        {
                            while ((*it)->getRect().intersects((*it2)->getRect()))
                            {
                                (*it2)->push(7, 7, 5);
                            }
                        }
                        else if (((*it)->getDirection()) == 6 && ((*it2)->getDirection()) == 6
                            && ((*it)->getX() >= (*it2)->getX() && (*it)->getY() <= (*it2)->getY()))
                        {
                            while ((*it)->getRect().intersects((*it2)->getRect()))
                            {
                                (*it2)->push(6, 6, 3);
                            }
                        }
                        else if (((*it)->getDirection()) == 6 && ((*it2)->getDirection()) == 6
                            && ((*it)->getX() <= (*it2)->getX() && (*it)->getY() <= (*it2)->getY()))
                        {
                            while ((*it)->getRect().intersects((*it2)->getRect()))
                            {
                                (*it2)->push(6, 6, 4);
                            }
                        }
                        else if (((*it)->getDirection()) == 6 && ((*it2)->getDirection()) == 6
                        && ((*it)->getX() >= (*it2)->getX() && (*it)->getY() >= (*it2)->getY()))
                        {
                              while ((*it)->getRect().intersects((*it2)->getRect()))
                             {
                                (*it2)->push(6, 6, 5);
                             }
                        }
                        else if (((*it)->getDirection()) == 5 && ((*it2)->getDirection()) == 5
                        && ((*it)->getX() <= (*it2)->getX() && (*it)->getY() >= (*it2)->getY()))
                        {
                              while ((*it)->getRect().intersects((*it2)->getRect()))
                             {
                                 (*it2)->push(5, 5, 3);
                             }
                        }
                        else if (((*it)->getDirection()) == 5 && ((*it2)->getDirection()) == 5
                        && ((*it)->getX() <= (*it2)->getX() && (*it)->getY() <= (*it2)->getY()))
                        {
                        while ((*it)->getRect().intersects((*it2)->getRect()))
                        {
                            (*it2)->push(5, 5, 4);
                        }
                        }
                        else if (((*it)->getDirection()) == 5 && ((*it2)->getDirection()) == 5
                        && ((*it)->getX() >= (*it2)->getX() && (*it)->getY() >= (*it2)->getY()))
                        {
                        while ((*it)->getRect().intersects((*it2)->getRect()))
                        {
                            (*it2)->push(5, 5, 5);
                        }
                        }
                        else if (((*it)->getDirection()) == 4 && ((*it2)->getDirection()) == 4
                        && ((*it)->getX() >= (*it2)->getX() && (*it)->getY() >= (*it2)->getY()))
                        {
                        while ((*it)->getRect().intersects((*it2)->getRect()))
                        {
                            (*it2)->push(4, 4, 3);
                        }
                        }
                        else if (((*it)->getDirection()) == 4 && ((*it2)->getDirection()) == 4
                        && ((*it)->getX() >= (*it2)->getX() && (*it)->getY() <= (*it2)->getY()))
                        {
                        while ((*it)->getRect().intersects((*it2)->getRect()))
                        {
                            (*it2)->push(4, 4, 4);
                        }
                        }
                        else if (((*it)->getDirection()) == 4 && ((*it2)->getDirection()) == 4
                        && ((*it)->getX() <= (*it2)->getX() && (*it)->getY() >= (*it2)->getY()))
                        {
                        while ((*it)->getRect().intersects((*it2)->getRect()))
                        {
                            (*it2)->push(4, 4, 5);
                        }
                        }
                    }

                    if (((*it)->getName() == "aim") && ((*it2)->getName() == "smallAsteroid")
                         && (*it2)->isRockAimed())
                    {
                        (*it)->setX((*it2)->getX() + 17);
                        (*it)->setY((*it2)->getY() + 17);
                    }
                    if (((*it)->getName() == "aim") && ((*it2)->getName() == "bigAsteroid")
                        && (*it2)->isRockAimed())
                    {
                        (*it)->setX((*it2)->getX() + 30);
                        (*it)->setY((*it2)->getY() + 30);
                    }

                    if ((*it)->getName() == "missile" && (*it)->isMissilePicked() && (!isAimed))
                    {
                        if ((*it2)->getName() == "aim")
                        {
                            (*it2)->setX(pos.x);
                            (*it2)->setY(pos.y);
                        }
                    }

                    if (((*it)->getName() == "aim"))
                    {
                        float x = (*it)->getX();
                        float y = (*it)->getY();
                        if ((*it2)->getName() == "missile" && (*it2)->isMissileLaunched())
                        {
                            (*it2)->setTempX(x);
                            (*it2)->setTempY(y);
                        }
                    }

                    if (((*it)->getName() == "autoShooter") && (*it)->getRect().intersects(p.getRect())) //pick auto-shooter
                    {
                        (*it)->kill();

                        if (((*it2)->getName() == "bigAsteroid" || (*it2)->getName() == "smallAsteroid")
                            && ((abs((*it2)->getX() - p.getX()) <= 200 && (abs((*it2)->getY() - p.getY())) <= 200)))
                        {
                            ++bulletCount;
                            objects.push_back(new Bullet("bullet", p.getX() + 11, p.getY() + 11, p.getDirection(), 5, 5, true, bulletCount));
                            (*it2)->mark(bulletCount);
                        }
                    }

                    if (((*it)->getName() == "bullet") && (*it)->isBulletAuto() && ((*it2)->getName() == "smallAsteroid"
                        || (*it2)->getName() == "bigAsteroid") && ((*it)->getMarkIndex() == (*it2)->getMarkIndex())) // follow aimed asteroids
                    {
                        float x = (*it2)->getX();
                        float y = (*it2)->getY();
                        (*it)->setTempX(x);
                        (*it)->setTempY(y);
                    }
                   
                }
            }
        }
      
        window.clear();
        window.draw(backgroundSprite);
        for (it = objects.begin(); it != objects.end(); it++) 
        {
            if (((*it)->getName() == "shield") && (shieldBlinkState) && (*it)->isShieldActive());
            else if ((*it)->getName() == "aim");
            else
            window.draw((*it)->getSprite());
        }
        for (it = objects.begin(); it != objects.end(); it++) 
        {
            if ((*it)->getName() == "aim")
            {
                window.draw((*it)->getSprite());
                break;
            }
        }
        if (!blinkState)
        window.draw(p.getSprite());
        window.display();
    }

    return 0;
}