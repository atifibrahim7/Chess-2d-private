/*
    This code file (main.cpp) contains the main function that runs the game
    all libraries that must be used have to be included here.
*/

#include <iostream>
#include <SFML/Graphics.hpp>
#include "chessGame.h"
#include "menu.h"
int main()
{
    Menu m;
    if (m.display_menu() == 1)
        ;
    ChessGame chess(sf::Color(0xe5e4e2ff), sf::Color(0x7b7b7bff));

    sf::RenderWindow window(sf::VideoMode(768, 512), "Chess", sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);
    while (window.isOpen())
    {

        sf::Event event;

        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if ((0 <= event.mouseButton.x) && (event.mouseButton.x <= 512) && (0 <= event.mouseButton.y) && (event.mouseButton.y <= 512))
                    {
                        unsigned int buttonPos{ (event.mouseButton.x / 64) + ((event.mouseButton.y / 64) * (8 * (512 / window.getSize().y))) };

                        if (!chess.getSelected())
                            chess.selectPiece(buttonPos);
                        else
                            chess.moveSelected(buttonPos);
                    }
                    else if ((517 <= event.mouseButton.x) && (event.mouseButton.x <= 763) && (5 <= event.mouseButton.y) && (event.mouseButton.y <= 45))
                    {
                        chess.restart();
                    }
                }
            }
        }

        window.draw(chess);
        window.display();
    }
}