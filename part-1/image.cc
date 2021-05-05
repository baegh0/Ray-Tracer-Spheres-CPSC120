
#include "image.h"

// See the header file for documentation.

void Image::header() {
  if (is_open()) {
    output_stream_ << "P3\n";
    output_stream_ << "# The P3 means colors are in ACII, then the number\n";
    output_stream_ << "# of columns (" << width_ << ") and the number of\n";
    output_stream_ << "# rows (" << height_ << "), then 255 for the max\n";
    output_stream_ << "# color, then RGB triples.\n";
    output_stream_ << width_ << " " << height_ << "\n255\n";
  }
}

Image::Image(const std::string& file_name, int width, int height) {
  file_name_ = file_name;
  width_ = width;
  height_ = height;
  aspect_ratio_ = double(width_) / double(height_);
  output_stream_ = std::ofstream(file_name_);
  header();
}

bool Image::is_open() { return output_stream_.is_open(); }

void Image::write(int red, int green, int blue) {
  output_stream_ << red << " " << green << " "
                 << " " << blue << "\n";
}

void Image::write(const Color& c) {
  // Get the color value, multiple by 255.0 and use lround() to round
  // to the nearest integer.
  // Write the values out to the output_stream.
  auto r = lround(255.0 * c.r());
  auto g = lround(255.0 * c.g());
  auto b = lround(255.0 * c.b());
  output_stream_ << r << " " << g << " " << b << "\n";
}

void Image::close() { output_stream_.close(); }

int Image::width() const { return width_; }

int Image::height() const { return height_; }
