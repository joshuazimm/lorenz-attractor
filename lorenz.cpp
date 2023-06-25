#include <iostream>
#include <cmath>
<<<<<<< HEAD
#include <SDL2/SDL.h>

void HSVtoRGB(double h, double s, double v, double& r, double& g, double& b) {
    int i = static_cast<int>(h / 60.0f) % 6;
    double f = (h / 60.0f) - static_cast<double>(i);
    double p = v * (1.0f - s);
    double q = v * (1.0f - f * s);
    double t = v * (1.0f - (1.0f - f) * s);
=======
#include <array>
#include <SDL2/SDL.h>

void HSVtoRGB(float h, float s, float v, float& r, float& g, float& b) {
    int i = static_cast<int>(h / 60.0f) % 6;
    float f = (h / 60.0f) - static_cast<float>(i);
    float p = v * (1.0f - s);
    float q = v * (1.0f - f * s);
    float t = v * (1.0f - (1.0f - f) * s);
>>>>>>> 1ee45d6e8cc299e26d8cb34c0dbe0eaf20949889

    switch (i) {
        case 0:
            r = v;
            g = t;
            b = p;
            break;
        case 1:
            r = q;
            g = v;
            b = p;
            break;
        case 2:
            r = p;
            g = v;
            b = t;
            break;
        case 3:
            r = p;
            g = q;
            b = v;
            break;
        case 4:
            r = t;
            g = p;
            b = v;
            break;
        case 5:
            r = v;
            g = p;
            b = q;
            break;
    }
}

<<<<<<< HEAD
SDL_Color getColor(double currentLength, double maxLength) {
    double ratio = currentLength / maxLength;
    //double hue = ratio * 80 + 250; // purple
    double hue = ratio * 360; // full range
    double saturation = 1;
    double value = 1;

    double r, g, b;
=======
SDL_Color getColor(float currentLength, float maxLength) {
    float ratio = currentLength / maxLength;
    float hue = ratio * 80.0f + 250.0f; // purple
    //float hue = ratio * 360.0f; // full range
    float saturation = 1.0f;
    float value = 1.0f;

    float r, g, b;
>>>>>>> 1ee45d6e8cc299e26d8cb34c0dbe0eaf20949889
    HSVtoRGB(hue, saturation, value, r, g, b);

    Uint8 red = static_cast<Uint8>(r * 255);
    Uint8 green = static_cast<Uint8>(g * 255);
    Uint8 blue = static_cast<Uint8>(b * 255);
    Uint8 alpha = 255;

    SDL_Color color = { red, green, blue, alpha };
    return color;
}

struct Node {
<<<<<<< HEAD
    double point1[3];
    double point2[3];
    double length;
=======
    std::array<float, 3> point1;
    std::array<float, 3> point2;
    float length;
>>>>>>> 1ee45d6e8cc299e26d8cb34c0dbe0eaf20949889
    int counter;
    Node* next;
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() {
        head = nullptr;
    }

<<<<<<< HEAD
    double calculateLength(double p1[3], double p2[3]) {
        double dx = p2[0] - p1[0];
        double dy = p2[1] - p1[1];
        double dz = p2[2] - p1[2];
        double length = std::sqrt(dx * dx + dy * dy + dz * dz);
        return length;
    }

    void insert(double p1[3], double p2[3], int count) {
        Node* newNode = new Node;
        std::copy(p1, p1 + 3, newNode->point1);
        std::copy(p2, p2 + 3, newNode->point2);
=======
    float calculateLength(std::array<float, 3> p1, std::array<float, 3> p2) {
        float dx = p2[0] - p1[0];
        float dy = p2[1] - p1[1];
        float dz = p2[2] - p1[2];

        float length = std::sqrt(dx * dx + dy * dy + dz * dz);
        return length;
    }

    void insert(std::array<float, 3> p1, std::array<float, 3> p2, int count) {
        Node* newNode = new Node;
        newNode->point1 = p1;
        newNode->point2 = p2;
>>>>>>> 1ee45d6e8cc299e26d8cb34c0dbe0eaf20949889
        newNode->counter = count;
        newNode->length = calculateLength(p1, p2);
        newNode->next = nullptr;

        if (head == nullptr) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current->counter--;
                if (current->counter < 1) {
                    deleteNode(current->point1, current->point2, current->counter);
                }
                current = current->next;
            }
            current->counter--;
            if (current->counter < 1) {
                deleteNode(current->point1, current->point2, current->counter);
            }
            current->next = newNode;
        }
    }

<<<<<<< HEAD
    void deleteNode(double p1[3], double p2[3], int count) {
=======
    void deleteNode(std::array<float, 3> p1, std::array<float, 3> p2, int count) {
>>>>>>> 1ee45d6e8cc299e26d8cb34c0dbe0eaf20949889
        Node* current = head;
        Node* previous = nullptr;

        while (current != nullptr) {
            if (current->point1 == p1 && current->point2 == p2 && current->counter == count) {
                if (previous == nullptr) {
                    head = current->next;
                } else {
                    previous->next = current->next;
                }
                delete current;
                return;
            }
<<<<<<< HEAD
=======

>>>>>>> 1ee45d6e8cc299e26d8cb34c0dbe0eaf20949889
            previous = current;
            current = current->next;
        }
    }

<<<<<<< HEAD
    void draw(SDL_Renderer* renderer, double scaleX, double scaleY, double scaleZ, double cameraX, double cameraY, double cameraZ, double cameraPitch, 
                double cameraYaw, double focalX, double focalY, double focalZ, double fov) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        Node* current = head;
        double maxLength = 1.68;
=======
    void draw(SDL_Renderer* renderer, float scaleX, float scaleY, float scaleZ, float cameraX, float cameraY, float cameraZ, float cameraPitch, 
                float cameraYaw, float focalX, float focalY, float focalZ, float fov) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        Node* current = head;
        float maxLength = 0.56f;
>>>>>>> 1ee45d6e8cc299e26d8cb34c0dbe0eaf20949889
        while (current != nullptr) {
            SDL_Color color = getColor(current->length, maxLength);
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

<<<<<<< HEAD
            double halfFOV = fov / 2.0;
            double focalLength = 1.0 / tan(halfFOV * (M_PI / 180.0));

            double x1 = current->point1[0] - focalX - cameraX;
            double y1 = current->point1[1] - focalY - cameraY;
            double z1 = current->point1[2] - focalZ - cameraZ;

            double x2 = current->point2[0] - focalX - cameraX;
            double y2 = current->point2[1] - focalY - cameraY;
            double z2 = current->point2[2] - focalZ - cameraZ;

            double rotatedX1 = x1 * cos(cameraYaw) - z1 * sin(cameraYaw);
            double rotatedZ1 = x1 * sin(cameraYaw) + z1 * cos(cameraYaw);
            double rotatedY1 = y1 * cos(cameraPitch) - rotatedZ1 * sin(cameraPitch);
            double rotatedZ2 = y1 * sin(cameraPitch) + rotatedZ1 * cos(cameraPitch);

            double rotatedX2 = x2 * cos(cameraYaw) - z2 * sin(cameraYaw);
            double rotatedZ3 = x2 * sin(cameraYaw) + z2 * cos(cameraYaw);
            double rotatedY2 = y2 * cos(cameraPitch) - rotatedZ3 * sin(cameraPitch);
            double rotatedZ4 = y2 * sin(cameraPitch) + rotatedZ3 * cos(cameraPitch);

            double projectedX1 = (rotatedX1 / (rotatedZ2 + scaleZ)) * focalLength * scaleX + scaleX;
            double projectedY1 = (rotatedY1 / (rotatedZ2 + scaleZ)) * focalLength * scaleY + scaleY;

            double projectedX2 = (rotatedX2 / (rotatedZ4 + scaleZ)) * focalLength * scaleX + scaleX;
            double projectedY2 = (rotatedY2 / (rotatedZ4 + scaleZ)) * focalLength * scaleY + scaleY;
=======
            float halfFOV = fov / 2.0f;
            float focalLength = 1.0f / tan(halfFOV * (M_PI / 180.0f));

            float x1 = current->point1[0] - focalX - cameraX;
            float y1 = current->point1[1] - focalY - cameraY;
            float z1 = current->point1[2] - focalZ - cameraZ;

            float x2 = current->point2[0] - focalX - cameraX;
            float y2 = current->point2[1] - focalY - cameraY;
            float z2 = current->point2[2] - focalZ - cameraZ;

            float rotatedX1 = x1 * cos(cameraYaw) - z1 * sin(cameraYaw);
            float rotatedZ1 = x1 * sin(cameraYaw) + z1 * cos(cameraYaw);
            float rotatedY1 = y1 * cos(cameraPitch) - rotatedZ1 * sin(cameraPitch);
            float rotatedZ2 = y1 * sin(cameraPitch) + rotatedZ1 * cos(cameraPitch);

            float rotatedX2 = x2 * cos(cameraYaw) - z2 * sin(cameraYaw);
            float rotatedZ3 = x2 * sin(cameraYaw) + z2 * cos(cameraYaw);
            float rotatedY2 = y2 * cos(cameraPitch) - rotatedZ3 * sin(cameraPitch);
            float rotatedZ4 = y2 * sin(cameraPitch) + rotatedZ3 * cos(cameraPitch);

            float projectedX1 = (rotatedX1 / (rotatedZ2 + scaleZ)) * focalLength * scaleX + scaleX;
            float projectedY1 = (rotatedY1 / (rotatedZ2 + scaleZ)) * focalLength * scaleY + scaleY;

            float projectedX2 = (rotatedX2 / (rotatedZ4 + scaleZ)) * focalLength * scaleX + scaleX;
            float projectedY2 = (rotatedY2 / (rotatedZ4 + scaleZ)) * focalLength * scaleY + scaleY;
>>>>>>> 1ee45d6e8cc299e26d8cb34c0dbe0eaf20949889

            SDL_RenderDrawLine(renderer, projectedX1, projectedY1, projectedX2, projectedY2);

            current = current->next;
        }    
    }

    void display() {
        Node* current = head;
        while (current != nullptr) {
            std::cout << "Point 1: (" << current->point1[0] << ", " << current->point1[1] << ", " << current->point1[2] << "), ";
            std::cout << "Point 2: (" << current->point2[0] << ", " << current->point2[1] << ", " << current->point2[2] << "), ";
            std::cout << "Counter: " << current->counter << ", ";
            std::cout << "Length: " << current->length << std::endl;
            current = current->next;
        }
    }
<<<<<<< HEAD

    void clear() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
    }
=======
>>>>>>> 1ee45d6e8cc299e26d8cb34c0dbe0eaf20949889
};

