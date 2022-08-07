/*
 * BSD 3-Clause License
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include<VGUI_BitmapTGA.h>
#include<VGUI_DataInputStream.h>

using namespace vgui;

BitmapTGA::BitmapTGA(InputStream* is,bool invertAlpha) : Bitmap()
{
	loadTGA(is,invertAlpha);
}

bool BitmapTGA::loadTGA(InputStream* is,bool invertAlpha)
{
	if(is==null)
	{
		return false;
	}

	DataInputStream dis(is);

	bool success=false;

	uchar id_length=dis.readUChar(success);
	if(!success)
	{
		return false;
	}

	uchar colormap_type=dis.readUChar(success);
	if(!success)
	{
		return false;
	}

	uchar image_type=dis.readUChar(success);
	if(!success)
	{
		return false;
	}

	ushort colormap_index=dis.readUShort(success);
	if(!success)
	{
		return false;
	}

	ushort colormap_length=dis.readUShort(success);
	if(!success)
	{
		return false;
	}

	uchar colormap_size=dis.readUChar(success);
	if(!success)
	{
		return false;
	}

	ushort x_origin=dis.readUShort(success);
	if(!success)
	{
		return false;
	}

	ushort y_origin=dis.readUShort(success);
	if(!success)
	{
		return false;
	}

	int wide=dis.readUShort(success);
	if(!success)
	{
		return false;
	}

	int tall=dis.readUShort(success);
	if(!success)
	{
		return false;
	}

	uchar pixel_size=dis.readUChar(success);
	if(!success)
	{
		return false;
	}

	uchar attributes=dis.readUChar(success);
	if(!success)
	{
		return false;
	}

	if (image_type!=2 
		&& image_type!=10)
	{
		return false;
	}

	if (colormap_type !=0 
		|| (pixel_size!=32 && pixel_size!=24))
	{
		return false;
	}

	setSize(wide,tall);

	if(_rgba==null)
	{
		return false;
	}

	if (id_length != 0)
		dis.seekRelative(id_length,success);  // skip TARGA image comment

	int column, row;
	uchar* ptr;
	if (image_type==2) {  // Uncompressed, RGB images
		for(row=tall-1; row>=0; row--) {
			ptr = _rgba + row*wide*4;
			for(column=0; column<wide; column++) {
				switch (pixel_size) {
					case 24:
							ptr[2]=dis.readUChar(success);
							if(!success)
							{
								return false;
							}
							ptr[1]=dis.readUChar(success);
							if(!success)
							{
								return false;
							}
							ptr[0]=dis.readUChar(success);
							if(!success)
							{
								return false;
							}
							ptr[3]=255;
							if(invertAlpha)
							{
								ptr[3]=0;
							}
							ptr+=4;
							break;
					case 32:
							ptr[2]=dis.readUChar(success);
							if(!success)
							{
								return false;
							}
							ptr[1]=dis.readUChar(success);
							if(!success)
							{
								return false;
							}
							ptr[0]=dis.readUChar(success);
							if(!success)
							{
								return false;
							}
							ptr[3]=255-dis.readUChar(success);
							if(!success)
							{
								return false;
							}
							if(invertAlpha)
							{
								ptr[3]=255-ptr[3];
							}
							ptr+=4;
							break;
				}
			}
		}
	}
	else/* if (image_type==10)*/ {   // Runlength encoded RGB images
		uchar packetHeader,packetSize,j,color[4];
		for(row=tall-1; row>=0; row--) {
			ptr = _rgba + row*wide*4;
			for(column=0; column<wide; ) {
				packetHeader=dis.readUChar(success);
				if(!success)
				{
					return false;
				}
				packetSize = 1 + (packetHeader & 0x7f);
				if (packetHeader & 0x80) {        // run-length packet
					switch (pixel_size) {
						case 24:
								color[2]=dis.readUChar(success);
								if(!success)
								{
									return false;
								}
								color[1]=dis.readUChar(success);
								if(!success)
								{
									return false;
								}
								color[0]=dis.readUChar(success);
								if(!success)
								{
									return false;
								}
								color[3]=255;
								if(invertAlpha)
								{
									color[3]=0;
								}
								break;
						case 32:
								color[2]=dis.readUChar(success);
								if(!success)
								{
									return false;
								}
								color[1]=dis.readUChar(success);
								if(!success)
								{
									return false;
								}
								color[0]=dis.readUChar(success);
								if(!success)
								{
									return false;
								}
								color[3]=dis.readUChar(success);
								if(!success)
								{
									return false;
								}
								if(invertAlpha)
								{
									color[3]=255-color[3];
								}
								break;
					}
	
					for(j=0;j<packetSize;j++) {
						*ptr++=color[0];
						*ptr++=color[1];
						*ptr++=color[2];
						*ptr++=color[3];
						column++;
						if (column==wide) { // run spans across tall
							column=0;
							if (row>0)
								row--;
							else
								goto breakOut;
							ptr = _rgba + row*wide*4;
						}
					}
				}
				else {                            // non run-length packet
					for(j=0;j<packetSize;j++) {
						switch (pixel_size) {
							case 24:
									ptr[2]=dis.readUChar(success);
									if(!success)
									{
										return false;
									}
									ptr[1]=dis.readUChar(success);
									if(!success)
									{
										return false;
									}
									ptr[0]=dis.readUChar(success);
									if(!success)
									{
										return false;
									}
									ptr[0]=255;
									if(invertAlpha)
									{
										color[3]=0;
									}
									ptr+=4;
									break;
							case 32:
									ptr[2]=dis.readUChar(success);
									if(!success)
									{
										return false;
									}
									ptr[1]=dis.readUChar(success);
									if(!success)
									{
										return false;
									}
									ptr[0]=dis.readUChar(success);
									if(!success)
									{
										return false;
									}
									ptr[3]=dis.readUChar(success);
									if(!success)
									{
										return false;
									}
									if(invertAlpha)
									{
										ptr[3]=255-ptr[3];
									}
									ptr+=4;
									break;
						}
						column++;
						if (column==wide) { // pixel packet run spans across tall
							column=0;
							if (row>0)
								row--;
							else
								goto breakOut;
							ptr = _rgba + row*wide*4;
						}						
					}
				}
			}
			breakOut:;
		}
	}

	return true;
}
