#include "scanner.h"    

//Construtor
Scanner::Scanner(string input)
{
    this->input = input;
    cout << "Entrada: " << input << endl << "Tamanho: " 
         << input.length() << endl;
    pos = 0;
}

//Método que retorna o próximo token da entrada
Token* 
Scanner::nextToken()
{
    
    Token* tok;
    int state;

    state = 0;

    while (true)
    {
        switch (state)
        {
            case 0://Junção dos estados 0, 9, 12 e 22 dos diagramas
                if (input[pos] == '\0')
                {
                    tok = new Token(END_OF_FILE);

                    return tok;
                }
                if (input[pos] == '<')
                    state = 1;
                else if (input[pos] == '=')
                    state = 5;
                else if (input[pos] == '>')
                    state = 6;
                else if (isalpha(input[pos]))
                    state = 10;
                else if (isdigit(input[pos]))
                    state = 13;
                else if (isspace(input[pos]))
                    state = 23;

                pos++;

                break;

            case 1:
                if (input[pos] == '=')
                    state = 2;
                else if (input[pos] == '>')
                    state = 3;
                else
                    state = 4;

                pos++;

                break;
            case 2:
                tok = new Token(RELOP, LE);

                return tok;
            
            case 3:
                tok = new Token(RELOP, NE);

                return tok;

            case 4:
                tok = new Token(RELOP, LT);
                pos--;
                return tok;

            case 5:
                tok = new Token(RELOP, EQ);

                return tok;
            case 6:
                if (input[pos] == '=')
                    state = 7;
                else
                    state = 8;

                pos++;

                break;

            case 7:
                tok = new Token(RELOP, GE);

                return tok;
            case 8:
                tok = new Token(RELOP, GT);
                pos--;

                return tok;
            //case 9:Juntou com o 0
            case 10:
                if (!isalnum(input[pos]))
                    state = 11;
                pos++;

                break;
            case 11:
                tok = new Token(ID);
                pos--;
                return tok;

            // case 12 juntou com o 0
            case 13:
                if(isdigit(input[pos]))
                    ;
                else if(input[pos] == '.')
                    state = 14;
                else if(input[pos] == 'E')
                    state = 16;
                else
                    state = 20;
                pos++;

                break;
            case 14:
                if(isdigit(input[pos]))
                    state = 15;
                else
                    return lexicalError()
                pos++;

                break;
            case 15:
                if(isdigit(input[pos]))
                    ;
                else if(input[pos] == 'E')
                    state = 16;
                else
                    state = 21;
                pos++;

                break;
            case 16:
                if(input[pos] == '+' || input[pos] == '-')
                    state = 17;
                else if(isdigit(input[pos]))
                    state = 18;
                else
                    return lexicalError();
                pos++;

                break;
            case 17:
                if(isdigit(input[pos]))
                    state = 18;
                else
                    return lexicalError();
                pos++;

                break;
            case 18:
                if(isdigit(input[pos]))
                    ;
                else
                    state = 19;
                pos++;
                
                break;
            case 19:
                pos--;
                tok = Token(NUMBER, DOUBLE_LITERAL);
                return tok;
            case 20:
                pos--;
                tok = Token(NUMBER, INTEGER_LITERAL);
                return tok;
            case 21:
                pos--;
                tok = Token(NUMBER, FLOAT_LITERAL);
                return tok;
            // Case 22 juntou com o 0
            case 23:
                if(input[pos] == ' ')
                    ;
                else
                    state = 24
                pos++;
                
                break;
            case 24:
                pos--;
                state = 0;
                
                break;
        }
    }   


   
}

void 
Scanner::lexicalError()
{
    cout << "Token mal formado\n";
    
    exit(EXIT_FAILURE);
}
