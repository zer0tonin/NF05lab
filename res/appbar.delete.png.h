#ifndef APPBAR_DELETE_PNG_H
#define APPBAR_DELETE_PNG_H

#include <wx/mstream.h>
#include <wx/image.h>
#include <wx/bitmap.h>

static const unsigned char appbar_delete_png[] = 
{
	0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A, 0x00, 0x00, 
	0x00, 0x0D, 0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x4C, 
	0x00, 0x00, 0x00, 0x4C, 0x08, 0x06, 0x00, 0x00, 0x00, 0xC7, 
	0x97, 0x51, 0x2B, 0x00, 0x00, 0x00, 0x01, 0x73, 0x52, 0x47, 
	0x42, 0x00, 0xAE, 0xCE, 0x1C, 0xE9, 0x00, 0x00, 0x00, 0x04, 
	0x67, 0x41, 0x4D, 0x41, 0x00, 0x00, 0xB1, 0x8F, 0x0B, 0xFC, 
	0x61, 0x05, 0x00, 0x00, 0x00, 0x09, 0x70, 0x48, 0x59, 0x73, 
	0x00, 0x00, 0x0E, 0xC3, 0x00, 0x00, 0x0E, 0xC3, 0x01, 0xC7, 
	0x6F, 0xA8, 0x64, 0x00, 0x00, 0x02, 0x26, 0x49, 0x44, 0x41, 
	0x54, 0x78, 0x5E, 0xED, 0xDA, 0xCF, 0x2B, 0x45, 0x41, 0x14, 
	0x07, 0xF0, 0xC7, 0x02, 0xA5, 0x90, 0xA2, 0x64, 0xA3, 0x58, 
	0x51, 0x4A, 0x91, 0x9D, 0xAC, 0x10, 0x65, 0x6F, 0x63, 0x23, 
	0x1B, 0x4B, 0xFF, 0x90, 0x85, 0xAD, 0x95, 0x1D, 0x2B, 0x0B, 
	0x65, 0x87, 0xB5, 0xC4, 0xC2, 0x46, 0x51, 0xA2, 0xE4, 0x47, 
	0xC2, 0xF7, 0xDC, 0x99, 0xD1, 0x98, 0xBC, 0x72, 0xBD, 0x7B, 
	0xCE, 0x7B, 0xEE, 0xFB, 0x7E, 0xEA, 0xDB, 0xCC, 0xBB, 0xDE, 
	0xA5, 0x99, 0x66, 0xCE, 0x7D, 0xEE, 0xBB, 0x15, 0x22, 0x22, 
	0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0xA2, 0xFA, 
	0x68, 0xF1, 0x6D, 0xA3, 0xE8, 0x47, 0xFA, 0x5C, 0xF7, 0xCB, 
	0x13, 0x72, 0xE1, 0xBA, 0x14, 0x5B, 0x41, 0x5E, 0x91, 0x8F, 
	0x24, 0xEF, 0xC8, 0x3A, 0x42, 0x89, 0x33, 0x24, 0x9D, 0xAC, 
	0x90, 0x53, 0x84, 0x12, 0x93, 0xC8, 0x15, 0x92, 0x4E, 0xD6, 
	0x35, 0x32, 0x8B, 0x34, 0x04, 0xAB, 0x1A, 0x36, 0x85, 0x74, 
	0xBA, 0xAE, 0x9A, 0x37, 0xE4, 0xD0, 0x75, 0xFF, 0xB7, 0x79, 
	0x24, 0x5D, 0x35, 0x5A, 0x59, 0x42, 0x54, 0xB5, 0xFA, 0x56, 
	0xD3, 0xB2, 0x6F, 0x2D, 0x2C, 0xFA, 0x56, 0x8D, 0xC5, 0x84, 
	0x8D, 0xFA, 0xD6, 0x82, 0xFA, 0xDF, 0xB2, 0xA8, 0x61, 0xB2, 
	0x25, 0xBB, 0x5C, 0x57, 0xDD, 0x03, 0xB2, 0xE7, 0xBA, 0x3A, 
	0x2C, 0x3F, 0xB8, 0xF6, 0x22, 0xAB, 0x48, 0x4F, 0xF6, 0xAA, 
	0x38, 0x8F, 0xC8, 0x16, 0x72, 0x9B, 0xBD, 0x2A, 0x91, 0x1D, 
	0xE4, 0xA7, 0x42, 0x5D, 0x44, 0xE4, 0x77, 0x9B, 0xB0, 0xA8, 
	0x61, 0xC1, 0x8C, 0x6F, 0x35, 0x0C, 0xFA, 0x56, 0x9D, 0xE5, 
	0x96, 0x3C, 0x47, 0x86, 0x5D, 0x37, 0xB3, 0x8B, 0xBC, 0x20, 
	0xDD, 0xC8, 0x9C, 0x1C, 0xF0, 0x4E, 0x10, 0x79, 0xAF, 0x18, 
	0x41, 0x26, 0x5C, 0x37, 0xB3, 0x8F, 0xDC, 0x23, 0xED, 0x48, 
	0x7C, 0xF5, 0x95, 0xBA, 0xB5, 0xE0, 0xBA, 0xE5, 0x71, 0x84, 
	0xC4, 0xDB, 0x28, 0xFC, 0x93, 0x3D, 0x86, 0xC4, 0xC7, 0x37, 
	0x90, 0x40, 0xFA, 0xF1, 0xCF, 0xAA, 0x9D, 0xB3, 0x8D, 0x98, 
	0xB0, 0xDC, 0x92, 0xB2, 0x32, 0xB4, 0xC8, 0xD5, 0xD1, 0x84, 
	0xE5, 0x84, 0x69, 0x0E, 0xEA, 0xC6, 0xB7, 0xEA, 0x2C, 0x27, 
	0x2C, 0x1D, 0x54, 0x87, 0x6F, 0xA5, 0x8E, 0xD5, 0xAA, 0x29, 
	0x56, 0x58, 0xF8, 0x30, 0x9B, 0x67, 0xAB, 0x86, 0x49, 0x4F, 
	0x6F, 0x32, 0x6A, 0x6E, 0xF7, 0x6F, 0xEA, 0xB9, 0xC2, 0x8A, 
	0x54, 0xCA, 0x2D, 0xC9, 0xA2, 0x9F, 0x53, 0x3A, 0x28, 0xF9, 
	0x2C, 0x25, 0x8A, 0xA8, 0x61, 0x4D, 0x51, 0xF4, 0x43, 0x0D, 
	0xFB, 0xED, 0xEA, 0x88, 0xCF, 0x4F, 0x6B, 0x58, 0x53, 0xAC, 
	0xB0, 0x22, 0xB1, 0xE8, 0xE7, 0x20, 0x5B, 0xBA, 0x94, 0x2B, 
	0x4C, 0x6B, 0x15, 0x98, 0x4D, 0x96, 0xA8, 0xE7, 0x96, 0x8C, 
	0xEB, 0xD0, 0x6F, 0x56, 0x5F, 0x7C, 0x7E, 0x7C, 0x43, 0xD2, 
	0xAC, 0xE0, 0x0B, 0xCB, 0x09, 0x13, 0xB5, 0x0C, 0x2E, 0xBE, 
	0x9A, 0x86, 0x2B, 0xAC, 0x28, 0xED, 0x0A, 0x13, 0x1A, 0x83, 
	0x33, 0x2B, 0xF8, 0xE2, 0x3F, 0xAD, 0xB0, 0x6A, 0x4A, 0xBD, 
	0x25, 0xE3, 0xD5, 0x50, 0x4B, 0x0D, 0x93, 0x9B, 0x8E, 0x01, 
	0xB7, 0x64, 0x15, 0xCF, 0xBE, 0x15, 0x71, 0x0D, 0x63, 0xD1, 
	0xCF, 0x89, 0x2B, 0x2C, 0x27, 0xD3, 0xA2, 0x6F, 0x6D, 0x13, 
	0x09, 0xF7, 0xE1, 0x2F, 0x91, 0x03, 0x9F, 0x3B, 0x7F, 0x4C, 
	0x22, 0x8F, 0x3D, 0x85, 0xE3, 0xF1, 0x23, 0x50, 0xF2, 0x9E, 
	0x70, 0x5C, 0xCE, 0x0D, 0xC7, 0x2D, 0x1F, 0x45, 0x30, 0xB7, 
	0x86, 0x84, 0x81, 0x16, 0x95, 0x86, 0x79, 0x14, 0x4A, 0xC3, 
	0x10, 0x22, 0xDF, 0x54, 0xFF, 0x34, 0xF0, 0xBF, 0x44, 0x9E, 
	0x58, 0x1C, 0x40, 0xCC, 0xD4, 0xE3, 0x19, 0xD7, 0x71, 0x64, 
	0x1A, 0x69, 0xCB, 0x5E, 0xD5, 0x46, 0xBE, 0xBA, 0x3B, 0x76, 
	0x5D, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 
	0x22, 0x22, 0xA2, 0xA0, 0x52, 0xF9, 0x04, 0x56, 0x25, 0xD5, 
	0x24, 0xB4, 0x4A, 0xBD, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 
	0x45, 0x4E, 0x44, 0xAE, 0x42, 0x60, 0x82, 
};

wxBitmap& appbar_delete_png_to_wx_bitmap()
{
	static wxMemoryInputStream memIStream( appbar_delete_png, sizeof( appbar_delete_png ) );
	static wxImage image( memIStream, wxBITMAP_TYPE_PNG );
	static wxBitmap bmp( image );
	return bmp;
};


#endif //APPBAR_DELETE_PNG_H
