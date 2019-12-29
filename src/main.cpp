#include <odroid_go.h>
#include "WiFiServer.h"
#include "WiFiClientSecure.h"

int xBasis = 0;
int yBasis = 0;
int zBasis = 150;
int cSize = 50;
int viewPlane = 64;
float angle = PI / 60; 

float cube3d[8][3] = {
    {xBasis - cSize, yBasis + cSize, zBasis - cSize},
    {xBasis + cSize, yBasis + cSize, zBasis - cSize},
    {xBasis - cSize, yBasis - cSize, zBasis - cSize},
    {xBasis + cSize, yBasis - cSize, zBasis - cSize},
    {xBasis - cSize, yBasis + cSize, zBasis + cSize},
    {xBasis + cSize, yBasis + cSize, zBasis + cSize},
    {xBasis - cSize, yBasis - cSize, zBasis + cSize},
    {xBasis + cSize, yBasis - cSize, zBasis + cSize},
};
unsigned char cube2d[8][2];

void setup()
{
    // put your setup code here, to run once:
    GO.begin();
    GO.lcd.clearDisplay();

    Serial.begin(115200);
    Serial.println("Cube Test!");

    delay(1000);
}

void loop()
{
    // put your main code here, to run repeatedly:
    xRotate3d(angle);
    rechne3dnach2d();
    zeichne2d();
    GO.update();
}

void xRotate3d(float q)
{
    float ty, tz, temp;
    for (byte i = 0; i < 8; i++)
    {
        ty = cube3d[i][1] - yBasis;
        tz = cube3d[i][2] - zBasis;
        temp = ty * cos(q) - tz * sin(q);
        tz = tv * sin(q) + tz * cos(q);
        ty = temp;
        ty = cube3d[i][1] + yBasis;
        tz = cube3d[i][2] + zBasis;

        /* code */
    }
}