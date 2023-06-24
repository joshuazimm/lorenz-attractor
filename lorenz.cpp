#include <iostream>
#include <cmath>
#include <array>
#include <SDL2/SDL.h>

void HSVtoRGB(float h, float s, float v, float& r, float& g, float& b) {
    int i = static_cast<int>(h / 60.0f) % 6;
    float f = (h / 60.0f) - static_cast<float>(i);
    float p = v * (1.0f - s);
    float q = v * (1.0f - f * s);
    float t = v * (1.0f - (1.0f - f) * s);

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

SDL_Color getColor(float currentLength, float maxLength) {
    float ratio = currentLength / maxLength;
    float hue = ratio * 80.0f + 250.0f; // purple
    //float hue = ratio * 360.0f; // full range
    float saturation = 1.0f;
    float value = 1.0f;

    float r, g, b;
    HSVtoRGB(hue, saturation, value, r, g, b);

    Uint8 red = static_cast<Uint8>(r * 255);
    Uint8 green = static_cast<Uint8>(g * 255);
    Uint8 blue = static_cast<Uint8>(b * 255);
    Uint8 alpha = 255;

    SDL_Color color = { red, green, blue, alpha };
    return color;
}

struct Node {
    std::array<float, 3> point1;
    std::array<float, 3> point2;
    float length;
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

    void deleteNode(std::array<float, 3> p1, std::array<float, 3> p2, int count) {
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

            previous = current;
            current = current->next;
        }
    }

    void draw(SDL_Renderer* renderer, float scaleX, float scaleY, float scaleZ, float cameraX, float cameraY, float cameraZ, float cameraPitch, 
                float cameraYaw, float focalX, float focalY, float focalZ, float fov) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        Node* current = head;
        float maxLength = 0.56f;
        while (current != nullptr) {
            SDL_Color color = getColor(current->length, maxLength);
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

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
};

class Particle {
public:
    Particle(std::array<float, 3> pos, float radius) : pos(pos), radius(radius) {}

    void update(std::array<float, 3> position) {
        pos = position;
    }

    std::array<float, 3> getPosition() const {
        return pos;
    }

    void displayPosition() const {
        std::cout << "Position: (" << pos[0] << ", " << pos[1] << ", " << pos[2] << ")" << std::endl;
    }

private:
    std::array<float, 3> pos;
    float radius;
};

class Lorenz {
public:
    Lorenz(Particle& particle, double sigma, double rho, double beta) : particle(particle), sigma(sigma), rho(rho), beta(beta) {}

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

    while (!quit) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
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
                    if (fov < 110.0f) {
                        fov += fovSpeed;
                    }
                }
                else if(event.wheel.y > 0) {
                    /*
                    float dirX = sin(cameraYaw) * cos(cameraPitch);
                    float dirY = sin(cameraPitch);
                    float dirZ = cos(cameraYaw) * cos(cameraPitch);
                    cameraX += movementSpeed * dirX;
                    cameraY += movementSpeed * dirY;
                    cameraZ += movementSpeed * dirZ;
                    */
                    if (fov > 10.0f) {
                        fov -= fovSpeed;
                    }
                }
            }
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
                }
            }
        }
        SDL_RenderClear(renderer);

        std::array<float, 3> preMovePos = particle.getPosition();
        lorenz.update(0.001f);
        std::array<float, 3> postMovePos = particle.getPosition();
        list.insert(preMovePos, postMovePos, length);

        list.draw(renderer, scaleX, scaleY, scaleZ, cameraX, cameraY, cameraZ, cameraPitch, cameraYaw, focalX, focalY, focalZ, fov);
        SDL_RenderPresent(renderer);

        SDL_Delay(1);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}