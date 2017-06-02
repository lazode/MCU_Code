#ifndef	 _FRAMEWIN_H
#define  _FRAMEWIN_H


#include "DIALOG.h"
#include "ADS822_.h"
#include "delay.h"

#include "ADS1110_CTL.h"


WM_HWIN CreateFramewin(void);
static void _cbDialog(WM_MESSAGE * pMsg);

#endif

