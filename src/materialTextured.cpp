#include "materialTextured.h"


materialTextured::materialTextured(double ka, double kd, double ks, double exponent, double reflectance, double transmitance, double refraction, std::string name)
                                    :Material(ka,kd,ks, exponent, reflectance, transmitance, refraction), name{name}{
                                            decodeTwoSteps();
                                    };

std::string materialTextured::getName(){
    return name;
}

void materialTextured::decodeTwoSteps() {
  std::string path {"/scenes/"};
  path += name;
  const char * filename =  path.c_str();

  //load and decode
  unsigned error = lodepng::load_file(png, filename);
  if(!error) error = lodepng::decode(image, width, height, png);

  //if there's an error, display it
  if(error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

  //the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA..., use it as texture, draw it, ...
}

math::vec3<double> materialTextured::getPixels(double u, double v) {
    // Convert u, v to image coordinates
    unsigned x = static_cast<unsigned>(u * width);
    unsigned y = static_cast<unsigned>(v * height);

    // Check if the coordinates are within the image boundaries texture repeat ! 
    if (x >= width || y >= height) {
        x %= width;
        y %= height;
        
    }

    // Get the pixel color at the specified coordinates
    unsigned index = 4 * (y * width + x); // Each pixel has 4 bytes (RGBA)
    unsigned char r = image[index];
    unsigned char g = image[index + 1];
    unsigned char b = image[index + 2];
   

    double red = static_cast<double>(r) / 255;
    double green = static_cast<double>(g) / 255;
    double blue = static_cast<double>(b) / 255;

    math::vec3<double> color (red, green, blue);
    return color;
 
}