#include <SFML/Graphics.hpp>
#include <string>
#include <cctype>

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 400), "Temperature Conversion");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
        return -1;

    std::string input = "";
    std::string result = "";

    // ---------- TEXT ----------
    sf::Text title("TEMPERATURE CONVERSION", font, 26);
    title.setPosition(130, 20);
    title.setFillColor(sf::Color::Black);

    sf::Text inputLabel("Enter Temperature:", font, 20);
    inputLabel.setPosition(80, 100);
    inputLabel.setFillColor(sf::Color::Black);

    sf::Text inputText("", font, 22);
    inputText.setPosition(80, 140);
    inputText.setFillColor(sf::Color::Blue);

    sf::Text resultText("", font, 22);
    resultText.setPosition(80, 200);
    resultText.setFillColor(sf::Color::Red);

    // ---------- BUTTON STRUCT ----------
    struct Button
    {
        sf::RectangleShape box;
        sf::Text label;
    };

    auto makeButton = [&](float x, float y, const std::string& text)
    {
        Button b;
        b.box.setSize({200, 45});
        b.box.setPosition(x, y);
        b.box.setFillColor(sf::Color(170, 220, 255));
        b.label.setFont(font);
        b.label.setString(text);
        b.label.setCharacterSize(20);
        b.label.setFillColor(sf::Color::Black);
        b.label.setPosition(x + 20, y + 8);
        return b;
    };

    Button cToFBtn = makeButton(80, 260, "Celsius to Fahrenheit");
    Button fToCBtn = makeButton(320, 260, "Fahrenheit to Celsius");
    Button clearBtn = makeButton(200, 320, "Clear");

    // ---------- MAIN LOOP ----------
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // ---------- INPUT ----------
            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode == 8) // backspace
                {
                    if (!input.empty())
                        input.pop_back();
                }
                else if (event.text.unicode < 128 &&
                         (isdigit(event.text.unicode) || event.text.unicode == '.'))
                {
                    input += char(event.text.unicode);
                }
            }

            // ---------- MOUSE ----------
            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2f mouse(sf::Mouse::getPosition(window));

                if (cToFBtn.box.getGlobalBounds().contains(mouse) && !input.empty())
                {
                    float c = std::stof(input);
                    float f = (c * 9 / 5) + 32;
                    result = "Result: " + std::to_string(f) + " F";
                }

                if (fToCBtn.box.getGlobalBounds().contains(mouse) && !input.empty())
                {
                    float f = std::stof(input);
                    float c = (f - 32) * 5 / 9;
                    result = "Result: " + std::to_string(c) + " C";
                }

                if (clearBtn.box.getGlobalBounds().contains(mouse))
                {
                    input = "";
                    result = "";
                }
            }
        }

        inputText.setString(input);
        resultText.setString(result);

        // ---------- DRAW ----------
        window.clear(sf::Color(240, 240, 240));
        window.draw(title);
        window.draw(inputLabel);
        window.draw(inputText);
        window.draw(resultText);

        window.draw(cToFBtn.box);
        window.draw(cToFBtn.label);

        window.draw(fToCBtn.box);
        window.draw(fToCBtn.label);

        window.draw(clearBtn.box);
        window.draw(clearBtn.label);

        window.display();
    }

    return 0;
}