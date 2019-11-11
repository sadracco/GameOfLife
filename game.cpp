#include <SFML/Graphics.hpp>
#include <iostream>


const short WIDTH = 700;
const short HEIGTH = 700;


short getNeigh(short x, short y, bool cells[70][70]){
    short res = 0;

    short offsets[8][2] = {{-1, -1},{0, -1},{1, -1}, {-1, 0},
                           {1, 0},{-1, 1},{0, 1},{1, 1}};
    
    for(short i=0; i<8; i++){
        if(x+offsets[i][0]>69) continue;
        if(x+offsets[i][0]<0) continue;
        if(y+offsets[i][1]>69) continue;
        if(y+offsets[i][1]<0) continue;

        if(cells[x+offsets[i][0]][y+offsets[i][1]])
            res++;
    }

    return res;
}

void updateCells(bool (*cells)[70]){
    bool res[70][70];

    for(short i=0; i<70; i++){
        for(short j=0; j<70; j++){
            if(cells[i][j])
                if(getNeigh(i, j, cells)==3 || getNeigh(i, j, cells)==2)
                    res[i][j] = true;
                else
                    res[i][j] = false;
            else
                if(getNeigh(i,j,cells) == 3)
                    res[i][j] = true;
                else
                    res[i][j] = false;
        }
    }

    for(short i=0; i<70; i++)
        for(short j=0; j<70; j++)
            cells[i][j] = res[i][j];
}


int main(int argc, char *argv[]){
    using namespace sf;

    bool cells[70][70] = {{false}};

    bool anim = false;
    bool spacePressed = false;

    RenderWindow window(VideoMode(WIDTH, HEIGTH), "Game Of Life");
    window.setFramerateLimit(60);
    RectangleShape rect;
    rect.setSize(Vector2f(10,10));
    rect.setOutlineColor(Color::White);
    rect.setOutlineThickness(0);
    rect.setFillColor(Color::Black);

    Event event;

    while(window.isOpen()){
        while(window.pollEvent(event))
            switch(event.type){
                case Event::Closed:
                    window.close();
                    return 0;
                    break;

                case Event::KeyPressed:
                    if(event.key.code == Keyboard::Space)
                        if(!spacePressed)
                            spacePressed = true;
                            anim = !anim;

                    if(event.key.code == Keyboard::Space)
                        spacePressed = false;
                    break;
            }

        if(Mouse::isButtonPressed(Mouse::Left)){
            short mouseX = Mouse::getPosition(window).x;
            short mouseY = Mouse::getPosition(window).y;
            if(0<=mouseX<=WIDTH && 0<=mouseY<=HEIGTH && !anim){
                short x = mouseX/10;
                short y = mouseY/10;
                cells[x][y] = true;
            }
        }

        if(Mouse::isButtonPressed(Mouse::Right)){
            short mouseX = Mouse::getPosition(window).x;
            short mouseY = Mouse::getPosition(window).y;
            if(0<=mouseX<=WIDTH && 0<=mouseY<=HEIGTH && !anim){
                short x = mouseX/10;
                short y = mouseY/10;
                cells[x][y] = false;
            }
        }

        window.clear();
        for(int i=0; i<70; i++)
            for(int j=0; j<70; j++){
                if(cells[i][j])
                    rect.setFillColor(Color(102, 160, 255));
                else
                    rect.setFillColor(Color::Black);

                rect.setPosition(i*10, j*10);
                window.draw(rect);
            }

        window.display();
        if(anim)
            updateCells(cells);
    }
    return 0;
}