class Particle {
public:
<<<<<<< HEAD
    Particle(double pos[3], double radius) : radius(radius) {
        std::copy(pos, pos + 3, this->pos);
    }

    void update(double position[3]) {
        std::copy(position, position + 3, pos);
    }

    void getPosition(double &x, double &y, double &z) const {
        x = pos[0];
        y = pos[1];
        z = pos[2];
=======
    Particle(std::array<float, 3> pos, float radius) : pos(pos), radius(radius) {}

    void update(std::array<float, 3> position) {
        pos = position;
    }

    std::array<float, 3> getPosition() const {
        return pos;
>>>>>>> 1ee45d6e8cc299e26d8cb34c0dbe0eaf20949889
    }

    void displayPosition() const {
        std::cout << "Position: (" << pos[0] << ", " << pos[1] << ", " << pos[2] << ")" << std::endl;
    }

private:
<<<<<<< HEAD
    double pos[3];
    double radius;
=======
    std::array<float, 3> pos;
    float radius;
>>>>>>> 1ee45d6e8cc299e26d8cb34c0dbe0eaf20949889
};

class Lorenz {
public:
    Lorenz(Particle& particle, double sigma, double rho, double beta) : particle(particle), sigma(sigma), rho(rho), beta(beta) {}

<<<<<<< HEAD
    void update(double t) {
        double xl, yl, zl;
        particle.getPosition(xl, yl, zl);
        double dx = sigma * (yl - xl);
        double dy = xl * (rho - zl) - yl;
        double dz = xl * yl - beta * zl;
        xl += dx * t;
        yl += dy * t;
        zl += dz * t;
        double position2[3] = { xl, yl, zl };
        particle.update(position2);
    }

