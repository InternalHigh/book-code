/******************************************************************************
Module:  AppLog.cpp
Notices: Copyright (c) 2000 Jeffrey Richter
******************************************************************************/


#include "..\CmnHdr.h"              // See Appendix A.
#include <WindowsX.h>

#define EVENTLOG_IMPL
#include "EventLog.h"

#include "Resource.h"
#include "AppLogMsgs.h"             // Generated by MC.exe


///////////////////////////////////////////////////////////////////////////////


CEventLog g_EventLog(TEXT("AppLog"));


///////////////////////////////////////////////////////////////////////////////


BOOL Dlg_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) {

   chSETDLGICONS(hwnd, IDI_APPLOG);
   return(TRUE);
}


///////////////////////////////////////////////////////////////////////////////


void Dlg_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify) {
   
   switch (id) {
   case IDCANCEL:
      EndDialog(hwnd, id);
      break;

   case IDC_SPAWNEVENTVIEWER:
      // Spawn the Event Viewer Snap-In
      ShellExecute(hwnd, TEXT("Open"), TEXT("eventvwr.msc"), TEXT("/s"), 
         NULL, SW_SHOWDEFAULT);
      break;

   case IDC_INSTALL:
      // Install the event log parameter file info into the registry
      chVERIFY(g_EventLog.Install(
         EVENTLOG_INFORMATION_TYPE | EVENTLOG_ERROR_TYPE, NULL, 
         TEXT("Kernel32.dll"), 2, NULL));
      break;

   case IDC_REMOVE:
      // Uninstall the event log parameter file info from the registry
      chVERIFY(g_EventLog.Uninstall());
      break;

   case IDC_SIMULATEERROR:
      // Report a Win32 error code event
      TCHAR szErrorCode[10];
      PCTSTR pszErrorCode = szErrorCode;
      GetDlgItemText(hwnd, IDC_ERRORCODE, szErrorCode, chDIMOF(szErrorCode));
      chVERIFY(g_EventLog.ReportEvent(EVENTLOG_ERROR_TYPE, CAT_APPEVENT, 
         MSG_ERROR, CEventLog::REUSER_NOTAPPLICABLE, 
         1, (PCTSTR*) &pszErrorCode));
      break;
   }
}


///////////////////////////////////////////////////////////////////////////////


INT_PTR WINAPI Dlg_Proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

   switch (uMsg) {
   chHANDLE_DLGMSG(hwnd, WM_INITDIALOG, Dlg_OnInitDialog);
   chHANDLE_DLGMSG(hwnd, WM_COMMAND,    Dlg_OnCommand);
   }
   return(FALSE);
}


///////////////////////////////////////////////////////////////////////////////


int WINAPI _tWinMain(HINSTANCE hinstExe, HINSTANCE, PTSTR pszCmdLine, int) {

   // Report an event that this application is starting
   g_EventLog.ReportEvent(EVENTLOG_INFORMATION_TYPE, 
      CAT_APPEXECSTATUS, MSG_APPSTART);
   DialogBox(hinstExe, MAKEINTRESOURCE(IDD_APPLOG), NULL, Dlg_Proc);

   // Report an event that this application is stopping
   g_EventLog.ReportEvent(EVENTLOG_INFORMATION_TYPE, 
      CAT_APPEXECSTATUS, MSG_APPSTOP);
   return(0);
}


//////////////////////////////// End of File //////////////////////////////////

