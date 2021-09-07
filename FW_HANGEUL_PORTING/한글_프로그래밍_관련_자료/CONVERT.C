/* johab2ksc.c -- convert X11 johab fonts to KSC5601.1987-[0,1]

   Written by Changwoo Ryu, 1999

   This software is in public domain.
   
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "johabdraw.h"

typedef enum { JOHAB, JOHABS, JOHABSH, JOHAB844 } JohabFontType;

/* by pchacker (2001.12.24) */

static char *s;
static char *foundry, *family, *weight, *slant, *setwidth;
static char *pixel, *point, *resolution_x, *resolution_y, *spacing, *average_width;

//----------------------------------------------------------------------------

static char *font_get_full_name (Display *dpy, XFontStruct *fs);
static JohabFontType font_get_font_type (char *full_name);
static char *font_get_output_font_name (char *full_name, int msb);

static void write_header (XFontStruct *fs, char *output_font_name);
static void write_footer (void);
static void write_char (Display *display, int code, Window window, int msb);

//----------------------------------------------------------------------------

void convert (Display *dpy, char *font_name, int msb)
{
  XFontStruct *font;
  char *full_name;
  JohabFontType font_type;
  char *output_font_name;

  Window canvas;
  XGCValues gcv;
  GC gc;

  int i, j;

  font = XLoadQueryFont (dpy, font_name);
  if (! font)
    {
      fprintf (stderr, "Can't open the font: %s\n", font_name);
      exit (1);
    }

  full_name = font_get_full_name (dpy, font);
  font_type = font_get_font_type (full_name);
  output_font_name = font_get_output_font_name (full_name, msb);

  write_header (font, output_font_name);

  canvas = XCreateSimpleWindow (dpy, DefaultRootWindow (dpy),
				//0, 0, 16, 16, 1,
				0, 0, atoi(pixel), atoi(pixel), 1,	// by pchacker (2001.12.24)
				BlackPixel (dpy, DefaultScreen(dpy)),
				WhitePixel (dpy, DefaultScreen(dpy)));
  XMapWindow (dpy, canvas);

  gcv.font = font->fid;
  gcv.foreground = BlackPixel (dpy, DefaultScreen(dpy));
  gcv.background = WhitePixel (dpy, DefaultScreen(dpy));
  
  gc = XCreateGC (dpy, canvas, GCFont | GCForeground | GCBackground, &gcv);
  XFlush (dpy);

  /* Hangul Jamo: 94 chars */
  i = 0xa4;
  for (j = 0xa1; j <= 0xfe; j++)
    {
	int code = (i << 8) + j;

	XClearWindow (dpy, canvas);
	switch (font_type)
	  {
	  case JOHAB:
	  case JOHABS:
	  case JOHABSH:
	    johab_draw (dpy, canvas, gc, code);
	    break;
	  case JOHAB844:
	    johab844_draw (dpy, canvas, gc, code);
	    break;
	  }

	XFlush (dpy);
	write_char (dpy, code, canvas, msb);
    }

  /* Hangul composed: 2350 chars */
  for (i = 0xb0; i <= 0xc8; i++)
    for (j = 0xa1; j <= 0xfe; j++)
      {
	int code = (i << 8) + j;

	XClearWindow (dpy, canvas);
	switch (font_type)
	  {
	  case JOHAB:
	  case JOHABS:
	  case JOHABSH:
	    johab_draw (dpy, canvas, gc, code);
	    break;
	  case JOHAB844:
	    johab844_draw (dpy, canvas, gc, code);
	    break;
	  }

	XFlush (dpy);
	write_char (dpy, code, canvas, msb);
      }

  XDestroyWindow (dpy, canvas);
    
  write_footer ();

  free (output_font_name);
  free (full_name);
  XFreeFont (dpy, font);
}

static char * font_get_full_name (Display *dpy, XFontStruct *fs)
{
  XFontProp *fp;
  int i;
  Atom fontatom = XInternAtom (dpy, "FONT", False);

  for (i = 0, fp = fs->properties; i < fs->n_properties; i++, fp++)
    {
      if (fp->name == fontatom)
	return (XGetAtomName (dpy, fp->card32));
    }
  return NULL;
}


static JohabFontType font_get_font_type (char *full_name)
{
  int count = 0;
  char *ptr;

  ptr = full_name + strlen (full_name);
  while (ptr >= full_name)
    {
      if (*ptr == '-')
	count++;
      if (count >= 2)
	break;
      ptr--;
    }
  ptr++;

  if (strcasecmp (ptr, "johab-1") == 0)
    return JOHAB;
  else if (strcasecmp (ptr, "johabs-1") == 0)
    return JOHABS;
  else if (strcasecmp (ptr, "johabsh-1") == 0)
    return JOHABSH;
  else if (strcasecmp (ptr, "johab844-1") == 0)
    return JOHAB844;
  else
    {
      fprintf (stderr, "It's not a JOHAB font: %s\n", full_name);
      exit (1);
    }
}

