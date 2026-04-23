#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <algorithm>

using namespace std;

const double PI = 3.14159265358979323846;

struct Point3D {
    double x, y, z;
    Point3D(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
};

string setToString(const set<int>& s) {
    if (s.empty()) return "{}";
    string res = "";
    for (int x : s) res += to_string(x);
    return res;
}

vector<set<int>> generateSubsets(int maxSize) {
    vector<set<int>> result;
    for (int mask = 0; mask < (1 << 10); mask++) {
        set<int> subset;
        for (int i = 0; i < 10; i++)
            if (mask & (1 << i)) subset.insert(i);
        if ((int)subset.size() <= maxSize)
            result.push_back(subset);
    }
    return result;
}

vector<pair<int, int>> generateEdges(const vector<set<int>>& subsets) {
    vector<pair<int, int>> edges;
    for (size_t i = 0; i < subsets.size(); i++) {
        for (size_t j = 0; j < subsets.size(); j++) {
            if (i == j) continue;
            if (subsets[j].size() == subsets[i].size() + 1) {
                bool isSubset = true;
                for (int x : subsets[i])
                    if (subsets[j].find(x) == subsets[j].end()) { isSubset = false; break; }
                if (isSubset) edges.push_back({i, j});
            }
        }
    }
    return edges;
}

vector<Point3D> placeOnSphere(const vector<set<int>>& subsets, double radius) {
    vector<Point3D> points(subsets.size());
    int n = subsets.size();
    double phiGolden = PI * (3 - sqrt(5));
    for (int i = 0; i < n; i++) {
        double y = 1 - (i / (double)(n - 1)) * 2;
        double radiusAtY = sqrt(1 - y*y);
        double theta = i * phiGolden * 2;
        double x = cos(theta) * radiusAtY;
        double z = sin(theta) * radiusAtY;
        points[i] = Point3D(x * radius, y * radius, z * radius);
    }
    return points;
}

sf::Vector2f project(const Point3D& p, double distance, int screenW, int screenH) {
    double factor = distance / (distance + p.z);
    double x2d = p.x * factor;
    double y2d = p.y * factor;
    return sf::Vector2f(screenW / 2 + x2d, screenH / 2 + y2d);
}

Point3D rotate(const Point3D& p, double yaw, double pitch) {
    double cosY = cos(yaw), sinY = sin(yaw);
    double cosP = cos(pitch), sinP = sin(pitch);
    double x1 = p.x * cosY + p.z * sinY;
    double z1 = -p.x * sinY + p.z * cosY;
    double y1 = p.y;
    double y2 = y1 * cosP - z1 * sinP;
    double z2 = y1 * sinP + z1 * cosP;
    return Point3D(x1, y2, z2);
}

int main() {
    int screenW = 600, screenH = 800;
    sf::RenderWindow window(sf::VideoMode(screenW, screenH), "Vu Tru Cau - Tap Hop Con");
    window.setFramerateLimit(60);

    int maxSize = 3;
    auto subsets = generateSubsets(maxSize);
    auto edges = generateEdges(subsets);
    double radius = 130.0;  // Bán kính cầu nhỏ lại cho vừa màn hình
    auto spherePoints = placeOnSphere(subsets, radius);

    sf::Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf"))
        cout << "Khong load duoc font, text se khong hien" << endl;

    vector<sf::CircleShape> nodes(subsets.size());
    vector<sf::Text> texts(subsets.size());
    for (size_t i = 0; i < subsets.size(); i++) {
        nodes[i].setRadius(8);  // Node nhỏ hơn
        nodes[i].setFillColor(sf::Color(80, 150, 250, 200));
        nodes[i].setOutlineColor(sf::Color::White);
        nodes[i].setOutlineThickness(1);
        nodes[i].setOrigin(8, 8);

        texts[i].setFont(font);
        texts[i].setString(setToString(subsets[i]));
        texts[i].setCharacterSize(10);
        texts[i].setFillColor(sf::Color::White);
        texts[i].setOrigin(texts[i].getLocalBounds().width/2, texts[i].getLocalBounds().height/2);
    }

    double yaw = 0, pitch = 0;
    bool dragging = false;
    sf::Vector2i lastMouse;
    double distance = 300;  // Khoảng cách camera

    sf::Text info;
    info.setFont(font);
    info.setCharacterSize(14);
    info.setFillColor(sf::Color::Yellow);
    info.setPosition(5, 5);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                dragging = true;
                lastMouse = sf::Mouse::getPosition(window);
            }
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                dragging = false;
            }
            if (event.type == sf::Event::MouseMoved && dragging) {
                sf::Vector2i newMouse = sf::Mouse::getPosition(window);
                yaw += (newMouse.x - lastMouse.x) * 0.008;
                pitch += (newMouse.y - lastMouse.y) * 0.008;
                if (pitch > PI/2) pitch = PI/2;
                if (pitch < -PI/2) pitch = -PI/2;
                lastMouse = newMouse;
            }

            if (event.type == sf::Event::MouseWheelScrolled) {
                distance -= event.mouseWheelScroll.delta * 20;
                if (distance < 150) distance = 150;
                if (distance > 600) distance = 600;
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                for (size_t i = 0; i < subsets.size(); i++) {
                    sf::Vector2f nodePos = nodes[i].getPosition();
                    float dx = mousePos.x - nodePos.x;
                    float dy = mousePos.y - nodePos.y;
                    if (sqrt(dx*dx + dy*dy) <= 8) {
                        info.setString("Tap hop: " + setToString(subsets[i]));
                        break;
                    }
                }
            }
        }

        vector<sf::Vector2f> projected(subsets.size());
        vector<Point3D> rotated(subsets.size());
        for (size_t i = 0; i < subsets.size(); i++) {
            rotated[i] = rotate(spherePoints[i], yaw, pitch);
            projected[i] = project(rotated[i], distance, screenW, screenH);
        }

        for (size_t i = 0; i < subsets.size(); i++) {
            nodes[i].setPosition(projected[i]);
            texts[i].setPosition(projected[i]);
            double brightness = 0.5 + 0.5 * (distance / (distance + rotated[i].z));
            int r = 80 * brightness, g = 150 * brightness, b = 250 * brightness;
            nodes[i].setFillColor(sf::Color(r, g, b, 200));
        }

        window.clear(sf::Color(10, 10, 30));

        for (auto& e : edges) {
            sf::Vertex line[] = {
                sf::Vertex(projected[e.first], sf::Color(150, 150, 200, 80)),
                sf::Vertex(projected[e.second], sf::Color(150, 150, 200, 80))
            };
            window.draw(line, 2, sf::Lines);
        }

        for (size_t i = 0; i < subsets.size(); i++) {
            window.draw(nodes[i]);
            window.draw(texts[i]);
        }

        window.setView(window.getDefaultView());
        window.draw(info);

        window.display();
    }

    return 0;
}
