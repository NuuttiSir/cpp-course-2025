/**
 * @file png.cpp
 * Implementation of the PNG class for the EasyPNG library.
 * @see http://zarb.org/~gc/html/libpng.html
 *
 * @author Chase Geigle
 * @date Created: Spring 2012
 *
 * @modified in Spring 2025 by Anna LaValle and Elmeri Uotila
 */

#include "png.h"

inline void epng_err(std::string const & err)
{
	std::cerr << "[EasyPNG]: " << err << std::endl;
}

size_t PNG::_index(size_t x, size_t y) const
{
  return (_width * y + x);
}

void PNG::_clear()
{
  _pixels.resize(0);
}


void PNG::_copy(PNG const & other)
{
  	_width = other._width;
	_height = other._height;
	_pixels = other._pixels;

}

void PNG::_init()
{
	_width = 0;
	_height = 0;
	_pixels.resize(0, RGBAPixel());
}

void PNG::_min_clamp_xy(size_t & width_arg, size_t & height_arg) const
{
	_min_clamp_x(width_arg);
	_min_clamp_y(height_arg);
}

void PNG::_min_clamp_x(size_t & width_arg) const
{
	if (width_arg <= 0)
	{
		epng_err("Warning: specified non-positive width, default of 1 being used");
		width_arg = 1;
	}

}

void PNG::_min_clamp_y(size_t & height_arg) const
{
	if (height_arg <= 0)
	{
		epng_err("Warning: specified non-positive height, default of 1 being used");
		height_arg = 1;
	}
}

void PNG::_clamp_xy(size_t & x, size_t & y) const
{
	size_t i = x;
	size_t j = y;
	if (x >= _width)
		x = _width - 1;
	if (y >= _height)
		y = _height - 1;

	if (i != x || j != y)
	{
		std::stringstream ss;
		ss << "Warning: attempted to access non-existent pixel "
			<< "(" << i << ", " << j << ");" <<std:: endl
			<< "            Truncating request to fit in the range [0,"
			<< (_width - 1) << "] x [0," << (_height - 1) << "]." << std::endl;
		epng_err(ss.str());  
	}
}

PNG::PNG()
{
	_init();
}

PNG::PNG(size_t width_arg, size_t height_arg)
{
	_width = width_arg;
	_height = height_arg;
	_pixels.resize(_height * _width, RGBAPixel());
}

PNG::PNG(std::string const & file_name)
{
	_read_file(file_name);
}

PNG::PNG(PNG const & other)
{
	_copy(other);
}

PNG::~PNG()
{
	_clear();
}

PNG const & PNG::operator=(PNG const & other)
{
	if (this != &other)
	{
		_clear();
		_copy(other);
	}
	return *this;
}

bool PNG::_pixels_same( const RGBAPixel & first, const RGBAPixel & second ) const {
    return first.red == second.red && first.green == second.green && first.blue == second.blue && first.alpha == second.alpha;
}

bool PNG::operator==(PNG const & other) const
{
	if (_width != other._width || _height != other._height)
		return false;
	for (size_t y = 0; y < _height; y++)
	{
		for (size_t x = 0; x < _width; x++)
		{
            if( !_pixels_same( _pixels[_index( x, y )], other._pixels[_index( x, y ) ]) )
				return false;
		}
	}
	return true;
}

bool PNG::operator!=(PNG const & other) const
{
	return !(*this == other);
}

RGBAPixel& PNG::operator()(size_t x, size_t y)
{
	_clamp_xy(x, y);
	return (_pixels[_index(x,y)]);
}
const RGBAPixel & PNG::operator()(size_t x, size_t y) const
{
	_clamp_xy(x, y);
	return (_pixels[_index(x,y)]);
}

bool PNG::readFromFile(std::string const & file_name)
{
	_clear();
	return _read_file(file_name);
}

