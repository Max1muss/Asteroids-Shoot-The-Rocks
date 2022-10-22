#pragma once
#include "Object.h"
#include <iostream>
#include <SFML/Graphics.hpp>



class Player : public Object
{
    float upSpeed, downSpeed, rightSpeed, leftSpeed;
    Image m_explosion;
    float currentFrame = 0;
    int frameCount = 1;
    bool isImmune = false;

public:

    Player(string name, float x, float y, int dir, float w, float h) : Object(name, x, y, dir, w, h) 
    {
        m_image.loadFromFile("images/spritesheet.png");
        m_image.createMaskFromColor(Color(246, 246, 246));
        m_image.createMaskFromColor(Color(255, 255, 255));
        m_image.createMaskFromColor(Color(247, 247, 247));
        m_texture.loadFromImage(m_image);
        m_sprite.setTexture(m_texture);
        m_sprite.setOrigin(m_w / 2, m_h / 2);
        m_explosion.loadFromFile("images/explosion.png");

        for (int add1 = 0; add1 < 11; ++add1)
            for (int add2 = 0; add2 < 11; ++add2)
                for (int add3 = 0; add3 < 11; ++add3)
                    m_explosion.createMaskFromColor(Color(240 + add1, 240 + add2, 240 + add3));

    }

    void update(RenderWindow& window, float time);
    virtual Sprite getSprite();
    virtual void update(){}
    virtual void update(float time){}
    virtual IntRect getRect();

    void setDirection(int dir);
    virtual int getDirection();
    void explode();
    virtual float getSpeed() { return m_speed; }
    bool isPlayerImmune();
    void setVulnerable();
    void paintBlue();
    void setImmune();
    void removeBlue();
    
};

