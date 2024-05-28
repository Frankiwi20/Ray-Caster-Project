#include <malloc.h>
#include "canvas.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
// used indent
static char *unsigned_int_to_char_array (unsigned int);

Canvas
canvas (unsigned int w, unsigned int h)
{
  // Allocate memory for the Canvas struct
  Canvas c;
  c.width = w;
  c.height = h;
  c.channels = 3;		// Assuming RGB channels

  // Allocate memory for pixel data (using single-dimensional array for RGB pixels)
  c.pixels =
    (unsigned int *) calloc (w * h * c.channels, sizeof (unsigned int));
  if (c.pixels == NULL)
    {
      fprintf (stderr,
	       "Error: Failed to allocate memory for canvas pixels.\n");
      exit (EXIT_FAILURE);
    }

  // Initialize pixels to black (0, 0, 0)
  for (unsigned int i = 0; i < w * h * c.channels; ++i)
    {
      c.pixels[i] = 0;		// All channels set to 0 (black)
    }

  return c;
}

// Helper function to clamp the color values to 0-255 range
static unsigned int
clamp_color_value (double value)
{
  int scaled = (int) (value * 255.0 + 0.5);	// Use rounding to nearest integer
  if (scaled < 0)
    return 0;
  if (scaled > 255)
    return 255;
  return scaled;
}

Canvas
write_pixel (Canvas ca, unsigned int x, unsigned int y, Color co)
{
  // Ensure x and y are within the bounds of the canvas
  if (x >= ca.width || y >= ca.height)
    {
      fprintf (stderr,
	       "Error: Pixel coordinates (%u, %u) out of bounds (width=%u, height=%u).\n",
	       x, y, ca.width, ca.height);
      exit (EXIT_FAILURE);
    }

  // Calculate the index in the pixel array for the given (x, y) coordinates
  unsigned int index = (y * ca.width + x) * ca.channels;

  // Apply clamping when setting pixel values
  ca.pixels[index] = clamp_color_value (co.red);	// Red
  ca.pixels[index + 1] = clamp_color_value (co.green);	// Green
  ca.pixels[index + 2] = clamp_color_value (co.blue);	// Blue

  return ca;
}






Color
pixel_at (Canvas ca, unsigned int x, unsigned int y)
{
  // Calculate the index in the pixel array for the given (x, y) coordinates
  unsigned int index = (y * ca.width + x) * ca.channels;

  // Directly retrieve color components from the pixel array (already in [0, 255] range)
  Color co;
  co.red = (double) (ca.pixels[index]);	// Red
  co.green = (double) (ca.pixels[index + 1]);	// Green
  co.blue = (double) (ca.pixels[index + 2]);	// Blue

  return co;
}


char *
canvas_to_ppm (Canvas ca)
{
  const unsigned int HEADER_MAX_LEN = 100;
  char header[HEADER_MAX_LEN];
  sprintf (header, "P3\n%d %d\n255\n", ca.width, ca.height);
  unsigned int header_length = strlen (header);

  // Generous buffer allocation to account for space and newlines
  char *ppm =
    (char *) calloc (header_length + (ca.width * ca.height * 15) +
		     (ca.height * 2) + 2, sizeof (char));
  if (ppm == NULL)
    {
      fprintf (stderr, "Error: Failed to allocate memory for PPM output.\n");
      exit (EXIT_FAILURE);
    }

  strcpy (ppm, header);
  unsigned int ppm_index = header_length;
  char pixel_buffer[20];	// Increase buffer size to safely hold any pixel value strings

  for (unsigned int y = 0; y < ca.height; y++)
    {
      for (unsigned int x = 0; x < ca.width; x++)
	{
	  unsigned int index = (y * ca.width + x) * ca.channels;
	  sprintf (pixel_buffer, "%u %u %u ", ca.pixels[index],
		   ca.pixels[index + 1], ca.pixels[index + 2]);
	  if (x < ca.width - 1)
	    {
	      strcat (ppm + ppm_index, pixel_buffer);
	      ppm_index += strlen (pixel_buffer);
	    }
	  else
	    {
	      // Remove trailing space for the last pixel in a row
	      pixel_buffer[strlen (pixel_buffer) - 1] = '\0';
	      strcat (ppm + ppm_index, pixel_buffer);
	      ppm_index += strlen (pixel_buffer);
	    }
	}
      strcat (ppm + ppm_index, "\n");	// End each row of pixels with a newline
      ppm_index += 1;
    }

  // Ensure the final character is a newline
  ppm[ppm_index] = '\n';	// Add the final newline character
  ppm[ppm_index + 1] = '\0';	// Ensure the string is null-terminated

  return ppm;
}




/* utility for conversion of unsigned int to char array */
static char *
unsigned_int_to_char_array (unsigned int num)
{
  /* function only needs to expect numbers from 0 - 255 */
  assert (num <= 255);

  char *str = (char *) calloc (4, sizeof (char));	// Allocate memory for 3 digits + '\0'

  if (str == NULL)
    {
      fprintf (stderr, "Error: Failed to allocate memory for char array.\n");
      exit (EXIT_FAILURE);
    }

  sprintf (str, "%u", num);	// Convert num to string

  return str;
}
