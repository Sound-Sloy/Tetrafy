#pragma once
#pragma warning(disable:4244)
#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <initializer_list>

namespace Utils {
	static inline void FastGausianBlur(Image& image, int32_t blurRadius = 1) {
        Image outputImage = GenImageColor(image.width, image.height, BLANK);

        // Create a temporary image to hold the horizontal blur
        Image tempImage = GenImageColor(image.width, image.height, BLANK);

        // Apply horizontal blur
        for (int y = 0; y < image.height; y++) {
            for (int x = 0; x < image.width; x++) {
                Color accum = BLANK;
                float weightSum = 0.0f;

                for (int i = -blurRadius; i <= blurRadius; i++) {
                    int currentX = x + i;

                    // Clamp to the image bounds
                    currentX = Clamp(currentX, 0, image.width - 1);

                    //Color pixel = GetPixel(image, currentX, y);
                    Color pixel = GetImageColor(image, currentX, y);
                    float weight = 1.0f / (1.0f + i * i * 0.1f); // Adjust the weight function as needed

                    accum.r += pixel.r * weight;
                    accum.g += pixel.g * weight;
                    accum.b += pixel.b * weight;
                    accum.a += pixel.a * weight;

                    weightSum += weight;
                }

                accum.r /= weightSum;
                accum.g /= weightSum;
                accum.b /= weightSum;
                accum.a /= weightSum;

                // Set the pixel in the temporary image
                //SetPixel(tempImage, x, y, accum);
                ImageDrawPixel(&tempImage, x, y, accum);
            }
        }

        // Apply vertical blur to the temporary image
        for (int y = 0; y < image.height; y++) {
            for (int x = 0; x < image.width; x++) {
                Color accum = BLANK;
                float weightSum = 0.0f;

                for (int j = -blurRadius; j <= blurRadius; j++) {
                    int currentY = y + j;

                    // Clamp to the image bounds
                    currentY = Clamp(currentY, 0, image.height - 1);

                    Color pixel = GetImageColor(tempImage, x, currentY);
                    float weight = 1.0f / (1.0f + j * j * 0.1f); // Adjust the weight function as needed

                    accum.r += pixel.r * weight;
                    accum.g += pixel.g * weight;
                    accum.b += pixel.b * weight;
                    accum.a += pixel.a * weight;

                    weightSum += weight;
                }

                accum.r /= weightSum;
                accum.g /= weightSum;
                accum.b /= weightSum;
                accum.a /= weightSum;

                // Set the pixel in the output image
                //SetPixel(outputImage, x, y, accum);
                ImageDrawPixel(&outputImage, x, y, accum);

            }
        }

        // Unload temporary image
        UnloadImage(tempImage);
        image = outputImage;
        UnloadImage(outputImage);
	}

    template <typename T>
    static inline T max(std::initializer_list<T> elems...) {
        T elemMax;
        for (T elem : elems) {
            elemMax = std::max(elem, elemMax);
        }
        return elemMax;
    }

    template <typename T>
    static inline T min(std::initializer_list<T> elems...) {
        T elemMin;
        for (T elem : elems) {
            elemMin = std::min(elem, elemMin);
        }
        return elemMin;
    }
};
