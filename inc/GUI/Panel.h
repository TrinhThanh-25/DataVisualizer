#ifndef PANEL_H
#define PANEL_H

#include <fstream>
#include <GUI/Button.h>
#include <GUI/inputBox.h>
#include <GUI/Console.h>

#include <string>
#include <sstream>

extern "C" {
    #include <tinyfiledialogs.h>
}

class Panel : public Console{
    public:
        Panel();
        virtual void draw()=0;
        virtual void update()=0;
        bool isBackPressed();
        virtual bool isAnyButtonPressed()=0;
        void updatePanel();
        void drawPanel();

        std::string loadFileContent(){
            std::string text="";
            const char *filterPatterns[] = {"*.txt"};
            const char *filePath = tinyfd_openFileDialog("Open a File","",1,filterPatterns,"Text Files",0);
            if (filePath) {
                std::ifstream in(filePath);
                std::string line;
                while (std::getline(in, line)) {
                    text += line + '\n';
                }
            }
            return text;
        }
    protected:
        Rectangle dataTitle;
        Button Back;

        Rectangle panelHolder;
};

#endif