    void integrate(double dt, int steps, double &xi, double &yi, double &zi) {
        double averagePosition[3] = {0, 0, 0};
        for (int i = 0; i < steps; i++) {
            update(dt);
            particle.getPosition(xi, yi, zi);
            averagePosition[0] += xi;
            averagePosition[1] += yi;
            averagePosition[2] += zi;
        }

        for (int i = 0; i < 3; i++) {
            averagePosition[i] /= steps;
        } 
        xi = averagePosition[0];
        yi = averagePosition[1];
        zi = averagePosition[2];
    }

    void setup(double &focalX, double &focalY, double &focalZ) {
        double x = 0.0, y = 0.0, z = 0.0;
        integrate(0.005, 30000, x, y, z);
        focalX = x;
        focalY = y;
        focalZ = z;
    }

    void reset(double &cameraX, double &cameraY, double &cameraZ, double &cameraPitch, double &cameraYaw, 
                double &fov, double focalX, double focalY) {
        cameraX = focalX;
        cameraY = focalY;
        cameraZ = 0;
        cameraYaw = 0.0;
        cameraPitch = 0.0;
        fov = 60.0;
    }

=======
    void update(float t) {
        std::array<float, 3> position = particle.getPosition();
        float x = position[0];
        float y = position[1];
        float z = position[2];
        double dx = sigma * (y - x);
        double dy = x * (rho - z) - y;
        double dz = x * y - beta * z;
        x += dx * t;
        y += dy * t;
        z += dz * t;
        std::array<float, 3> position2 = { x, y, z };
        particle.update(position2);
    }
>>>>>>> 1ee45d6e8cc299e26d8cb34c0dbe0eaf20949889
private:
    Particle& particle;
    double sigma;
    double rho;
    double beta;
};


int main() {
    bool quit = false;
    SDL_Event event;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
<<<<<<< HEAD
    int const windowWidth = 2200;
    int const windowHeight = 1200;
    window = SDL_CreateWindow("Trails", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

    double cameraX = 0.0, cameraY = 0.0, cameraZ = 0;
    double focalX = 0.0, focalY = 0.0, focalZ = 0.0;
    double cameraYaw = 0.0, cameraPitch = 0.0;
    double fov = 60.0;
    double const fovSpeed = 1.0;
    double const scaleX = windowWidth / 2.0, scaleY = windowHeight / 2.0, scaleZ = windowHeight / 2.0;
    double const rotationSpeed = 0.01;
    double const movementSpeedF = 10.0, movementSpeedS = 5.0;
    int mouseX = 0, mouseY = 0, prevMouseX = 0, prevMouseY = 0;
    
    int const length = 50000; // length of trail drawing the attractor
    double sigma = 10.0, rho = 32.0, beta = 8.0 / 3.0;

    double x = 0, y = 0, z = 0;
    LinkedList list;
    double pos[3] = {1.0, 1.0, 1.0};
    Particle particle(pos, 1.0);
    Lorenz lorenz(particle, sigma, rho, beta);
    lorenz.setup(focalX, focalY, focalZ);
    lorenz.reset(cameraX, cameraY, cameraZ, cameraPitch, cameraYaw, fov, focalX, focalY);
=======
    int const windowWidth = 1500;
    int const windowHeight = 1000;
    window = SDL_CreateWindow("Trails", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

    float cameraX = -2.0f;
    float cameraY = -2.0f;
    float cameraZ = 0;
    float focalX = -2.0f;
    float focalY = -2.0f;
    float focalZ = 25.0f;
    float cameraYaw = 0;
    float cameraPitch = 0;
    float fov = 60.0f;
    float const fovSpeed = 1.0f;
    float const scaleX = windowWidth / 2.0f;
    float const scaleY = windowHeight / 2.0f;
    float const scaleZ = windowHeight / 2.0f;
    float prevMouseX = 0;
    float prevMouseY = 0;
    float rotationSpeed = 0.01;
    float movementSpeed = 3;
    int mouseX, mouseY;
    

    int const length = 30000;

    LinkedList list;
    std::array<float, 3> pos = {1.0f, 1.0f, 1.0f};
    Particle particle(pos, 1.0f);
    Lorenz lorenz(particle, 10.0f, 32.0f, 8.0f / 3.0f);
>>>>>>> 1ee45d6e8cc299e26d8cb34c0dbe0eaf20949889

    while (!quit) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
<<<<<<< HEAD
            if (event.type == SDL_MOUSEWHEEL) {
                if (event.wheel.y < 0) { // scroll up / zoom in
=======
            if(event.type == SDL_MOUSEWHEEL) {
                if(event.wheel.y < 0) {
                    /*
                    float dirX = sin(cameraYaw) * cos(cameraPitch);
                    float dirY = sin(cameraPitch);
                    float dirZ = cos(cameraYaw) * cos(cameraPitch);
                    cameraX -= movementSpeed * dirX;
                    cameraY -= movementSpeed * dirY;
                    cameraZ -= movementSpeed * dirZ;
                    */
>>>>>>> 1ee45d6e8cc299e26d8cb34c0dbe0eaf20949889
                    if (fov < 110.0f) {
                        fov += fovSpeed;
                    }
                }
<<<<<<< HEAD
                else if (event.wheel.y > 0) { // scroll down / zoom out
=======
                else if(event.wheel.y > 0) {
                    /*
                    float dirX = sin(cameraYaw) * cos(cameraPitch);
                    float dirY = sin(cameraPitch);
                    float dirZ = cos(cameraYaw) * cos(cameraPitch);
                    cameraX += movementSpeed * dirX;
                    cameraY += movementSpeed * dirY;
                    cameraZ += movementSpeed * dirZ;
                    */
>>>>>>> 1ee45d6e8cc299e26d8cb34c0dbe0eaf20949889
                    if (fov > 10.0f) {
                        fov -= fovSpeed;
                    }
                }
            }
<<<<<<< HEAD
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.scancode == SDL_SCANCODE_S) {
                    double dirX = sin(cameraYaw) * cos(cameraPitch);
                    double dirY = sin(cameraPitch);
                    double dirZ = cos(cameraYaw) * cos(cameraPitch);
                    cameraX -= movementSpeedF * dirX;
                    cameraY -= movementSpeedF * dirY;
                    cameraZ -= movementSpeedF * dirZ;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_W) {
                    double dirX = sin(cameraYaw) * cos(cameraPitch);
                    double dirY = sin(cameraPitch);
                    double dirZ = cos(cameraYaw) * cos(cameraPitch);
                    cameraX += movementSpeedF * dirX;
                    cameraY += movementSpeedF * dirY;
                    cameraZ += movementSpeedF * dirZ;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_A) {
                    double dirX = -cos(cameraYaw);
                    double dirZ = sin(cameraYaw);
                    cameraX += movementSpeedS * dirX;
                    cameraZ += movementSpeedS * dirZ;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_D) {
                    double dirX = cos(cameraYaw);
                    double dirZ = -sin(cameraYaw);
                    cameraX += movementSpeedS * dirX;
                    cameraZ += movementSpeedS * dirZ;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_R) { //reset camera
                    lorenz.reset(cameraX, cameraY, cameraZ, cameraPitch, cameraYaw, fov, focalX, focalY);
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_C) { //reset camera
                    list.clear();
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_O) { // sigma up
                    if (sigma < 90) {
                        sigma += 0.5;
                    }
                    list.clear();
                    Particle particle(pos, 1.0);
                    Lorenz lorenz(particle, sigma, rho, beta);
                    lorenz.setup(focalX, focalY, focalZ);
                    lorenz.reset(cameraX, cameraY, cameraZ, cameraPitch, cameraYaw, fov, focalX, focalY);
                    std::cout << "Sigma: " << sigma << std::endl;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_L) { // sigma down
                    if (sigma > 0.5) {
                        sigma -= 0.5;
                    }
                    list.clear();
                    Particle particle(pos, 1.0);
                    Lorenz lorenz(particle, sigma, rho, beta);
                    lorenz.setup(focalX, focalY, focalZ);
                    lorenz.reset(cameraX, cameraY, cameraZ, cameraPitch, cameraYaw, fov, focalX, focalY);
                    std::cout << "Sigma: " << sigma << std::endl;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_I) { // rho up
                    if (rho < 60) {
                        rho += 1.0;
                    }
                    list.clear();
                    Particle particle(pos, 1.0);
                    Lorenz lorenz(particle, sigma, rho, beta);
                    lorenz.setup(focalX, focalY, focalZ);
                    lorenz.reset(cameraX, cameraY, cameraZ, cameraPitch, cameraYaw, fov, focalX, focalY);
                    std::cout << "Rho: " << rho << std::endl;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_K) { // rho down
                    if (rho > 1) {
                        rho -= 1.0;
                    }
                    list.clear();
                    Particle particle(pos, 1.0);
                    Lorenz lorenz(particle, sigma, rho, beta);
                    lorenz.setup(focalX, focalY, focalZ);
                    lorenz.reset(cameraX, cameraY, cameraZ, cameraPitch, cameraYaw, fov, focalX, focalY);
                    std::cout << "Rho: " << rho << std::endl;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_U) { // beta up
                    beta += 0.1;
                    list.clear();
                    Particle particle(pos, 1.0);
                    Lorenz lorenz(particle, sigma, rho, beta);
                    lorenz.setup(focalX, focalY, focalZ);
                    lorenz.reset(cameraX, cameraY, cameraZ, cameraPitch, cameraYaw, fov, focalX, focalY);
                    std::cout << "Beta: " << beta << std::endl;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_J) { // beta down
                    beta -= 0.1;
                    list.clear();
                    Particle particle(pos, 1.0);
                    Lorenz lorenz(particle, sigma, rho, beta);
                    lorenz.setup(focalX, focalY, focalZ);
                    lorenz.reset(cameraX, cameraY, cameraZ, cameraPitch, cameraYaw, fov, focalX, focalY);
                    std::cout << "Beta: " << beta << std::endl;
                }
            }
            if (event.type == SDL_MOUSEMOTION) {
                Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);
                if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) {
                    cameraYaw += rotationSpeed * (mouseX - prevMouseX);
                    cameraPitch += rotationSpeed * (mouseY - prevMouseY);
                    prevMouseX = mouseX;
                    prevMouseY = mouseY;
                }
                else {
                    prevMouseX = mouseX;
                    prevMouseY = mouseY;
=======
            if (event.type == SDL_MOUSEMOTION) {
                Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);
                if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) {
                    float mouseXf = static_cast<float>(mouseX);
                    float mouseYf = static_cast<float>(mouseY);
                    cameraYaw += rotationSpeed * (mouseXf - prevMouseX);
                    cameraPitch += rotationSpeed * (mouseYf - prevMouseY);
                    prevMouseX = mouseXf;
                    prevMouseY = mouseYf;
                }
                else {
                    prevMouseX = static_cast<float>(mouseX);
                    prevMouseY = static_cast<float>(mouseY);
>>>>>>> 1ee45d6e8cc299e26d8cb34c0dbe0eaf20949889
                }
            }
        }
        SDL_RenderClear(renderer);

<<<<<<< HEAD
        double x, y, z;
        particle.getPosition(x, y, z);
        double preMovePos[3] = {x, y, z};
        lorenz.update(0.003);
        particle.getPosition(x, y, z);
        double postMovePos[3] = {x, y, z};
=======
        std::array<float, 3> preMovePos = particle.getPosition();
        lorenz.update(0.001f);
        std::array<float, 3> postMovePos = particle.getPosition();
>>>>>>> 1ee45d6e8cc299e26d8cb34c0dbe0eaf20949889
        list.insert(preMovePos, postMovePos, length);

        list.draw(renderer, scaleX, scaleY, scaleZ, cameraX, cameraY, cameraZ, cameraPitch, cameraYaw, focalX, focalY, focalZ, fov);
        SDL_RenderPresent(renderer);

        SDL_Delay(1);
    }

<<<<<<< HEAD
    list.clear();
=======
>>>>>>> 1ee45d6e8cc299e26d8cb34c0dbe0eaf20949889
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}