#include <odroid_go.h>
#include "WiFiServer.h"
#include "WiFiClientSecure.h"

// OpenHDZ/Arduino-experimentation

float xBasis = 0;
float yBasis = 0;
float zBasis = 100;
float cSize = 50;
int viewPlane = 32;
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
unsigned int cube2d[8][2];

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);
    Serial.println("Cube Test!");

    GO.begin();
    GO.lcd.clearDisplay();

    delay(50);
}

void xRotate3d(float q)
{
    float ty, tz, temp;
    for (byte i = 0; i < 8; i++)
    {
        ty = cube3d[i][1] - yBasis;
        tz = cube3d[i][2] - zBasis;
        temp = ty * cos(q) - tz * sin(q);
        tz = ty * sin(q) + tz * cos(q);
        ty = temp;
        cube3d[i][1] = ty + yBasis;
        cube3d[i][2] = tz + zBasis;
    }
}

void rechne3dnach2d()
{
    // Rechne die 2d Punkte //
    for (byte i = 0; i < 8; i++)
    {
        cube2d[i][0] = (unsigned int)((cube3d[i][0] * viewPlane / cube3d[i][2]) + (240 / 2));
        cube2d[i][1] = (unsigned int)((cube3d[i][1] * viewPlane / cube3d[i][2]) + (320 / 2));
    }
}

void zeichne2d()
{
    GO.lcd.clearDisplay();
    GO.lcd.drawLine(cube2d[0][0], cube2d[0][1], cube2d[1][0], cube2d[1][1], ILI9341_RED);
    GO.lcd.drawLine(cube2d[0][0], cube2d[0][1], cube2d[2][0], cube2d[2][1], ILI9341_RED);
    GO.lcd.drawLine(cube2d[0][0], cube2d[0][1], cube2d[4][0], cube2d[4][1], ILI9341_RED);
    GO.lcd.drawLine(cube2d[1][0], cube2d[1][1], cube2d[5][0], cube2d[5][1], ILI9341_RED);
    GO.lcd.drawLine(cube2d[1][0], cube2d[1][1], cube2d[3][0], cube2d[3][1], ILI9341_RED);
    GO.lcd.drawLine(cube2d[2][0], cube2d[2][1], cube2d[6][0], cube2d[6][1], ILI9341_RED);
    GO.lcd.drawLine(cube2d[2][0], cube2d[2][1], cube2d[3][0], cube2d[3][1], ILI9341_RED);
    GO.lcd.drawLine(cube2d[4][0], cube2d[4][1], cube2d[6][0], cube2d[6][1], ILI9341_RED);
    GO.lcd.drawLine(cube2d[4][0], cube2d[4][1], cube2d[5][0], cube2d[5][1], ILI9341_RED);
    GO.lcd.drawLine(cube2d[7][0], cube2d[7][1], cube2d[6][0], cube2d[6][1], ILI9341_RED);
    GO.lcd.drawLine(cube2d[7][0], cube2d[7][1], cube2d[3][0], cube2d[3][1], ILI9341_RED);
    GO.lcd.drawLine(cube2d[7][0], cube2d[7][1], cube2d[5][0], cube2d[5][1], ILI9341_RED);
}

void loop()
{
    // put your main code here, to run repeatedly:
    xRotate3d(angle);
    rechne3dnach2d();
    zeichne2d();
    delay(10);
    GO.update();
}
