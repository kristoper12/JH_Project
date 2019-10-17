#include "File.h"



File::File()
{
}


File::~File()
{
}

void File::SaveFile(HWND hwnd) {
	if (MessageBox(hwnd, TEXT("저장하시겠습니까?"), TEXT("닫기"), MB_YESNOCANCEL) == IDYES) {
		if (GetSaveFileName(&OFN) != 0) {
			hFile = CreateFile(OFN.lpstrFile, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			if (hFile == INVALID_HANDLE_VALUE)
				return;

			BITMAP bmp;
			GetObject(hBitmap, sizeof(BITMAP), &bmp);
			ZeroMemory(&ih, sizeof(BITMAPINFOHEADER));
			ih.biSize = sizeof(BITMAPINFOHEADER);
			ih.biWidth = bmp.bmWidth;
			ih.biHeight = bmp.bmHeight;
			ih.biPlanes = 1;
			ih.biBitCount = 24;
			ih.biCompression = BI_RGB;

			GetDIBits(hMemDC, hBitmap, 0, bmp.bmHeight, NULL, (LPBITMAPINFO)&ih, DIB_RGB_COLORS);

			LPVOID lpDIBits = new BYTE[ih.biSizeImage];
			GetDIBits(hMemDC, hBitmap, 0, bmp.bmHeight, lpDIBits, (LPBITMAPINFO)&ih, DIB_RGB_COLORS);

			fh.bfType = 'MB';
			fh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
			fh.bfSize = fh.bfOffBits + ih.biSizeImage;
			fh.bfReserved1 = fh.bfReserved2 = 0;

			WriteFile(hFile, &fh, sizeof(BITMAPFILEHEADER), NULL, NULL);
			WriteFile(hFile, &ih, sizeof(BITMAPINFOHEADER), NULL, NULL);
			WriteFile(hFile, lpDIBits, ih.biSizeImage, NULL, NULL);
			CloseHandle(hFile);

			delete[] lpDIBits;
		}
	}
}

void File::OpenFile() {
	cnt = 0;
	PatBlt(hMemDC, 0, 0, crt.right, crt.bottom, WHITENESS);
	if (GetOpenFileName(&OFN) != 0) {
		if (hFile != NULL) {
			hFile = NULL;
		}
		dwRead = 1;
		hFile = CreateFile(OFN.lpstrFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile != INVALID_HANDLE_VALUE) {
			ReadFile(hFile, &fh, sizeof(fh), &dwRead, NULL);
			ReadFile(hFile, &ih, sizeof(ih), &dwRead, NULL);
			dwDataSize = fh.bfSize - fh.bfOffBits;
			pData = new BYTE[dwDataSize];
			if (ih.biBitCount == 24) {
				ReadFile(hFile, pData, dwDataSize, &dwRead, NULL);
				CloseHandle(hFile);

				for (int i = ih.biHeight - 1; i >= 0; i--) {
					for (int j = 0; j < ih.biWidth; j++) {
						SetPixel(hMemDC, j, i, RGB(pData[cnt + 2], pData[cnt + 1], pData[cnt]));
						cnt += 3;
					}
					for (int j = 0; j < ih.biWidth % 4; j++)
						cnt++;
				}
			}
			else if (ih.biBitCount == 8) {
				ReadFile(hFile, rgb, sizeof(RGBQUAD) * 256, &dwRead, NULL);
				ReadFile(hFile, pData, dwDataSize, &dwRead, NULL);
				CloseHandle(hFile);

				for (int i = ih.biHeight - 1; i >= 0; i--) {
					for (int j = 0; j < ih.biWidth; j++) {
						SetPixel(hMemDC, j, i, RGB(rgb[pData[cnt]].rgbRed, rgb[pData[cnt]].rgbGreen, rgb[pData[cnt]].rgbBlue));
						cnt++;
					}
					cnt += ih.biWidth % 4;
				}
			}
			else if (ih.biBitCount == 4) {
				ReadFile(hFile, rgb, sizeof(RGBQUAD) * 16, &dwRead, NULL);
				ReadFile(hFile, pData, dwDataSize, &dwRead, NULL);
				CloseHandle(hFile);
				BYTE hByte1;
				BYTE hByte2;
				int Check_cnt = 0;
				for (int i = ih.biHeight - 1; i >= 0; i--) {
					for (int j = 0; j < ih.biWidth; j += 2) {
						hByte1 = pData[cnt] & 240;
						hByte1 = hByte1 >> 4;
						hByte2 = pData[cnt] & 15;
						SetPixel(hMemDC, j, i, RGB(rgb[hByte1].rgbRed, rgb[hByte1].rgbGreen, rgb[hByte1].rgbBlue));
						if (Check_cnt * 2 + 1 < ih.biWidth || ih.biWidth % 4 == 0) {
							SetPixel(hMemDC, j + 1, i, RGB(rgb[hByte2].rgbRed, rgb[hByte2].rgbGreen, rgb[hByte2].rgbBlue));
							Check_cnt++;
						}
						else
							Check_cnt = 0;
						cnt++;
					}
					Check_cnt = 0;
					if (ih.biWidth % 4 != 0) {
						cnt += 4 - ih.biWidth / 2 % 4;
						if (ih.biWidth % 2 == 1)
							cnt--;
					}
				}
			}
			else if (ih.biBitCount == 1) {
				ReadFile(hFile, rgb, sizeof(RGBQUAD) * 2, &dwRead, NULL);
				ReadFile(hFile, pData, dwDataSize, &dwRead, NULL);
				CloseHandle(hFile);
				BYTE hByte;
				for (int i = ih.biHeight - 1; i >= 0; i--) {
					for (int j = 0; j < ih.biWidth; j++) {
						hByte = pData[cnt] & 128;
						hByte = hByte >> 7;
						SetPixel(hMemDC, j, i, RGB(rgb[hByte].rgbRed, rgb[hByte].rgbGreen, rgb[hByte].rgbBlue));
						pData[cnt] = pData[cnt] << 1;
					}
					cnt += (32 - ih.biWidth) / 8 + 1;
				}
			}
		}
	}
}