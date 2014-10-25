#ifndef EDITTRASH_PNG_H
#define EDITTRASH_PNG_H

#include <wx/mstream.h>
#include <wx/image.h>
#include <wx/bitmap.h>

static const unsigned char edittrash_png[] = 
{
	0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A, 0x00, 0x00, 
	0x00, 0x0D, 0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x20, 
	0x00, 0x00, 0x00, 0x20, 0x08, 0x06, 0x00, 0x00, 0x00, 0x73, 
	0x7A, 0x7A, 0xF4, 0x00, 0x00, 0x06, 0x0E, 0x49, 0x44, 0x41, 
	0x54, 0x58, 0x85, 0x9D, 0x97, 0xCD, 0x8F, 0x5C, 0x57, 0x11, 
	0xC5, 0x7F, 0x55, 0x75, 0xEF, 0x7D, 0xDD, 0x3D, 0xD3, 0xDD, 
	0xE3, 0x49, 0xFC, 0x45, 0x1C, 0xC6, 0x86, 0x08, 0x12, 0x26, 
	0x76, 0xF8, 0x92, 0xB2, 0x0B, 0xDE, 0xB0, 0x60, 0xC3, 0x22, 
	0x2C, 0x11, 0x0B, 0x24, 0x36, 0x61, 0xC9, 0x0A, 0x24, 0x07, 
	0x59, 0x62, 0x93, 0xFF, 0x80, 0x04, 0x56, 0xEC, 0xBC, 0x45, 
	0xC1, 0xF1, 0x22, 0x24, 0xC1, 0x8B, 0x6C, 0x10, 0x24, 0x06, 
	0x27, 0x38, 0xF1, 0x07, 0x58, 0xB6, 0x63, 0x9B, 0x8C, 0x63, 
	0x7B, 0x86, 0xE9, 0x19, 0x4F, 0xF7, 0xBB, 0xB7, 0x58, 0xBC, 
	0x1E, 0x7B, 0x6C, 0x4F, 0x8F, 0x33, 0x29, 0xA9, 0xA5, 0x7E, 
	0xFD, 0xD4, 0x55, 0xE7, 0x9E, 0x3A, 0x75, 0xEA, 0x3D, 0x71, 
	0x77, 0x1E, 0x15, 0x4B, 0x4B, 0x4B, 0xD3, 0x6B, 0xC3, 0xE1, 
	0x2F, 0x4C, 0xE5, 0xA7, 0x9F, 0xDD, 0xBC, 0x55, 0xCE, 0x7E, 
	0x7C, 0xFE, 0xF7, 0x87, 0xBF, 0xF7, 0xC2, 0x2B, 0x96, 0x8C, 
	0xE0, 0xE0, 0x01, 0xAE, 0x5F, 0x5D, 0xE8, 0x9B, 0xE9, 0x61, 
	0x47, 0x66, 0xB2, 0x97, 0x3F, 0x3E, 0xB1, 0xE7, 0x4B, 0xB7, 
	0xCD, 0xE4, 0x91, 0xB9, 0x65, 0x22, 0x00, 0x07, 0xC7, 0xF1, 
	0xE2, 0x5C, 0xFD, 0xEF, 0xB5, 0x23, 0xC1, 0xC2, 0x6F, 0x7A, 
	0xBD, 0x2E, 0x51, 0x8D, 0x7F, 0x7E, 0xF0, 0x21, 0xE7, 0x2E, 
	0x5C, 0xFC, 0xD5, 0x0F, 0xBE, 0x7F, 0xF8, 0x95, 0x7F, 0x9D, 
	0xFD, 0x88, 0x6E, 0xA7, 0xDB, 0x99, 0xEE, 0xF6, 0x7E, 0x12, 
	0x62, 0x7C, 0x75, 0x69, 0xE9, 0x26, 0x10, 0x4E, 0xCD, 0xCE, 
	0xF4, 0xBF, 0xD3, 0xDB, 0xD1, 0x2F, 0x9D, 0x56, 0x67, 0x4B, 
	0x00, 0x3A, 0xE9, 0x86, 0x37, 0x08, 0x78, 0xEB, 0xED, 0xB7, 
	0x74, 0xF1, 0xE6, 0xED, 0x17, 0x56, 0x56, 0xEE, 0xD0, 0xAE, 
	0xDA, 0x58, 0x08, 0x7C, 0xE3, 0xE9, 0x67, 0xD9, 0xFD, 0xF8, 
	0xEC, 0xAF, 0x8F, 0xBF, 0xF9, 0xE7, 0x3F, 0x4C, 0x77, 0xBA, 
	0xEF, 0x84, 0x76, 0xEB, 0x46, 0x67, 0xAA, 0xF3, 0xAA, 0xA9, 
	0x32, 0xDD, 0xDD, 0x41, 0x1E, 0xE6, 0x6F, 0x2A, 0x7A, 0xE2, 
	0xF4, 0x3F, 0x4E, 0xF7, 0x6F, 0xDC, 0x5C, 0xD8, 0x12, 0x80, 
	0x1D, 0x3D, 0x7A, 0x74, 0xE2, 0xCD, 0x37, 0x4E, 0x9C, 0x78, 
	0xE9, 0xF8, 0x9F, 0x8E, 0xBF, 0xFE, 0xE4, 0xDC, 0xDC, 0xA1, 
	0xAA, 0xDD, 0xA2, 0x8A, 0x15, 0x55, 0xAB, 0x42, 0x44, 0x50, 
	0xB3, 0xD8, 0xEE, 0x74, 0x9E, 0xDB, 0x3F, 0x37, 0xB7, 0x7F, 
	0xA6, 0x3D, 0x1D, 0xAD, 0x13, 0x99, 0xDD, 0x31, 0xCB, 0x4C, 
	0xBF, 0xC7, 0xEC, 0x63, 0x3D, 0x3E, 0xBB, 0x71, 0xEB, 0xAB, 
	0xAF, 0xBD, 0xF6, 0xDB, 0x97, 0x4A, 0xF6, 0xE9, 0xF9, 0xF9, 
	0xF9, 0xB7, 0x27, 0xD5, 0x08, 0x9B, 0x9E, 0xDE, 0x9D, 0xE2, 
	0x85, 0xCB, 0x57, 0x2E, 0xFF, 0x7C, 0xFE, 0xE0, 0xB3, 0xBB, 
	0xAB, 0x98, 0xB8, 0x7A, 0xE5, 0x0A, 0x9F, 0x5C, 0xBA, 0x88, 
	0x4A, 0x24, 0x56, 0x42, 0x5D, 0x3B, 0x31, 0x46, 0xCE, 0x9C, 
	0x39, 0x83, 0x7B, 0xC1, 0x30, 0xFA, 0x3B, 0xA6, 0xB1, 0xD8, 
	0x66, 0xAA, 0xD5, 0x61, 0x6D, 0xB8, 0x46, 0x09, 0xDA, 0x1F, 
	0xE5, 0xFC, 0x33, 0xE0, 0xC8, 0x24, 0x00, 0x9B, 0xB6, 0x40, 
	0x1C, 0x0A, 0x4A, 0x29, 0xF8, 0x8F, 0x5E, 0x7C, 0x91, 0xDE, 
	0x4C, 0x9F, 0xB9, 0x03, 0x5F, 0xE6, 0xBD, 0xF7, 0x3F, 0xE4, 
	0xBB, 0xCF, 0x3F, 0xCF, 0xD7, 0x9E, 0x3A, 0xC8, 0xA9, 0xD3, 
	0x1F, 0x70, 0xE9, 0xC2, 0x65, 0x0E, 0x1E, 0x3A, 0xC8, 0xFE, 
	0x03, 0x4F, 0xF2, 0x95, 0xAF, 0x3F, 0xC5, 0xDE, 0x27, 0xF6, 
	0xB1, 0x6F, 0xEF, 0x5E, 0x1E, 0x7B, 0xBC, 0xCB, 0xED, 0xE5, 
	0x01, 0x7B, 0x76, 0xEE, 0xE6, 0xEC, 0xC7, 0xE7, 0xAA, 0x89, 
	0x14, 0x4F, 0x02, 0xE0, 0xDA, 0xDC, 0x70, 0x0A, 0xCB, 0xCB, 
	0x2B, 0x14, 0x2F, 0x48, 0x51, 0x2E, 0x5E, 0xF8, 0x88, 0x50, 
	0x32, 0x97, 0x3F, 0xB9, 0xC4, 0x9B, 0x6F, 0x9C, 0xE0, 0xDD, 
	0x77, 0xDF, 0xC1, 0x8B, 0x22, 0x56, 0xD1, 0x69, 0x4F, 0x31, 
	0xD3, 0x9F, 0xA1, 0x33, 0xDD, 0x41, 0x53, 0x45, 0x1E, 0x65, 
	0xCA, 0xB0, 0x06, 0xF1, 0xB2, 0x6D, 0x00, 0xE0, 0x08, 0x0E, 
	0x45, 0xA4, 0x94, 0x82, 0x97, 0x82, 0x0B, 0x74, 0x7B, 0x7D, 
	0x4A, 0x29, 0xA4, 0x54, 0xD8, 0x37, 0x77, 0x80, 0x5D, 0xFB, 
	0x0E, 0x60, 0x01, 0x4C, 0x9C, 0x32, 0xAA, 0xA1, 0x34, 0xB5, 
	0x9A, 0xC9, 0x2A, 0x84, 0x56, 0x8B, 0x66, 0x50, 0xB7, 0x09, 
	0x40, 0x50, 0x44, 0x1C, 0x51, 0xC8, 0x25, 0x23, 0x28, 0xE6, 
	0xD0, 0xB6, 0xC4, 0x9A, 0x67, 0x56, 0x07, 0x43, 0x82, 0x2A, 
	0x09, 0xA1, 0x1E, 0xD5, 0x78, 0x51, 0x30, 0x40, 0x00, 0x77, 
	0xF2, 0x5A, 0x8D, 0x8B, 0x62, 0xA2, 0xA8, 0xB2, 0xA5, 0x19, 
	0x6C, 0x2A, 0xC2, 0xE6, 0x14, 0xCD, 0x51, 0x72, 0x16, 0x5C, 
	0x9C, 0xEC, 0x82, 0x76, 0x13, 0x2E, 0x35, 0xC3, 0xEC, 0xB4, 
	0x5A, 0x6D, 0x48, 0x81, 0xEC, 0x4D, 0x05, 0x07, 0x8A, 0x0B, 
	0x22, 0x82, 0x98, 0x20, 0x9E, 0xB1, 0x10, 0xC8, 0x94, 0x7A, 
	0xDB, 0x0C, 0xE0, 0x4E, 0x16, 0xC1, 0xC1, 0x90, 0x82, 0xB8, 
	0x10, 0x44, 0x30, 0x09, 0x48, 0x31, 0x5C, 0x0A, 0x21, 0x41, 
	0xBB, 0x95, 0x90, 0x3C, 0x02, 0xE1, 0x2E, 0x08, 0x80, 0xE1, 
	0xA8, 0xC6, 0xDD, 0xD1, 0x68, 0x18, 0x7C, 0x11, 0x0D, 0x80, 
	0x96, 0x31, 0x01, 0xA3, 0x82, 0x03, 0xAE, 0x42, 0x0C, 0x01, 
	0x33, 0x25, 0x0F, 0x47, 0x4C, 0xC5, 0x44, 0xC4, 0x50, 0x07, 
	0xBF, 0x4B, 0xF2, 0x18, 0x42, 0x76, 0x1C, 0x21, 0x4A, 0x00, 
	0xD1, 0xED, 0x6B, 0xC0, 0x01, 0x11, 0x10, 0x44, 0xB2, 0x8F, 
	0x9A, 0xEF, 0xC5, 0x51, 0x0D, 0xD4, 0xA5, 0x50, 0x28, 0x48, 
	0x95, 0xF0, 0x4A, 0x19, 0xCA, 0xE8, 0xAE, 0xD0, 0x05, 0x19, 
	0x7B, 0x88, 0x03, 0x8E, 0x06, 0x45, 0xC5, 0xB6, 0xAA, 0x3F, 
	0x41, 0x84, 0x0D, 0xFD, 0xB8, 0x80, 0x67, 0xA7, 0x50, 0x40, 
	0x9D, 0x2A, 0x56, 0xE0, 0x05, 0xAF, 0x85, 0xA4, 0x2D, 0x2A, 
	0x0D, 0xB8, 0x0B, 0x48, 0x93, 0xC6, 0x4B, 0x06, 0x71, 0x8A, 
	0x67, 0x70, 0x50, 0x55, 0x44, 0xB6, 0xDE, 0x76, 0x9B, 0x33, 
	0x50, 0x1A, 0x06, 0x70, 0xA7, 0x94, 0x8C, 0x8E, 0x5D, 0x21, 
	0x56, 0x01, 0xC9, 0x82, 0x50, 0xA8, 0x3A, 0x81, 0x10, 0x13, 
	0x5E, 0x8F, 0xF7, 0xC6, 0x98, 0x39, 0x77, 0xEE, 0x5E, 0xA9, 
	0x2A, 0x88, 0x6C, 0x1F, 0xC0, 0xFA, 0xE0, 0xB8, 0x43, 0x3D, 
	0x3E, 0x40, 0x46, 0x49, 0x9D, 0x8A, 0xDA, 0x9B, 0x72, 0xC9, 
	0xDA, 0x98, 0x19, 0xB9, 0x14, 0x64, 0xE3, 0xA4, 0xB9, 0xE3, 
	0xDE, 0xE8, 0xC6, 0x74, 0x6B, 0xFA, 0x27, 0x03, 0xF0, 0xA6, 
	0x9F, 0x22, 0x88, 0x97, 0x0C, 0x38, 0x52, 0x84, 0xB6, 0x56, 
	0x90, 0x9B, 0x82, 0x56, 0x19, 0x55, 0x15, 0x29, 0xD4, 0x3C, 
	0x48, 0xB2, 0xE7, 0xE6, 0x07, 0xB5, 0x89, 0x1A, 0xDF, 0x1A, 
	0x80, 0x88, 0xE3, 0x38, 0xD9, 0x71, 0xCF, 0x19, 0x77, 0x28, 
	0x56, 0x13, 0xDB, 0x09, 0xC4, 0x11, 0x11, 0x2A, 0x6B, 0xA1, 
	0x16, 0x9A, 0xB9, 0xDF, 0x00, 0xA0, 0x91, 0xDF, 0x18, 0x80, 
	0x2A, 0x6C, 0xED, 0x43, 0x93, 0x5A, 0x20, 0x8D, 0x1B, 0x82, 
	0xAC, 0xB7, 0x40, 0xB3, 0x52, 0x59, 0xC2, 0x45, 0x71, 0x84, 
	0x90, 0x04, 0x35, 0xA5, 0xE0, 0x0F, 0x64, 0x69, 0x1E, 0x62, 
	0x1A, 0x11, 0xDA, 0xA3, 0xEA, 0x4F, 0x6E, 0x41, 0xC3, 0x6B, 
	0x29, 0x4D, 0x0B, 0x9A, 0x89, 0xB0, 0x64, 0x8D, 0xC3, 0xA9, 
	0x90, 0xAA, 0x8A, 0x14, 0x12, 0x92, 0x1F, 0xFE, 0xAF, 0x7B, 
	0xC3, 0xA0, 0x3E, 0xCA, 0x87, 0x99, 0x64, 0xC5, 0x8D, 0x07, 
	0x00, 0xA2, 0xB9, 0x1E, 0xCF, 0xB8, 0x41, 0x95, 0x12, 0xD0, 
	0x58, 0x6D, 0x8C, 0x81, 0x60, 0x86, 0x6F, 0x52, 0xA2, 0x8C, 
	0x7D, 0xC1, 0x54, 0x1F, 0xD2, 0xC7, 0x83, 0x31, 0xD1, 0x88, 
	0xBC, 0xF1, 0xD6, 0xB2, 0x9E, 0xC1, 0x8B, 0x63, 0x21, 0x22, 
	0xAA, 0x08, 0x81, 0x60, 0x01, 0x8B, 0xA1, 0xD9, 0x9A, 0x1B, 
	0x90, 0x8F, 0x57, 0x48, 0x73, 0xA5, 0xDA, 0x74, 0x73, 0x8B, 
	0xD8, 0x94, 0x01, 0x59, 0x47, 0x71, 0x9F, 0xBE, 0x8C, 0x94, 
	0x1A, 0xD1, 0xA5, 0x2A, 0x10, 0x53, 0x85, 0x9A, 0xC1, 0x66, 
	0x63, 0xDE, 0x28, 0x11, 0x33, 0x83, 0x2F, 0xC2, 0x40, 0x13, 
	0x65, 0x9C, 0xAA, 0x39, 0x80, 0xB8, 0x93, 0x62, 0x85, 0xA8, 
	0x62, 0x21, 0x12, 0x43, 0x24, 0xB8, 0x6C, 0xB2, 0x69, 0x36, 
	0x58, 0xB1, 0x2A, 0xBE, 0x61, 0x53, 0x6C, 0x16, 0x13, 0xD6, 
	0xB1, 0xAF, 0x3F, 0x92, 0xDC, 0x53, 0xB1, 0x80, 0x06, 0x45, 
	0x5C, 0xA8, 0x62, 0x20, 0xC6, 0x80, 0x3C, 0x74, 0x42, 0x1F, 
	0xB7, 0xA0, 0x34, 0x19, 0x44, 0x9A, 0x89, 0xD8, 0x22, 0x26, 
	0x30, 0xD0, 0x54, 0x35, 0xD5, 0xF1, 0xA2, 0x11, 0x54, 0x84, 
	0x14, 0x5A, 0x58, 0x0C, 0xC4, 0x18, 0xB1, 0x98, 0x88, 0x16, 
	0xEE, 0x03, 0x20, 0xDC, 0x5B, 0x48, 0x8E, 0xE0, 0x5E, 0xA8, 
	0xAA, 0x96, 0x2C, 0x0F, 0x96, 0x3F, 0x3F, 0x80, 0x75, 0x11, 
	0x95, 0xE2, 0x0C, 0x87, 0x23, 0xB3, 0x10, 0x80, 0x82, 0xBB, 
	0x63, 0xD1, 0x30, 0x13, 0x2C, 0x46, 0x52, 0x0C, 0x58, 0x50, 
	0x6C, 0x03, 0x02, 0xA7, 0x69, 0x95, 0xBB, 0x8F, 0xA5, 0x21, 
	0xC4, 0x14, 0xDA, 0xC7, 0x8E, 0x1D, 0x9B, 0xFA, 0xFC, 0x0C, 
	0x8C, 0xF3, 0xC5, 0x60, 0xB3, 0xE2, 0xF4, 0x0A, 0x8E, 0x99, 
	0x11, 0x42, 0xA4, 0xDD, 0x6A, 0x91, 0x82, 0x91, 0x62, 0xA4, 
	0x4A, 0x09, 0x35, 0xBB, 0xAF, 0x03, 0xAA, 0x0A, 0x26, 0x04, 
	0x0B, 0xA8, 0x19, 0x66, 0x86, 0x9A, 0x75, 0x5F, 0x3E, 0xF2, 
	0xF2, 0x81, 0x49, 0x00, 0x1E, 0xD2, 0x80, 0xAC, 0xF7, 0x11, 
	0x06, 0xEF, 0xBD, 0xFF, 0xF7, 0x93, 0x3B, 0x77, 0xED, 0xFC, 
	0xF1, 0xEA, 0x60, 0x85, 0xE1, 0xAE, 0x9A, 0x4E, 0xA7, 0xC3, 
	0x68, 0xE4, 0x84, 0x10, 0x51, 0x53, 0xCC, 0x8D, 0x22, 0x20, 
	0xA2, 0xE0, 0x30, 0x1A, 0x8E, 0x58, 0x1B, 0x0E, 0x59, 0xB8, 
	0x71, 0x83, 0x85, 0x85, 0x4F, 0xB9, 0x7A, 0xED, 0x2A, 0xFF, 
	0x39, 0xFF, 0xEF, 0xBF, 0xDD, 0x59, 0x5D, 0xB9, 0x36, 0x09, 
	0xC0, 0xA6, 0xEF, 0x86, 0x3E, 0xA6, 0xF1, 0xE4, 0x5F, 0x4E, 
	0xEE, 0x5E, 0x5C, 0x5A, 0xFC, 0xE5, 0xCA, 0xEA, 0xEA, 0x0F, 
	0x29, 0xEC, 0xAB, 0xDA, 0x9D, 0xD4, 0xEB, 0x4F, 0x13, 0x53, 
	0xC0, 0x24, 0x70, 0xE7, 0xCE, 0x10, 0x95, 0xC6, 0xA4, 0xC0, 
	0xA8, 0x82, 0x32, 0x58, 0x59, 0xE5, 0xDA, 0xF5, 0xEB, 0x83, 
	0xFF, 0xDD, 0xBE, 0x7D, 0xCE, 0x5A, 0xE9, 0xF5, 0xF9, 0x67, 
	0x9E, 0xFE, 0xDD, 0x73, 0x87, 0xBE, 0x75, 0xA5, 0xDF, 0xEF, 
	0x6D, 0x03, 0x00, 0x7E, 0xD7, 0x89, 0x44, 0xA4, 0x3D, 0x18, 
	0xAC, 0x3C, 0xB3, 0xB8, 0x78, 0xEB, 0xDB, 0x4B, 0x4B, 0x4B, 
	0xF3, 0x83, 0xE5, 0xC1, 0x9E, 0xE1, 0xDA, 0xB0, 0x3B, 0xCA, 
	0x79, 0xAA, 0xAE, 0x47, 0x92, 0x4B, 0x09, 0x21, 0xA8, 0xB6, 
	0xAA, 0xCE, 0x5A, 0xAA, 0xC2, 0x42, 0x95, 0x5A, 0xE7, 0xA7, 
	0xA6, 0xA7, 0x4F, 0xCD, 0xF4, 0x7A, 0x7F, 0xED, 0xF7, 0xFB, 
	0x97, 0xDC, 0x29, 0x16, 0x26, 0xAF, 0xE5, 0xC9, 0x6F, 0xC7, 
	0xF7, 0x21, 0x2A, 0x14, 0x14, 0x15, 0x0C, 0xA8, 0xC6, 0x9F, 
	0xC0, 0x3D, 0x0D, 0x19, 0x50, 0x03, 0xCB, 0xC0, 0x1A, 0x78, 
	0x7E, 0xE4, 0x16, 0x1A, 0xC7, 0xFF, 0x01, 0xFC, 0xA4, 0xAD, 
	0x45, 0x52, 0x07, 0x89, 0xE8, 0x00, 0x00, 0x00, 0x00, 0x49, 
	0x45, 0x4E, 0x44, 0xAE, 0x42, 0x60, 0x82, 
};

wxBitmap& edittrash_png_to_wx_bitmap()
{
	static wxMemoryInputStream memIStream( edittrash_png, sizeof( edittrash_png ) );
	static wxImage image( memIStream, wxBITMAP_TYPE_PNG );
	static wxBitmap bmp( image );
	return bmp;
};


#endif //EDITTRASH_PNG_H
