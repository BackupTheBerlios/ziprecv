/*
 * zipsplit
 *
 * Copyright (c) 2005 Paulo Matias
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */
 
/*
 * This program looks for the pkzip header in a zipfile and splits it,
 * one file per entry in the archive.
 */

/*
 * FIXME: This program only searchs the header sequence in the file,
 * but it isn't aware of the archive internal structure. It could have
 * troubles in certain (rare) cases.
 */

#include <stdio.h>

int main(int argc, char **argv)
{
  int nreaded, nfound = 0, npart = 1;
  int buf;
  unsigned char search[] = { 0x50, 0x4b, 0x03, 0x04 };
  char filename[256];
  FILE *fp = 0;
  if(argc != 2)
  {
    printf("Usage: zipsplit sufix\n");
    return 1;
  }
  while((buf = fgetc(stdin)) >= 0)
  {
    if(search[nfound] == buf)
    {
      nfound++;
    } else {
      nfound = 0;
      if(search[0] == buf)
        nfound++;
    }
    if(nfound == 5)
    {
      sprintf(filename, "%s%03d", argv[1], npart++);
      if(fp)
        fclose(fp);
      fp = fopen(filename, "wb");
      fwrite(search, 1, 4, fp);
    }
    if(fp)
      fputc(buf, fp);
  }
  return 0;
}
