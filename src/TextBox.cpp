//
//  TextBox.cpp
//  MSD-CS6010-Final-Project
//
//  Created by Avishek Choudhury on 9/23/22.
//

#include "TextBox.hpp"
#include <SFML/Graphics.hpp>
#include <sstream>

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class TextBox {
private:
    sf::Text textBox;
    std::stringstream text;
    bool isSelected;
    
    void inputLogic(int charTyped) {
        if ((charTyped >= 65 && charTyped <= 90) || (charTyped >= 97 && charTyped <= 122)) {
            text << static_cast<char>(charTyped);
        }
        else if (charTyped == DELETE_KEY)
        {
            if (text.str().length() > 0) {
                deleteLastChar();
            }
        }
        textBox.setString(text.str() + "_");
    }
    
    void deleteLastChar() {
        std::string oldT = text.str();
        std::string newT = "";
        for (int i = 0; i < oldT.length() - 1; i++) {
            newT[i] += oldT[i];
        }
        textBox.setString(newT);
    }
    
public:
    TextBox(int size, sf::Color color, bool sel) {
        textBox.setCharacterSize(size);
        textBox.setColor(color);
        isSelected = sel;
        if (isSelected) {
            textBox.setString("_");
        }
        else {
            textBox.setString("");
        }
        sf::Font font;
        font.loadFromFile("arial.ttf");
        textBox.setFont(font);
    }
    
    void setPosition(sf::Vector2f position) {
        textBox.setPosition(position);
    }
    
    void setSelected(bool sel) {
        isSelected = sel;
        if (!isSelected) {
            std::string oldT = text.str();
            std::string newT = "";
            for (int i = 0; i < oldT.length() - 1; i++) {
                newT[i] += oldT[i];
            }
            textBox.setString(newT);
        }
    }
    
    std::string getText() {
        return text.str();
    }
    
    void draw(sf::RenderWindow& window) {
        window.draw(textBox);
    }
    
    void typedOn(sf::Event input) {
        if (isSelected) {
            int charTyped = input.text.unicode;
            if (charTyped < 128) {
                inputLogic(charTyped);
            }
            else if (charTyped == DELETE_KEY) {
                deleteLastChar();
            }
        }
    }
};