bool PNG::_read_file(std::string const & file_name)
{
	// unfortunately, we need to break down to the C-code level here, since
	// libpng is written in C itself

	// we need to open the file in binary mode
	FILE * fp = fopen(file_name.c_str(), "rb");
	if (!fp)
	{
		epng_err("Failed to open " + file_name);
		return false;
	}

	// read in the header (max size of 8), use it to validate this as a PNG file
	png_byte header[8];
	fread(header, 1, 8, fp);
	if (png_sig_cmp(header, 0, 8))
	{
		epng_err("File is not a valid PNG file");
		fclose(fp);
		_init();
		return false;
	}

	// set up libpng structs for reading info
	png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL); if (!png_ptr)
	{
		epng_err("Failed to create read struct");
		fclose(fp);
		_init();
		return false;
	}

	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr)
	{
		epng_err("Failed to create info struct");
		png_destroy_read_struct(&png_ptr, NULL, NULL);
		fclose(fp);
		_init();
		return false;
	}

	// set error handling to not abort the entire program
	if (setjmp(png_jmpbuf(png_ptr)))
	{
		epng_err("Error initializing libpng io");
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		fclose(fp);
		_init();
		return false;
	}

	// initialize png reading
	png_init_io(png_ptr, fp);
	// let it know we've already read the first 8 bytes
	png_set_sig_bytes(png_ptr, 8);

	// read in the basic image info
	png_read_info(png_ptr, info_ptr);

	// convert to 8 bits
	png_byte bit_depth = png_get_bit_depth(png_ptr, info_ptr);
	if (bit_depth == 16)
		png_set_strip_16(png_ptr);

	// verify this is in RGBA format, and if not, convert it to RGBA
	png_byte color_type = png_get_color_type(png_ptr, info_ptr);
	if (color_type != PNG_COLOR_TYPE_RGBA && color_type != PNG_COLOR_TYPE_RGB)
	{
		if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA) {
			if (bit_depth < 8)
				png_set_expand(png_ptr);
			png_set_gray_to_rgb(png_ptr);
		}
		if (color_type == PNG_COLOR_TYPE_PALETTE)
			png_set_palette_to_rgb(png_ptr);
	}
	// convert tRNS to alpha channel
	if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
		png_set_tRNS_to_alpha(png_ptr);

	_width = png_get_image_width(png_ptr, info_ptr);
	_height = png_get_image_height(png_ptr, info_ptr);

	png_read_update_info(png_ptr, info_ptr);

	// begin reading in the image
	if (setjmp(png_jmpbuf(png_ptr)))
	{
		epng_err("Error reading image with libpng");
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		fclose(fp);
		_init();
		return false;
	}


	int bpr = png_get_rowbytes(png_ptr, info_ptr); // number of bytes in a row
	int numchannels = png_get_channels(png_ptr, info_ptr);

	// initialize our image storage
	_pixels.resize(_height * _width, RGBAPixel());
	png_byte * row = new png_byte[bpr];
	for (size_t y = 0; y < _height; y++)
	{
		png_read_row(png_ptr, row, NULL);
		png_byte * pix = row;
		for (size_t x = 0; x < _width; x++)
		{
			RGBAPixel & pixel = _pixels[_index(x,y)];
			if (numchannels == 1 || numchannels == 2)
			{
				// monochrome
				unsigned char color = (unsigned char) *pix++;
				pixel.red = color;
				pixel.green = color;
				pixel.blue = color;
				if (numchannels == 2)
					pixel.alpha = (unsigned char) *pix++;
				else
					pixel.alpha = 255;
			} 
			else if (numchannels == 3 || numchannels == 4) 
			{
				pixel.red = (unsigned char) *pix++;
				pixel.green = (unsigned char) *pix++;
				pixel.blue = (unsigned char) *pix++;
				if (numchannels == 4)
					pixel.alpha = (unsigned char) *pix++;
				else
					pixel.alpha = 255;
			}
		}
	}
	// cleanup
	delete [] row;
	png_read_end(png_ptr, NULL);
	png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
	fclose(fp);
	return true;
}
bool PNG::writeToFile(std::string const & file_name)
{
	FILE * fp = fopen(file_name.c_str(), "wb");
	if (!fp)
	{
		epng_err("Failed to open file " + file_name);
		return false;
	}

	png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr)
	{
		epng_err("Failed to create png struct");
		fclose(fp);
		return false;
	}

	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr)
	{
		epng_err("Failed to create png info struct");
		png_destroy_write_struct(&png_ptr, NULL);
		fclose(fp);
		return false;
	}

	if (setjmp(png_jmpbuf(png_ptr)))
	{
		epng_err("Error initializing libpng io");
		png_destroy_write_struct(&png_ptr, &info_ptr);
		fclose(fp);
		return false;
	}

	png_init_io(png_ptr, fp);

	// write header
	if (setjmp(png_jmpbuf(png_ptr)))
	{
		epng_err("Error writing image header");
		png_destroy_write_struct(&png_ptr, &info_ptr);
		fclose(fp);
		return false;
	}
	png_set_IHDR(png_ptr, info_ptr, _width, _height, 
			8,
			PNG_COLOR_TYPE_RGB_ALPHA, 
			PNG_INTERLACE_NONE, 
			PNG_COMPRESSION_TYPE_BASE,
			PNG_FILTER_TYPE_BASE);

	png_write_info(png_ptr, info_ptr);

	// write image
	if (setjmp(png_jmpbuf(png_ptr)))
	{
		epng_err("Failed to write image");
		png_destroy_write_struct(&png_ptr, &info_ptr);
		fclose(fp);
		return false;
	}

	int bpr = png_get_rowbytes(png_ptr, info_ptr);
	
	//we have to leave row pointers here as we are using libpng library
	png_byte * row = new png_byte[bpr];
	for (size_t y = 0; y < _height; y++)
	{
		for (size_t x = 0; x < _width; x++)
		{
			png_byte * pix = &(row[x*4]);
			pix[0] = _pixels[_index(x,y)].red;
			pix[1] = _pixels[_index(x,y)].green;
			pix[2] = _pixels[_index(x,y)].blue;
			pix[3] = _pixels[_index(x,y)].alpha;
		}
		png_write_row(png_ptr, row);
	}
	delete [] row;
	png_write_end(png_ptr, NULL);
	png_destroy_write_struct(&png_ptr, &info_ptr);
	fclose(fp);
	return true;
}

size_t PNG::width() const
{
	return _width;
}

size_t PNG::height() const
{
	return _height;
}

void PNG::resize(size_t width_arg, size_t height_arg) {
    // Clamp dimensions to acceptable values
    _min_clamp_xy(width_arg, height_arg);

    // Early return if the dimensions haven't changed
    if (width_arg == _width && height_arg == _height) {
        return;
    }

    
    // Create a new vector to hold the resized pixel array
    // Default constructor fills with white
    std::vector<RGBAPixel> new_pixels(width_arg * height_arg, RGBAPixel());

    // Determine dimensions to copy
    size_t min_width = std::min(width_arg, _width);
    size_t min_height = std::min(height_arg, _height);

    // Copy existing pixels into the new array
    for (size_t x = 0; x < min_width; ++x) {
        for (size_t y = 0; y < min_height; ++y) {
            new_pixels[x + y * width_arg] = _pixels[_index(x, y)];
        }
    }

    // Replace the old pixel storage with the new one
    _pixels = std::move(new_pixels);

    // Update width and height
    _width = width_arg;
    _height = height_arg;
}

