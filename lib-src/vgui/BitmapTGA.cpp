//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

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
