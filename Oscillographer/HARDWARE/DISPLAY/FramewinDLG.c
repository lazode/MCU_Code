/*********************************************************************
*                                                                    *
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                                                                    *
**********************************************************************
*                                                                    *
* C-file generated by:                                               *
*                                                                    *
*        GUI_Builder for emWin version 5.26                          *
*        Compiled Aug  8 2014, 14:49:54                              *
*        (c) 2013 Segger Microcontroller GmbH & Co. KG               *
*                                                                    *
**********************************************************************
*                                                                    *
*        Internet: www.segger.com  Support: support@segger.com       *
*                                                                    *
**********************************************************************
*/

// USER START (Optionally insert additional includes)
// USER END

#include "FramewinDLG.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_FRAMEWIN_0    (GUI_ID_USER + 0x00)
#define ID_GRAPH_0    (GUI_ID_USER + 0x01)
#define ID_BUTTON_0    (GUI_ID_USER + 0x02)
#define ID_BUTTON_1    (GUI_ID_USER + 0x03)
#define ID_EDIT_0    (GUI_ID_USER + 0x04)
#define ID_TEXT_0    (GUI_ID_USER + 0x05)
#define ID_PROGBAR_0    (GUI_ID_USER + 0x06)


// USER START (Optionally insert additional defines)

#define DATA_SIZE_Y		600
#define DATA_SIZE_X		1200
#define POS_T			440
#define POS_Y			0
#define TICK_DIST_H		50
#define TICK_DIST_V		50		
#define OFFSET_V		200
#define OFFSET_H		0
#define	FACTOR_V		10
#define FACTOR_H		20

// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

GRAPH_DATA_Handle hData;
static GRAPH_SCALE_Handle hScaleH;
static GRAPH_SCALE_Handle hScaleV;

// USER START (Optionally insert additional static data)




// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, "Framewin", ID_FRAMEWIN_0, 0, 0, 800, 480, 0, 0x0, 0 },
  { GRAPH_CreateIndirect, "Graph", ID_GRAPH_0, 0, 0, 662, 450, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Sample", ID_BUTTON_0, 666, 144, 120, 110, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Redisplay", ID_BUTTON_1, 666, 262, 120, 110, 0, 0x0, 0 },
  { EDIT_CreateIndirect, "Edit", ID_EDIT_0, 671, 34, 113, 50, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "  Shift:", ID_TEXT_0, 671, 11, 100, 18, 0, 0x0, 0 },
  { PROGBAR_CreateIndirect, "Progbar", ID_PROGBAR_0, 670, 392, 114, 57, 0, 0x0, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

// USER START (Optionally insert additional static code)
// USER END

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int     NCode;
  int     Id;
  
  
  // USER START (Optionally insert additional variables)
  static short Data[] = {13,25,38,50,63,75,88,101,113,126,138,151,163,176,188,201,213,226,238,251,263,276,288,301,
	  313,325,338,350,363,375,387,400,412,424,437,449,461,473,486,498,510,522,534,546,559,571,583,595,607,619,631,643,655,
	  667,678,690,702,714,726,737,749,761,772,784,796,807,819,830,842,853,865,876,887,899,910,921,932,944,955,966,977,988,
	  999,1010,1021,1032,1042,1053,1064,1075,1085,1096,1107,1117,1128,1138,1149,1159,1169,1180,1190,1200,1210,1220,1230,
	  1241,1250,1260,1270,1280,1290,1300,1309,1319,1329,1338,1348,1357,1366,1376,1385,1394,1403,1413,1422,1431,1440,1449,
	  1457,1466,1475,1484,1492,1501,1509,1518,1526,1535,1543,1551,1559,1567,1575,1583,1591,1599,1607,1615,1623,1630,1638,
	  1645,1653,1660,1667,1675,1682,1689,1696,1703,1710,1717,1724,1730,1737,1744,1750,1757,1763,1770,1776,1782,1788,1794,
	  1800,1806,1812,1818,1824,1829,1835,1841,1846,1851,1857,1862,1867,1872,1877,1882,1887,1892,1897,1902,1906,1911,1915,
	  1920,1924,1928,1932,1936,1941,1944,1948,1952,1956,1960,1963,1967,1970,1974,1977,1980,1983,1986,1989,1992,1995,1998,
	  2001,2003,2006,2008,2011,2013,2015,2017,2019,2021,2023,2025,2027,2029,2030,2032,2033,2035,2036,2037,2039,2040,2041,
	  2042,2043,2043,2044,2045,2045,2046,2046,2046,2047,2047,2047,2047,2047,2047,2047,2046,2046,2045,2045,2044,2044,2043,
	  2042,2041,2040,2039,2038,2037,2036,2034,2033,2031,2030,2028,2026,2024,2022,2020,2018,2016,2014,2012,2009,2007,2004,
	  2002,1999,1996,1994,1991,1988,1985,1982,1978,1975,1972,1968,1965,1961,1958,1954,1950,1946,1942,1938,1934,1930,1926,
	  1922,1917,1913,1908,1904,1899,1894,1890,1885,1880,1875,1870,1865,1859,1854,1849,1843,1838,1832,1827,1821,1815,1809,
	  1803,1797,1791,1785,1779,1773,1766,1760,1754,1747,1740,1734,1727,1720,1713,1707,1700,1693,1685,1678,1671,1664,1656,
	  1649,1642,1634,1626,1619,1611,1603,1595,1587,1579,1571,1563,1555,1547,1539,1530,1522,1514,1505,1497,1488,1479,1471,
	  1462,1453,1444,1435,1426,1417,1408,1399,1390,1380,1371,1362,1352,1343,1333,1324,1314,1305,1295,1285,1275,1265,1255,
	  1246,1236,1225,1215,1205,1195,1185,1175,1164,1154,1143,1133,1123,1112,1101,1091,1080,1069,1059,1048,1037,1026,1015,
	  1004,993,982,971,960,949,938,927,916,904,893,882,870,859,847,836,825,813,801,790,778,767,755,743,732,720,708,696,684,
	  672,661,649,637,625,613,601,589,577,565,553,540,528,516,504,492,480,467,455,443,431,418,406,394,381,369,356,344,332,
	  319,307,294,282,270,257,245,232,220,207,195,182,170,157,144,132,119,107,94,82,69,57,44,31,19,6,-6,-19,-31,-44,-57,-69,
	  -82,-94,-107,-119,-132,-144,-157,-170,-182,-195,-207,-220,-232,-245,-257,-270,-282,-294,-307,-319,-332,-344,-356,-369,
	  -381,-394,-406,-418,-431,-443,-455,-467,-480,-492,-504,-516,-528,-540,-553,-565,-577,-589,-601,-613,-625,-637,-649,-661,
	  -672,-684,-696,-708,-720,-732,-743,-755,-767,-778,-790,-801,-813,-825,-836,-847,-859,-870,-882,-893,-904,-916,-927,-938,
	  -949,-960,-971,-982,-993,-1004,-1015,-1026,-1037,-1048,-1059,-1069,-1080,-1091,-1101,-1112,-1123,-1133,-1143,-1154,-1164,
	  -1175,-1185,-1195,-1205,-1215,-1225,-1236,-1246,-1255,-1265,-1275,-1285,-1295,-1305,-1314,-1324,-1333,-1343,-1352,-1362,
	  -1371,-1380,-1390,-1399,-1408,-1417,-1426,-1435,-1444,-1453,-1462,-1471,-1479,-1488,-1497,-1505,-1514,-1522,-1530,-1539,
	  -1547,-1555,-1563,-1571,-1579,-1587,-1595,-1603,-1611,-1619,-1626,-1634,-1642,-1649,-1656,-1664,-1671,-1678,-1685,-1693,
	  -1700,-1707,-1713,-1720,-1727,-1734,-1740,-1747,-1754,-1760,-1766,-1773,-1779,-1785,-1791,-1797,-1803,-1809,-1815,-1821,
	  -1827,-1832,-1838,-1843,-1849,-1854,-1859,-1865,-1870,-1875,-1880,-1885,-1890,-1894,-1899,-1904,-1908,-1913,-1917,-1922,
	  -1926,-1930,-1934,-1938,-1942,-1946,-1950,-1954,-1958,-1961,-1965,-1968,-1972,-1975,-1978,-1982,-1985,-1988,-1991,-1994,
	  -1996,-1999,-2002,-2004,-2007,-2009,-2012,-2014,-2016,-2018,-2020,-2022,-2024,-2026,-2028,-2030,-2031,-2033,-2034,-2036,
	  -2037,-2038,-2039,-2040,-2041,-2042,-2043,-2044,-2044,-2045,-2045,-2046,-2046,-2047,-2047,-2047,-2047,-2047,-2047,-2047,
	  -2046,-2046,-2046,-2045,-2045,-2044,-2043,-2043,-2042,-2041,-2040,-2039,-2037,-2036,-2035,-2033,-2032,-2030,-2029,-2027,
	  -2025,-2023,-2021,-2019,-2017,-2015,-2013,-2011,-2008,-2006,-2003,-2001,-1998,-1995,-1992,-1989,-1986,-1983,-1980,-1977,
	  -1974,-1970,-1967,-1963,-1960,-1956,-1952,-1948,-1944,-1941,-1936,-1932,-1928,-1924,-1920,-1915,-1911,-1906,-1902,-1897,
	  -1892,-1887,-1882,-1877,-1872,-1867,-1862,-1857,-1851,-1846,-1841,-1835,-1829,-1824,-1818,-1812,-1806,-1800,-1794,-1788,
	  -1782,-1776,-1770,-1763,-1757,-1750,-1744,-1737,-1730,-1724,-1717,-1710,-1703,-1696,-1689,-1682,-1675,-1667,-1660,-1653,
	  -1645,-1638,-1630,-1623,-1615,-1607,-1599,-1591,-1583,-1575,-1567,-1559,-1551,-1543,-1535,-1526,-1518,-1509,-1501,-1492,
	  -1484,-1475,-1466,-1457,-1449,-1440,-1431,-1422,-1413,-1403,-1394,-1385,-1376,-1366,-1357,-1348,-1338,-1329,-1319,-1309,
	  -1300,-1290,-1280,-1270,-1260,-1250,-1241,-1230,-1220,-1210,-1200,-1190,-1180,-1169,-1159,-1149,-1138,-1128,-1117,-1107,
	  -1096,-1085,-1075,-1064,-1053,-1042,-1032,-1021,-1010,-999,-988,-977,-966,-955,-944,-932,-921,-910,-899,-887,-876,-865,
	  -853,-842,-830,-819,-807,-796,-784,-772,-761,-749,-737,-726,-714,-702,-690,-678,-667,-655,-643,-631,-619,-607,-595,-583,
	  -571,-559,-546,-534,-522,-510,-498,-486,-473,-461,-449,-437,-424,-412,-400,-387,-375,-363,-350,-338,-325,-313,-301,-288,
	  -276,-263,-251,-238,-226,-213,-201,-188,-176,-163,-151,-138,-126,-113,-101,-88,-75,-63,-50,-38,-25,-13};
	
	
  short * pData = NULL;
  int Index = 0;
  short tempDebug = 0;
	

  int tempData = 0;
	  
  int cnt = 0;

  // USER END

  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    //
    // Initialization of 'Edit'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_0);
    EDIT_SetText(hItem, "");
    EDIT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    EDIT_SetFont(hItem, GUI_FONT_COMIC24B_1);
    //
    // Initialization of '  Shift:'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
    TEXT_SetFont(hItem, GUI_FONT_13HB_ASCII);
    // USER START (Optionally insert additional code for further widget initialization)
  
	
    // Initialization of 'Graph'
	hItem = WM_GetDialogItem(pMsg->hWin, ID_GRAPH_0);
  
	pData = Data;
	hData = GRAPH_DATA_YT_Create(GUI_RED, DATA_SIZE_Y, 0, 0);
	//GRAPH_DATA_YT_SetAlign(hData, GRAPH_ALIGN_LEFT);
	
	GRAPH_AttachData(hItem, hData);
  
	//GRAPH_SetBorder(hItem,BORDER_LEFT,BORDER_TOP,BORDER_RIGHT,BORDER_BOTTOM);//设置边界
	GRAPH_SetGridDistX(hItem,50);		//设置水平网格间距
	GRAPH_SetGridDistY(hItem,20);		//设置垂直网格间距
	GRAPH_SetGridVis(hItem,1);			//设置网格可见
  
	hScaleH = GRAPH_SCALE_Create(POS_T, GUI_TA_HCENTER, GRAPH_SCALE_CF_HORIZONTAL, TICK_DIST_H);
	
	GRAPH_SCALE_SetTextColor(hScaleH, GUI_DARKGREEN);
	GRAPH_SCALE_SetFactor(hScaleH,FACTOR_H);
	GRAPH_AttachScale(hItem, hScaleH);
	
	
	hScaleV = GRAPH_SCALE_Create(POS_Y, GUI_TA_VCENTER, GRAPH_SCALE_CF_VERTICAL, TICK_DIST_V);
	
	GRAPH_SCALE_SetTextColor(hScaleV, GUI_DARKGREEN);
	GRAPH_SCALE_SetFactor(hScaleV,FACTOR_V);
	GRAPH_SCALE_SetOff(hScaleV,OFFSET_V);  
	
	GRAPH_AttachScale(hItem, hScaleV);
	
    // USER END
	
	// Initialization of 'Progbar'
	
	hItem = WM_GetDialogItem(pMsg->hWin, ID_PROGBAR_0);
	PROGBAR_SetMinMax(hItem, 0, DATA_SIZE_X);
	PROGBAR_SetValue(hItem, 0);
	 
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_BUTTON_0: // Notifications sent by 'Sample'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
		// USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        
		// USER START (Optionally insert code for reacting on notification message)
	  
		hItem = WM_GetDialogItem(pMsg->hWin, ID_PROGBAR_0);
		
	  
		while(Index == DATA_SIZE_X)
		{
			if(tempData != Read_ADS822())
			{
				tempData = Read_ADS822();
				//Data[Index] = (Read_ADS822() / 1023) * 2 - 1;
				//Data[Index] = Read_ADS822();
				Data[Index] = ADS1110_ReadData();
				Index++;
				PROGBAR_SetValue(hItem, Index);
				delay_us(10);
				
			}	
		}
	  
		// USER END
        
		break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_1: // Notifications sent by 'Redisplay'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
		
		
	  
		for(Index = 0; Index < 1020; Index++)
		{
			//GRAPH_DATA_YT_AddValue(hData, data_map(Data[Index], 0, 1023, 0, DATA_SIZE_Y));
			
			if(Index % 2 == 0)
				GRAPH_DATA_YT_AddValue(hData, (short)(Data[Index])/10 + 220);
			
			
			//tempDebug = Data[Index];
			//GRAPH_DATA_YT_AddValue(hData, 0);
//			GRAPH_DATA_YT_AddValue(hData, (short)(cnt*4+20));
//			
//			cnt++;
//			if(cnt > 100)
//				cnt = 0;
//			GUI_Delay(1);
				
		}

		
	  
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_EDIT_0: // Notifications sent by 'Edit'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    // USER START (Optionally insert additional code for further Ids)
    // USER END
    }
    break;
  // USER START (Optionally insert additional message handling)
  // USER END
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       CreateFramewin
*/
WM_HWIN CreateFramewin(void);
WM_HWIN CreateFramewin(void) {
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
  return hWin;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
