#include "devicepoller.h"
#include "SDL2/SDL.h"
#include <iostream>
#include "InputManager.h"



DevicePoller::DevicePoller(QObject *parent) : QObject(parent)
{

}

void DevicePoller::doin() {
    while (true) {
        SDL_Event event;
        std::vector<std::string> data;

        while(SDL_PollEvent(&event))

            std::cout << "got in here" <<std::endl;
            switch(event.type)
            {
                case SDL_JOYHATMOTION:
                case SDL_JOYBUTTONDOWN:
                case SDL_JOYBUTTONUP:
                case SDL_KEYDOWN:
                case SDL_KEYUP:
                case SDL_JOYAXISMOTION:
                case SDL_TEXTINPUT:
                case SDL_TEXTEDITING:
                case SDL_JOYDEVICEADDED:
                case SDL_JOYDEVICEREMOVED:
                    emit keyPressed(InputManager::getInstance()->parseEvent(event));
                    break;
                //Save that shit into a vector, then call the handleInput Function
            }
            //handleInput(data);
        }
    }

