// Header guard
#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <fstream>
#include <string>

#include "vec3.h"

/// Image class to help create image files in the PPM format.
/// The image is created by specifying a path to a file to create along
/// with the dimensions of the image expressed as the width and height
/// of the image in pixels. The image is constructed one pixel at a time.
/// It is up to the application program to manage the image's scanlines.
// Each pixel is written to the image starting at it's upper left corner
/// and ending at the image's lower right corner.
class Image {
 private:
  /// The output file name
  std::string file_name_;
  /// The width of the image in pixels (number of columns)
  int width_;
  /// The height of the image in pixels (number of rows)
  int height_;
  /// The image's aspect ratio expressed as width : height.
  double aspect_ratio_;
  /// The output file stream where the data gets written
  std::ofstream output_stream_;
  /// Utility method to print the header to the output file.
  void header();

 public:
  /// Initialize a new image file with the given path and dimensions.
  /// \param file_name The path to the file to create
  /// \param width The width of the image in pixels
  /// \param height The height of the image in pixels
  Image(const std::string& file_name, int width, int height);

  // Remove unwanted constructors, copy, and move operations.
  Image() = delete;
  Image(const Image& i) = delete;
  Image(Image&& i) = delete;
  Image& operator=(const Image& i) = delete;
  Image& operator=(Image&& i) = delete;

  /// Image destructor.
  /// If the output file is open, close it.
  ~Image() {
    if (is_open()) {
      close();
    }
  }

  /// Check to see if the file is open and ready for pixel data.
  /// \returns bool if the file stream is open else false
  /// \remark If the file exists, then it will be deleted/truncated and
  /// recreted. Be careful!
  bool is_open();

  /// Write the pixel values red, green, and blue to the next scanline.
  /// The values of \p red, \p green, and \p blue must be between 0 and 255.
  /// \param red The red channel's value as an int. [0, 255]
  /// \param green The green channel's value as an int. [0, 255]
  /// \param blue The blue channel's value as an int. [0, 255]
  void write(int red, int green, int blue);

  /// Write the pixel value \p c to the next scanline, \p c represents a
  /// three channel (red, green, blue) color pixel.
  /// The type Color is really a Vec3. We can access the red, green, and blue
  /// color channels with the methods r(), g(), b() respectively.
  /// Remember that these values are doubles (between 0 and 1) and need to
  /// be converted to integer values between 0 and 255.
  /// \param c A color pixel with 3 channels: red, green and blue.
  void write(const Color& c);

  /// Close the output file stream associated with the Image object
  void close();

  /// The width of the image in pixels
  /// \returns The width of the image in pixels
  int width() const;

  /// The height of the image in pixels
  /// \returns the height of the image in pixels
  int height() const;
};

// End header guard
#endif