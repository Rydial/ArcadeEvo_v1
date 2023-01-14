#include "Util_Image.h"

#include "Debug.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// Utilities ///////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


std::optional<Image> utilities::loadImage(std::string_view filePath)
{
    // Load Image into an Array of Pixels (and Retrieve Image Information)
    Image image {};
    const auto desiredComposition {STBI_rgb_alpha};
    image.pixels = stbi_load(
        filePath.data(),
        &image.width,
        &image.height,
        &image.composition,
        desiredComposition);

	// Validate Image
	if (!image.pixels)
	{
        DEBUG_PRINT("Failed to load image file: %", filePath);
		return std::nullopt;
	}

    return std::make_optional(std::move(image));
}


void utilities::freeImage(const Image& image)
{
    // Free Pixel Data
    stbi_image_free(image.pixels);
}
