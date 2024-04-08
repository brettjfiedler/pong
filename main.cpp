#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>

const int WINDOW_WIDTH {2000};
const int WINDOW_HEIGHT {1440};
const int PADDLE_WIDTH {40};
const int PADDLE_HEIGHT {240};
const int BALL_DIAMETER {30};
const int PADDLE_SPEED {1};

float BALL_SPEED_X {1.0};
float BALL_SPEED_Y {0.8};


int main()
{
    sf::Font font;
    if(!font.loadFromFile("RedditMono.ttf"));
    {
        //error
    }
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "PONG");
    sf::CircleShape ball(BALL_DIAMETER);
    ball.setFillColor(sf::Color::White);
    sf::RectangleShape leftPaddle(sf::Vector2f(PADDLE_WIDTH,PADDLE_HEIGHT));
    leftPaddle.setFillColor(sf::Color::White);
    sf::RectangleShape rightPaddle(sf::Vector2f(PADDLE_WIDTH,PADDLE_HEIGHT));
    rightPaddle.setFillColor(sf::Color::White);


    int scoreRight {0};
    int scoreLeft {0};
    std::string scoreLine{};

    sf::Text Score;
    scoreLine = std::to_string(scoreLeft) + "  -  " + std::to_string(scoreRight);
    //std::cout << scoreLine << std::endl;
    Score.setFont(font);
    Score.setString(scoreLine);
    Score.setCharacterSize(75);
    Score.setFillColor(sf::Color::Green);
    Score.setPosition(round(WINDOW_WIDTH/2.4),20);



    // Set positions of paddles and ball
    leftPaddle.setPosition(50.0f, WINDOW_HEIGHT / 2 - PADDLE_HEIGHT / 2);
    rightPaddle.setPosition(WINDOW_WIDTH - PADDLE_WIDTH - 50.0f, WINDOW_HEIGHT / 2 - PADDLE_HEIGHT / 2);
    ball.setPosition(WINDOW_WIDTH / 2 - BALL_DIAMETER, WINDOW_HEIGHT / 2 - BALL_DIAMETER);



    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

                // Handle keyboard input to control the paddles
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && leftPaddle.getPosition().y > 0)
            leftPaddle.move(0, -PADDLE_SPEED);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && leftPaddle.getPosition().y < WINDOW_HEIGHT - PADDLE_HEIGHT)
            leftPaddle.move(0, PADDLE_SPEED);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && rightPaddle.getPosition().y > 0)
            rightPaddle.move(0, -PADDLE_SPEED);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && rightPaddle.getPosition().y < WINDOW_HEIGHT - PADDLE_HEIGHT)
            rightPaddle.move(0, PADDLE_SPEED);



        //check for collisions with the wall
        if(ball.getPosition().y < BALL_DIAMETER/2 || ball.getPosition().y > WINDOW_HEIGHT - BALL_DIAMETER){
            BALL_SPEED_Y = BALL_SPEED_Y * -1;
        }
        //check for collision with the right paddle
        if(round(ball.getPosition().x) == rightPaddle.getPosition().x - PADDLE_WIDTH/2 - BALL_DIAMETER && 
                (ball.getPosition().y > rightPaddle.getPosition().y && ball.getPosition().y < rightPaddle.getPosition().y + PADDLE_HEIGHT))
        {
            BALL_SPEED_X = BALL_SPEED_X * -1;
        }

        //right paddle collision
        if(round(ball.getPosition().x) == (leftPaddle.getPosition().x + PADDLE_WIDTH/2 + BALL_DIAMETER/2) && 
                (ball.getPosition().y > leftPaddle.getPosition().y && ball.getPosition().y < leftPaddle.getPosition().y + PADDLE_HEIGHT))
        {
            BALL_SPEED_X = BALL_SPEED_X * -1;

        }

        if(ball.getPosition().x < -200){
            //std::cout << "Right Scores!!" << std::endl;
            scoreRight += 1;
            //std::cout << "    " << scoreLeft << "  -  " << scoreRight << std::endl << std::endl;
            scoreLine = std::to_string(scoreLeft) + "  -  " + std::to_string(scoreRight);
            Score.setString(scoreLine);
            ball.setPosition(WINDOW_WIDTH / 2 - BALL_DIAMETER, WINDOW_HEIGHT / 2 - BALL_DIAMETER);
        }

        if(ball.getPosition().x > WINDOW_WIDTH + 200){
            //std::cout << "Left Scores!!" << std::endl;
            scoreLeft += 1;
            //std::cout << "    " << scoreLeft << "  -  " << scoreRight << std::endl << std::endl;
            scoreLine = std::to_string(scoreLeft) + "  -  " + std::to_string(scoreRight);
            Score.setString(scoreLine);
            ball.setPosition(WINDOW_WIDTH / 2 - BALL_DIAMETER, WINDOW_HEIGHT / 2 - BALL_DIAMETER);
        }

        //move the ball
        ball.move(BALL_SPEED_X,BALL_SPEED_Y);
        //std::cout << "this is a debug" << std::endl;

        window.clear();
        //window.draw(ball);

        //draw the elements
        window.draw(leftPaddle);
        window.draw(rightPaddle);
        window.draw(ball);
        window.draw(Score);


        //display
        window.display();
    }

    return 0;
}