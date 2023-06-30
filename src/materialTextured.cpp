#include "materialTextured.h"


materialTextured::materialTextured(double ka, double kd, double ks, double exponent, double reflectance, double transmitance, double refraction, std::string name)
                                    :Material(ka,kd,ks, exponent, reflectance, transmitance, refraction), name{name}{};

std::string materialTextured::getName(){
    return name;
}

void materialTextured::decodeTwoSteps() {
  const char * filename = name.c_str();
  unsigned width, height;

  //load and decode
  unsigned error = lodepng::load_file(png, filename);
  if(!error) error = lodepng::decode(image, width, height, png);

  //if there's an error, display it
  if(error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

  //the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA..., use it as texture, draw it, ...
}
