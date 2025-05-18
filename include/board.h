/*
    This header file contains the Board class.
*/

#ifndef _BOARD_H
#define _BOARD_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>

class Board : public sf::Drawable
{

public:
    Board(sf::Color col1 = sf::Color::White, sf::Color col2 = sf::Color::Black)
    {
        load(col1, col2);
    }

    // Member function that sets Board stuff, can choose square colors in parameters
    void load(sf::Color col1, sf::Color col2)
    {
        for (int i = 0; i < 8; i++)
        {

            bool tmpColor = ((i % 2) == 0) ? true : false;

            for (int j = 0; j < 8; j++)
            {

                m_boardSquares[j + (i * 8)].setPosition(sf::Vector2f(j * 64.f, i * 64.f));
                m_boardSquares[j + (i * 8)].setSize(sf::Vector2f(64.f, 64.f));
                m_boardSquares[j + (i * 8)].setFillColor(tmpColor ? col1 : col2);

                tmpColor = !tmpColor;
            }
        }
    }

private:
    std::array<sf::RectangleShape, 64> m_boardSquares;

    // Draw class on SFML Window
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        for (int i = 0; i < 64; i++)
        {
            target.draw(m_boardSquares[i]);
        }
    }
};

#endif