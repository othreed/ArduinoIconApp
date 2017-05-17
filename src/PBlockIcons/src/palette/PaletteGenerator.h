//
// Created by indrek on 13.05.2017.
//

#ifndef PBLOCKICONS_PALETTEGENERATOR_H
#define PBLOCKICONS_PALETTEGENERATOR_H


#include "src/screen/Colors.h"
#include "Arduino.h"



class PaletteGeneratorBase {


public:

    virtual uint8_t getWidth() = 0;
    virtual uint8_t getHeight() = 0;
    virtual void generateLine(uint8_t y) = 0;
    virtual RgbColor getPixel(uint8_t x) = 0;

};



template <uint8_t w, uint8_t h>
class PaletteGenerator : public PaletteGeneratorBase {

    static constexpr float hueSection = (h-1) / 6.0f;
    static constexpr uint16_t hueSection1 = hueSection * 1;
    static constexpr uint16_t hueSection2 = hueSection * 2;
    static constexpr uint16_t hueSection3 = hueSection * 3;
    static constexpr uint16_t hueSection4 = hueSection * 4;
    static constexpr uint16_t hueSection5 = hueSection * 5;

    uint8_t curY = 0;
    bool isHV; // true = HV (hue/value); false = HS (hue/saturation)
    RgbColor line[w];

public:

    PaletteGenerator(bool isHV) : isHV(isHV) {
    }


    uint8_t getWidth() { return w; };
    uint8_t getHeight() { return h; };


    void generateLine(uint8_t y) {
      curY = y;
      if (isHV) {
        initLineSV(curY);
      } else {
        initLineSH(curY);
      }
    }

    RgbColor getPixel(uint8_t x) {
      return line[x];
    };


private:


    void initLineSV(uint8_t y) {
      float hue = 0;
      float value = ((float)y)/(h-1);
      float hueMultiplier = calculateHueMultiplier(hue);

      float saturation = value;
      float dS = 0;
      if (w > 1) {
        saturation = 0;
        dS = (1.0f / (w - 1)) * value;
      }

      for (uint8_t saturationCnt = 0; saturationCnt < w; saturationCnt++) {
        line[saturationCnt] = calculateRGB(hue, hueMultiplier, saturation, value);
        saturation+=dS;
      }
    }


    void initLineSH(uint8_t hue) {
      float value = 1; // max brightness
      float hueMultiplier = calculateHueMultiplier(hue);
      float saturation = 0;
      float dS = (1.0f / (w - 1)) * value;

      for (uint8_t saturationCnt = 0; saturationCnt < w; saturationCnt++) {
        line[saturationCnt] = calculateRGB(hue, hueMultiplier, saturation, value);
        saturation+=dS;
      }
    }



    float calculateHueMultiplier(uint8_t hue) {
      float hueDiv = (hue / hueSection);
      uint16_t hueIntDiv = (uint16_t)hueDiv;
      float hueMod = hueIntDiv % 2 + (hueDiv - (hueIntDiv + (uint16_t)1));
      return (1.0f - abs(hueMod));
    }




    RgbColor calculateRGB(uint8_t hue, float hueMultiplier, float saturation, float value) {
      float X = saturation * hueMultiplier;

      float Rp;
      float Gp;
      float Bp;

      if (hue < hueSection1) {
        Rp = saturation;
        Gp = X;
        Bp = 0;
      } else if (hue < hueSection2) {
        Rp = X;
        Gp = saturation;
        Bp = 0;
      } else if (hue < hueSection3) {
        Rp = 0;
        Gp = saturation;
        Bp = X;
      } else if (hue < hueSection4) {
        Rp = 0;
        Gp = X;
        Bp = saturation;
      } else if (hue < hueSection5) {
        Rp = X;
        Gp = 0;
        Bp = saturation;
      } else {
        Rp = saturation;
        Gp = 0;
        Bp = X;
      }

      float m = value - saturation;
      if (m < 0) m = 0;

      return RgbColor(
          (Rp + m) * (uint16_t)31,
          (Gp + m) * (uint16_t)63,
          (Bp + m) * (uint16_t)31);
    }

};




#endif //PBLOCKICONS_PALETTEGENERATOR_H
