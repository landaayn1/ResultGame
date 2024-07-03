#include "token.h"


Token::Token(int initialPosition): m_position(initialPosition) {}

void Token::reset(){
    m_position = 0;
}

int Token::position() const {
    return m_position;
}

void Token::move(int steps){
    m_position += steps;
    if (m_position >= 37) {
        m_position = 0;
    }
}
