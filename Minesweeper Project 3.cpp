#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include "Game.h"
#include "TextureManger.h"
#include "Random.h"

using namespace std;

void DrawBoard(Game game, sf::RenderWindow window) {
    

}

int main()
{
    Game game = Game("boards/config.cfg");
    sf::RenderWindow window(sf::VideoMode(game.GetWidth()*32, game.GetHeight()*32+100), "Minesweeper");

    while (window.isOpen())
    {
        //Win Check
           
            if (game.clearedTiles == game.GetWidth() * game.GetHeight() - game.GetTotalBombs()){
                game.state = 2;
                game.remainingBombs = 0;
            }
        //----------Interact------------
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        
            if (event.type == sf::Event::MouseButtonReleased) {

                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    //Tiles
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    if (mousePosition.y < game.GetHeight() * 32 && game.state == 1) {
                        unsigned int col = mousePosition.x / 32 + .5f;
                        unsigned int row = mousePosition.y / 32 + .5f;
                        game.board[col * game.GetHeight() + row].Reveal(game);
                        if (game.board[col * game.GetHeight() + row].bomb)
                            game.state = 0;
                        game.clearedTiles = 0;
                        for (unsigned int i = 0; i < game.GetHeight() * game.GetWidth(); i++) {
                            if (game.board[i].revealed)
                                game.clearedTiles++;
                        }
                    }
                    //Debug
                    if (mousePosition.y > game.GetHeight() * 32 && mousePosition.x > 14 * 32 && mousePosition.x < 16 * 32 && mousePosition.y < (game.GetHeight() + 2) * 32 && game.state == 1) {
                        game.debug = !game.debug;
                    }
                    //Test1
                    if (mousePosition.y > game.GetHeight() * 32 && mousePosition.x > 16 * 32 && mousePosition.x < 18 * 32 && mousePosition.y < (game.GetHeight() + 2) * 32) {
                        game = Game("boards/testboard1.brd", 1, "boards/config.cfg");
                    }
                    //Test2
                    if (mousePosition.y > game.GetHeight() * 32 && mousePosition.x > 18 * 32 && mousePosition.x < 20 * 32 && mousePosition.y < (game.GetHeight() + 2) * 32) {
                        game = Game("boards/testboard2.brd", 1, "boards/config.cfg");
                    }
                    //Test3
                    if (mousePosition.y > game.GetHeight() * 32 && mousePosition.x > 20 * 32 && mousePosition.x < 22 * 32 && mousePosition.y < (game.GetHeight() + 2) * 32) {
                        game = Game("boards/testboard3.brd", 1, "boards/config.cfg");
                    }
                    //Face
                    if (mousePosition.y > game.GetHeight() * 32 && mousePosition.x > 10 * 32 && mousePosition.x < 12 * 32 && mousePosition.y < (game.GetHeight() + 2) * 32) {
                        game = Game("boards/config.cfg");
                    }
                }
                //Flags
                if (event.mouseButton.button == sf::Mouse::Right && game.state == 1)
                {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    if (mousePosition.y < game.GetHeight()*32) {
                        unsigned int col = mousePosition.x / 32 + .5f;
                        unsigned int row = mousePosition.y / 32 + .5f;
                        if(!game.board[col * game.GetHeight() + row].revealed)
                            game.board[col * game.GetHeight() + row].flagged = !game.board[col * game.GetHeight() + row].flagged;
                        if (game.board[col * game.GetHeight() + row].flagged) {
                            game.remainingBombs -= 1;
                            if (game.board[col * game.GetHeight() + row].bomb)
                                game.foundBombs++;
                        }
                        else if(!game.board[col * game.GetHeight() + row].revealed)
                            game.remainingBombs += 1;
                    }
                }
            }
        }


        window.clear();
       
        //-----------Load Sprites-----------
        sf::Sprite hiddenTile(TextureManager::GetTexture("tile_hidden"));
        sf::Sprite revealedTile(TextureManager::GetTexture("tile_revealed"));
        sf::Sprite mine(TextureManager::GetTexture("mine"));
        sf::Sprite debugTile(TextureManager::GetTexture("debug"));
        sf::Sprite faceTile(TextureManager::GetTexture("face_happy"));
        sf::Sprite winFace(TextureManager::GetTexture("face_win"));
        sf::Sprite loseFace(TextureManager::GetTexture("face_lose"));
        sf::Sprite test1Tile(TextureManager::GetTexture("test_1"));
        sf::Sprite test2Tile(TextureManager::GetTexture("test_2"));
        sf::Sprite test3Tile(TextureManager::GetTexture("test_3"));
        sf::Sprite number_1(TextureManager::GetTexture("number_1"));
        sf::Sprite number_2(TextureManager::GetTexture("number_2"));
        sf::Sprite number_3(TextureManager::GetTexture("number_3"));
        sf::Sprite number_4(TextureManager::GetTexture("number_4"));
        sf::Sprite number_5(TextureManager::GetTexture("number_5"));
        sf::Sprite number_6(TextureManager::GetTexture("number_6"));
        sf::Sprite number_7(TextureManager::GetTexture("number_7"));
        sf::Sprite number_8(TextureManager::GetTexture("number_8"));
        sf::Sprite flag(TextureManager::GetTexture("flag"));
        sf::Sprite digit0(TextureManager::GetTexture("digits"), sf::IntRect((0 * 21), 0, 21, 32));
        sf::Sprite digit1(TextureManager::GetTexture("digits"), sf::IntRect((1 * 21), 0, 21, 32));
        sf::Sprite digit2(TextureManager::GetTexture("digits"), sf::IntRect((2 * 21), 0, 21, 32));
        sf::Sprite digit3(TextureManager::GetTexture("digits"), sf::IntRect((3 * 21), 0, 21, 32));
        sf::Sprite digit4(TextureManager::GetTexture("digits"), sf::IntRect((4 * 21), 0, 21, 32));
        sf::Sprite digit5(TextureManager::GetTexture("digits"), sf::IntRect((5 * 21), 0, 21, 32));
        sf::Sprite digit6(TextureManager::GetTexture("digits"), sf::IntRect((6 * 21), 0, 21, 32));
        sf::Sprite digit7(TextureManager::GetTexture("digits"), sf::IntRect((7 * 21), 0, 21, 32));
        sf::Sprite digit8(TextureManager::GetTexture("digits"), sf::IntRect((8 * 21), 0, 21, 32));
        sf::Sprite digit9(TextureManager::GetTexture("digits"), sf::IntRect((9 * 21), 0, 21, 32));
        sf::Sprite digit10(TextureManager::GetTexture("digits"), sf::IntRect((10 * 21), 0, 21, 32));

        //----------Draw----------

        //Tiles
        for (unsigned int x = 0; x < game.GetWidth(); x++) {
            for (unsigned int y = 0; y < game.GetHeight(); y++) {
                if (game.board[x * game.GetHeight() + y].revealed) {
                    revealedTile.setPosition(sf::Vector2f((float)(x * 32), (float)(y * 32)));
                    window.draw(revealedTile);
                    if(game.board[x * game.GetHeight() + y].bomb){
                        mine.setPosition(sf::Vector2f((float)(x * 32), (float)(y * 32)));
                        window.draw(mine);
                    }

                    if (game.board[x * game.GetHeight() + y].adjecentBombs > 0) {
                        switch (game.board[x * game.GetHeight() + y].adjecentBombs) {
                        case 1:
                            number_1.setPosition(sf::Vector2f((float)(x * 32), (float)(y * 32)));
                            window.draw(number_1);
                            break;
                        case 2:
                            number_2.setPosition(sf::Vector2f((float)(x * 32), (float)(y * 32)));
                            window.draw(number_2);
                            break;
                        case 3:
                            number_3.setPosition(sf::Vector2f((float)(x * 32), (float)(y * 32)));
                            window.draw(number_3);
                            break;
                        case 4:
                            number_4.setPosition(sf::Vector2f((float)(x * 32), (float)(y * 32)));
                            window.draw(number_4);
                            break;
                        case 5:
                            number_5.setPosition(sf::Vector2f((float)(x * 32), (float)(y * 32)));
                            window.draw(number_5);
                            break;
                        case 6:
                            number_6.setPosition(sf::Vector2f((float)(x * 32), (float)(y * 32)));
                            window.draw(number_6);
                            break;
                        case 7:
                            number_7.setPosition(sf::Vector2f((float)(x * 32), (float)(y * 32)));
                            window.draw(number_7);
                            break;
                        case 8:
                            number_8.setPosition(sf::Vector2f((float)(x * 32), (float)(y * 32)));
                            window.draw(number_8);
                            break;
                        default:
                            cout << "fail";
                        }
                    }
                }
                else{
                    hiddenTile.setPosition(sf::Vector2f((float)(x * 32), (float)(y * 32)));
                    window.draw(hiddenTile);
                    if (game.board[x * game.GetHeight() + y].flagged) {
                        flag.setPosition(sf::Vector2f((float)(x * 32), (float)(y * 32)));
                        window.draw(flag);
                    }
                    if (game.board[x * game.GetHeight() + y].bomb && (game.debug || game.state == 0)) {
                        mine.setPosition(sf::Vector2f((float)(x * 32), (float)(y * 32)));
                        window.draw(mine);
                    }
                    if (game.board[x * game.GetHeight() + y].bomb && game.state == 2) {
                        flag.setPosition(sf::Vector2f((float)(x * 32), (float)(y * 32)));
                        window.draw(flag);
                    }
                }
            }
        }
        
        //Debug
        debugTile.setPosition(sf::Vector2f(14*32, (game.GetHeight() * 32)));
        window.draw(debugTile);
        
        //Face
        if (game.state == 1) {
            faceTile.setPosition(sf::Vector2f(10 * 32, (game.GetHeight() * 32)));
            window.draw(faceTile);
        }
        if (game.state == 0) {
            loseFace.setPosition(sf::Vector2f(10 * 32, (game.GetHeight() * 32)));
            window.draw(loseFace);
        }
        if (game.state == 2) {
            winFace.setPosition(sf::Vector2f(10 * 32, (game.GetHeight() * 32)));
            window.draw(winFace);
        }

        //Test1
        test1Tile.setPosition(sf::Vector2f(16 * 32, (game.GetHeight() * 32)));
        window.draw(test1Tile);

        //Test2
        test2Tile.setPosition(sf::Vector2f(18 * 32, (game.GetHeight() * 32)));
        window.draw(test2Tile);

        //Test3
        test3Tile.setPosition(sf::Vector2f(20 * 32, (game.GetHeight() * 32)));
        window.draw(test3Tile);

        //Counter
        string bombsLeft = to_string(game.remainingBombs);
        unsigned int posistion = 0;
        if (bombsLeft.length() < 3 && !(game.remainingBombs < 0)) {
            digit0.setPosition(sf::Vector2f(posistion * 21 + 32, game.GetHeight() * 32));
            window.draw(digit0);
            posistion++;
        }
        if (bombsLeft.length() < 2 || ((game.remainingBombs < 0) && bombsLeft.length() == 2)) {
            if(game.remainingBombs < 0)
                digit0.setPosition(sf::Vector2f((1 * 21 + 32), (game.GetHeight() * 32)));
            else
                digit0.setPosition(sf::Vector2f((posistion * 21 + 32), (game.GetHeight() * 32)));
            window.draw(digit0);
            posistion++;
        }

        for (unsigned int i = 0; i < bombsLeft.length(); i++) {
            switch (bombsLeft[i]) {
            case '0':
                digit0.setPosition(sf::Vector2f((posistion * 21 + 32), game.GetHeight()*32));
                window.draw(digit0);
            break; 
            case '1':
                digit1.setPosition(sf::Vector2f((posistion * 21 + 32), (game.GetHeight() * 32)));
                window.draw(digit1);
                break;
            case '2':
                digit2.setPosition(sf::Vector2f((posistion * 21 + 32), (game.GetHeight() * 32)));
                window.draw(digit2);
                break;
            case '3':
                digit3.setPosition(sf::Vector2f((posistion * 21 + 32), (game.GetHeight() * 32)));
                window.draw(digit3);
                break;
            case '4':
                digit4.setPosition(sf::Vector2f((posistion * 21 + 32), game.GetHeight() * 32));
                window.draw(digit4);
                break;
            case '5':
                digit5.setPosition(sf::Vector2f((posistion * 21 + 32), game.GetHeight() * 32));
                window.draw(digit5);
                break;
            case '6':
                digit6.setPosition(sf::Vector2f((posistion * 21 + 32), game.GetHeight() * 32));
                window.draw(digit6);
                break;
            case '7':
                digit7.setPosition(sf::Vector2f((posistion * 21 + 32), game.GetHeight() * 32));
                window.draw(digit7);
                break;
            case '8':
                digit8.setPosition(sf::Vector2f((posistion * 21 + 32), game.GetHeight() * 32));
                window.draw(digit8);
                break;
            case '9':
                digit9.setPosition(sf::Vector2f((posistion * 21 + 32), game.GetHeight() * 32));
                window.draw(digit9);
                break;
            case '-':
                digit10.setPosition(sf::Vector2f((0 * 21 + 32), game.GetHeight() * 32));
                window.draw(digit10);
                break;
            default:
                cout << "fail";
            }
            posistion++;
        }

        window.display();
    }
    
    return 0;
}