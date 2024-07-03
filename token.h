#ifndef TOKEN_H
#define TOKEN_H

class Token {
public:
    Token(int initialPosition);
    void reset();
    int position() const;
    void move(int steps);

private:
    int m_position;
};

#endif // TOKEN_H