static char * font_get_output_font_name (char *full_name, int msb)
{
  int count, i;
  char *result;
  char *ptr;
  int len = strlen (full_name);

  result = (char *) malloc (len + 20);
  result[0] = '\0';
    
  count = 0;
  i = 0;
  ptr = &full_name[i];
  while (i <= len)
    {
      if (ptr[i] == '-')
	count++;
      if (count == 6)
	break;
      i++;
    }
  strncat (result, ptr, i);
  strcat (result, "-");

  ptr = &full_name[i+1];
  i = 0;
  while (i <= len)
    {
      if (ptr[i] == '-')
	count++;
      if (count == 12)
	break;
      i++;
    }
  strncat (result, ptr, i);
  if (msb == 0)
    strcat (result, "-ksc5601.1987-0");
  else				/* msb == 1 */
    strcat (result, "-ksc5601.1987-1");

  return result;
}

  
static void write_header (XFontStruct *fs, char *output_font_name)
{
  /* by pchacker (2001.12.24)
  char *s;
  char *foundry, *family, *weight, *slant, *setwidth;
  char *pixel, *point, *resolution_x, *resolution_y, *spacing, *average_width;
  */
  
  s = strdup (output_font_name);
  foundry = strtok (s, "-");
  family = strtok (NULL, "-");
  weight = strtok (NULL, "-");
  slant = strtok (NULL, "-");
  setwidth = strtok (NULL, "-");
  pixel = strtok (NULL, "-");
  point = strtok (NULL, "-");
  resolution_x = strtok (NULL, "-");
  resolution_y = strtok (NULL, "-");
  spacing = strtok (NULL, "-");
  average_width = strtok (NULL, "-");
  
  printf ("STARTFONT 2.1\n");
  printf ("COMMENT converted to ksc5601 font by johab2ksc\n");
  printf ("FONT %s\n", output_font_name);
  printf ("SIZE %s %s %s\n", pixel, resolution_x, resolution_y);
  printf ("FONTBOUNDINGBOX %s %s 0 -2\n", pixel, pixel);
  printf ("STARTPROPERTIES 19\n");
  printf ("FONTNAME_REGISTRY \"\"\n");

  printf ("FOUNDRY \"%s\"\n", foundry);
  printf ("FAMILY_NAME \"%s\"\n", family);
  printf ("WEIGHT_NAME \"%s\"\n", weight);
  printf ("SLANT \"%s\"\n", slant);
  printf ("SETWIDTH_NAME \"%s\"\n", setwidth);
  printf ("ADD_STYLE_NAME \"\"\n");
  printf ("PIXEL_SIZE %s\n", pixel);
  printf ("POINT_SIZE %s\n", point);
  printf ("RESOLUTION_X %s\n", resolution_x);
  printf ("RESOLUTION_Y %s\n", resolution_y);
  printf ("SPACING \"%s\"\n", spacing);
  printf ("AVERAGE_WIDTH %s\n", average_width);

  free (s);

  printf ("CHARSET_REGISTRY \"KSC5601.1987\"\n");
  printf ("CHARSET_ENCODING \"0\"\n");

  printf ("DEFAULT_CHAR 8481\n");
  printf ("FONT_DESCENT 2\n");
  /*
  printf ("FONT_ASCENT 14\n");
  */
  printf ("FONT_ASCENT %d\n", atoi(pixel) - 2);	// by pchacker (2001.12.24)
  printf ("COPYRIGHT \"???, reencoded by johab2ksc.\"\n");
  printf ("ENDPROPERTIES\n");

  printf ("CHARS 2444\n");
}

static void write_footer (void)
{
  printf ("ENDFONT\n");
}

static void write_char (Display *dpy, int code, Window window, int msb)
{
  int mb = (code & 0xff00) >> 8;
  int lb = code & 0xff;
  int encoding = ((0x20 - 0xa0 + mb) << 8) + (0x20 - 0xa0 + lb);

  XImage *image;
  int i, j;

  printf ("STARTCHAR J%x\n", encoding);
  printf ("ENCODING %d\n", encoding);

  /* (FIXME) */
  printf ("SWIDTH 960 0\n");
  /*
  printf ("DWIDTH 16 0\n");
  */
  printf ("DWIDTH %s 0\n", pixel);	// by pchacker (2001.12.24)
  /*
  printf ("BBX 16 16 0 -2\n");
  */
  printf ("BBX %s %s 0 -2\n", pixel, pixel);	// by pchacker (2001.12.24)
  printf ("BITMAP\n");

  //image = XGetImage(dpy, window, 0, 0, 16, 16, AllPlanes, ZPixmap);
  image = XGetImage(dpy, window, 0, 0, atoi(pixel), atoi(pixel), AllPlanes, ZPixmap); // by pchacker (2001.12.24)

  //for (i = 0; i < 16; i ++)
  for (i = 0; i < atoi(pixel); i ++)	// by pchacker (2001.12.24)
    {
      int value;

      value = 0;
      //for (j = 0; j < 16; j++)
      for (j = 0; j < atoi(pixel); j++) // by pchacker (2001.12.24)
	{
	  unsigned long n;
	  value <<= 1;
	  n = XGetPixel(image, j, i);
	  if (!n)
	    value |= 0x1;
	}
      printf ("%X%X%X%X\n",
	      ((value & 0xf000) >> 12),
	      ((value & 0xf00) >> 8),
	      ((value & 0xf0) >> 4),
	      (value & 0xf));
    }
  
  printf ("ENDCHAR\n");
}

