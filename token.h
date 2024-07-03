#ifndef TOKEN_H
#define TOKEN_H

class Token {
public:
    Token(int initialPosition) : m_position(initialPosition) {}

    int position() const { return m_position; }
    void move(int steps) {
        m_position += steps;
        if (m_position >= 37) {
            m_position = 0;
        }
    }

private:
    int m_position;
};

#endif // TOKEN_H
