/*
    This header file contains the Piece class.
*/

#ifndef _PIECE_H
#define _PIECE_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "pieceTextures.h"

class Piece : public sf::Drawable
{

public:
    Piece(char type = 'P', bool player = true, int pos = -1, bool moved = false)
        : m_type{ type }, m_player{ player },
        m_position{ -1 }, m_moved{ true }, enPassant{ -1 }
    {
    }

    void setPiece(char type, bool player, int pos, bool moved = false)
    {
        setType(type);
        setPlayer(player);
        setPosition(pos); // m_moved true
        setMoved(moved);  // m_moved false
    }

    void setType(char ch)
    {
        m_type = ch;
        setTexture();
    }
    char getType() { return m_type; }

    void setPlayer(bool bl)
    {
        m_player = bl;
        setTexture();
    }
    bool getPlayer() { return m_player; }

    void setPosition(int pos)
    {
        m_position = pos;
        move();
    }
    int getPosition() { return m_position; }

    void setMoved(bool moved) { m_moved = moved; }
    bool getMoved() { return m_moved; }

    void setEnPassant(int x) { enPassant = x; }
    int getEnPassant() { return enPassant; }

    std::vector<int>& getPossibleMoves() { return possibleMoves; }
    std::vector<int>& getDangerMoves() { return dangerMoves; }

    std::string toString()
    {
        std::string str;

        str += m_player ? "White " : "Black ";

        switch (m_type)
        {
        case 'K':
            str += "King ";
            break;
        case 'Q':
            str += "Queen ";
            break;
        case 'R':
            str += "Rook ";
            break;
        case 'B':
            str += "Bishop ";
            break;
        case 'N':
            str += "Knight ";
            break;
        case 'P':
            str += "Pawn ";
            break;
        default:
            str += "??? ";
            break;
        }

        str += "\nto position\nX: ";
        str += std::to_string((m_position % 8) + 1);
        str += "  Y: ";
        str += std::to_string((m_position / 8) + 1);
        str += '\n';

        return str;
    }

private:
    sf::Sprite m_sprite;
    std::vector<int> possibleMoves;
    std::vector<int> dangerMoves; // Moves that endanger opposite king

    char m_type;    //'K'=King , 'Q' = Queen , 'R' = Rook , 'B' = Bishop , 'N' = Knight , 'P' = Pawn
    bool m_player;  // true == White , false == Black
    int m_position; // 0-63 board, -1 dead
    int enPassant;
    bool m_moved;

    void setTexture()
    {
        m_sprite = sf::Sprite();
        switch (m_type)
        {
        case 'K':
            m_sprite.setTexture(m_player ? PieceTextures::whiteKing : PieceTextures::blackKing);
            break;
        case 'Q':
            m_sprite.setTexture(m_player ? PieceTextures::whiteQueen : PieceTextures::blackQueen);
            break;
        case 'R':
            m_sprite.setTexture(m_player ? PieceTextures::whiteRook : PieceTextures::blackRook);
            break;
        case 'B':
            m_sprite.setTexture(m_player ? PieceTextures::whiteBishop : PieceTextures::blackBishop);
            break;
        case 'N':
            m_sprite.setTexture(m_player ? PieceTextures::whiteKnight : PieceTextures::blackKnight);
            break;
        case 'P':
            m_sprite.setTexture(m_player ? PieceTextures::whitePawn : PieceTextures::blackPawn);
            break;
        default:
            std::cerr << "Error piece type does not exist.\n";
            break;
        }
        m_sprite.setOrigin(sf::Vector2f(m_sprite.getTexture()->getSize().x / 2, m_sprite.getTexture()->getSize().y / 2));
        m_sprite.setScale(sf::Vector2f(0.375f, 0.375f));
    }
    void move()
    {
        if (m_position <= -1 || 64 <= m_position)
        {
            m_position = -1;
            m_sprite.setColor(sf::Color(0x00000000));
            m_sprite.setPosition(sf::Vector2f((m_position % 8) * 64.f + 32.f, (m_position / 8) * 64.f + 32.f));
            possibleMoves.clear();
            m_moved = true;
        }
        else
        {
            m_sprite.setPosition(sf::Vector2f((m_position % 8) * 64.f + 32.f, (m_position / 8) * 64.f + 32.f));
            m_moved = true;
        }
        return;
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(m_sprite);
    }
};

#endif