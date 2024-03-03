#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>

// Function to generate Collatz sequence
std::vector<int> collatzSequence(int n) {
    std::vector<int> sequence;
    while (n != 1) {
        sequence.push_back(n);
        if (n % 2 == 0) {
            n = n / 2;
        } else {
            n = 3 * n + 1;
        }
    }
    sequence.push_back(1); // Add the last element which is always 1
    return sequence;
}

// Function to draw the sequence as a graph
void drawSequence(sf::RenderWindow& window, const std::vector<int>& sequence) {
    // Calculate scale factors for drawing
    float scaleX = static_cast<float>(window.getSize().x) / sequence.size();
    float scaleY = static_cast<float>(window.getSize().y) / (*std::max_element(sequence.begin(), sequence.end()) + 10); // Add 10 to ensure some padding

    sf::VertexArray lines(sf::LinesStrip, sequence.size());
    for (size_t i = 0; i < sequence.size(); ++i) {
        lines[i].position = sf::Vector2f(i * scaleX, window.getSize().y - sequence[i] * scaleY);
        lines[i].color = sf::Color::White;
    }

    window.draw(lines);

    // Draw numbers above the spikes
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) { // Load a font for text display
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    for (size_t i = 1; i < sequence.size(); ++i) {
        if (sequence[i] > sequence[i - 1] && (i + 1 == sequence.size() || sequence[i] > sequence[i + 1])) {
            sf::Text text(std::to_string(sequence[i]), font, 20);
            text.setFillColor(sf::Color::White);
            text.setPosition(i * scaleX - 10, window.getSize().y - sequence[i] * scaleY - 30);
            window.draw(text);
        }
    }
}

int main() {
    int startNumber;
    std::cout << "Enter a positive integer to start with: ";
    std::cin >> startNumber;

    // Generate Collatz sequence
    std::vector<int> sequence = collatzSequence(startNumber);

    // Create SFML window (fullscreen)
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Collatz Sequence", sf::Style::Fullscreen);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        // Draw the sequence as a graph with numbers displayed above the spikes
        drawSequence(window, sequence);

        window.display();
    }

    return 0;
}
