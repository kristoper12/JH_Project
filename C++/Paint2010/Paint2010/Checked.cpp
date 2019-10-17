#include "Checked.h"



Checked::Checked()
{
}


Checked::~Checked()
{
}

void Checked::LineBaseLine() {
	tBaseLine = TRUE;
	tFreeLine = FALSE;
	tDottedLine = FALSE;
	tCircle = FALSE;
	tTriangle = FALSE;
	tRectangle = FALSE;
	penType = PS_SOLID;
}
void Checked::LineDottedLine() {
	tBaseLine = FALSE;
	tDottedLine = TRUE;
	tFreeLine = FALSE;
	tCircle = FALSE;
	tTriangle = FALSE;
	tRectangle = FALSE;
	penType = PS_DOT;
}
void Checked::LineFreeLine() {
	tBaseLine = FALSE;
	tDottedLine = FALSE;
	tFreeLine = TRUE;
	tCircle = FALSE;
	tTriangle = FALSE;
	tRectangle = FALSE;
	penType = PS_SOLID;
}
void Checked::LineCircle() {
	tBaseLine = FALSE;
	tFreeLine = FALSE;
	tDottedLine = FALSE;
	tCircle = TRUE;
	tTriangle = FALSE;
	tRectangle = FALSE;
	penType = PS_SOLID;
}
void Checked::LineTriangle() {
	tBaseLine = FALSE;
	tFreeLine = FALSE;
	tDottedLine = FALSE;
	tCircle = FALSE;
	tTriangle = TRUE;
	tRectangle = FALSE;
	penType = PS_SOLID;
}
void Checked::LineRectangle() {
	tBaseLine = FALSE;
	tFreeLine = FALSE;
	tDottedLine = FALSE;
	tCircle = FALSE;
	tTriangle = FALSE;
	tRectangle = TRUE;
	penType = PS_SOLID;
}