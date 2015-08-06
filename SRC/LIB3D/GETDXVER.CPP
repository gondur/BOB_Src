/*
	 Battle of Britain
	 Copyright (C) 2000, 2001 Empire Interactive (Europe) Ltd,
	 677 High Road, North Finchley, London N12 0DA

	 Please see the document licence.doc for the full licence agreement

2. LICENCE
 2.1 	
 	Subject to the provisions of this Agreement we now grant to you the 
 	following rights in respect of the Source Code:
  2.1.1 
  	the non-exclusive right to Exploit  the Source Code and Executable 
  	Code on any medium; and 
  2.1.2 
  	the non-exclusive right to create and distribute Derivative Works.
 2.2 	
 	Subject to the provisions of this Agreement we now grant you the
	following rights in respect of the Object Code:
  2.2.1 
	the non-exclusive right to Exploit the Object Code on the same
	terms and conditions set out in clause 3, provided that any
	distribution is done so on the terms of this Agreement and is
	accompanied by the Source Code and Executable Code (as
	applicable).

3. GENERAL OBLIGATIONS
 3.1 
 	In consideration of the licence granted in clause 2.1 you now agree:
  3.1.1 
	that when you distribute the Source Code or Executable Code or
	any Derivative Works to Recipients you will also include the
	terms of this Agreement;
  3.1.2 
	that when you make the Source Code, Executable Code or any
	Derivative Works ("Materials") available to download, you will
	ensure that Recipients must accept the terms of this Agreement
	before being allowed to download such Materials;
  3.1.3 
	that by Exploiting the Source Code or Executable Code you may
	not impose any further restrictions on a Recipient's subsequent
	Exploitation of the Source Code or Executable Code other than
	those contained in the terms and conditions of this Agreement;
  3.1.4 
	not (and not to allow any third party) to profit or make any
	charge for the Source Code, or Executable Code, any
	Exploitation of the Source Code or Executable Code, or for any
	Derivative Works;
  3.1.5 
	not to place any restrictions on the operability of the Source 
	Code;
  3.1.6 
	to attach prominent notices to any Derivative Works stating
	that you have changed the Source Code or Executable Code and to
	include the details anddate of such change; and
  3.1.7 
  	not to Exploit the Source Code or Executable Code otherwise than
	as expressly permitted by  this Agreement.

questions about this file may be asked at bob@rowansoftware.com a
better place to ask is http://www.simhq.com/ or even :-
http://www.simhq.com/cgi-bin/boards/cgi-bin/forumdisplay.cgi?action=topics&forum=Battle+of+Britain&number=40&DaysPrune=20&LastLogin=
*/

//-----------------------------------------------------------------------------
// File: GetDXVer.cpp
//
// Desc: Demonstrates how applications can detect what version of DirectX
//       is installed.
//
//    (C) Copyright 1995-1997 Microsoft Corp.  All rights reserved.
//-----------------------------------------------------------------------------
#include <windows.h>
#include <windowsx.h>
#include <ddraw.h>
#include <dinput.h>
#include <dmusici.h>




typedef HRESULT(WINAPI * DIRECTDRAWCREATE)( GUID*, LPDIRECTDRAW*, IUnknown* );
typedef HRESULT(WINAPI * DIRECTDRAWCREATEEX)( GUID*, VOID**, REFIID, IUnknown* );
typedef HRESULT(WINAPI * DIRECTINPUTCREATE)( HINSTANCE, DWORD, LPDIRECTINPUT*,
                                             IUnknown* );



//-----------------------------------------------------------------------------
// Name: GetDXVersion()
// Desc: This function returns two arguments:
//          dwDXVersion:
//            0x0000 = No DirectX installed
//            0x0100 = DirectX version 1 installed
//            0x0200 = DirectX 2 installed
//            0x0300 = DirectX 3 installed
//            0x0500 = At least DirectX 5 installed.
//            0x0600 = At least DirectX 6 installed.
//            0x0601 = At least DirectX 6.1 installed.
//            0x0700 = At least DirectX 7 installed.
//          dwDXPlatform:
//            0                          = Unknown (This is a failure case)
//            VER_PLATFORM_WIN32_WINDOWS = Windows 9X platform
//            VER_PLATFORM_WIN32_NT      = Windows NT platform
// 
//          Please note that this code is intended as a general guideline. Your
//          app will probably be able to simply query for functionality (via
//          QueryInterface) for one or two components.
//
//          Please also note:
//            "if (dxVer != 0x500) return FALSE;" is BAD. 
//            "if (dxVer < 0x500) return FALSE;" is MUCH BETTER.
//          to ensure your app will run on future releases of DirectX.
//-----------------------------------------------------------------------------
VOID GetDXVersion( DWORD* pdwDXVersion, DWORD* pdwDXPlatform )
{
//DEADCODE RDH 26/04/00     HRESULT              hr;
    HINSTANCE            DDHinst = 0;
    HINSTANCE            DIHinst = 0;
//DeadCode JON 20Oct00     LPDIRECTDRAW         pDDraw  = 0;
//DeadCode JON 20Oct00     LPDIRECTDRAW2        pDDraw2 = 0;
//DeadCode JON 20Oct00     DIRECTDRAWCREATE     DirectDrawCreate   = 0;
    DIRECTDRAWCREATEEX   DirectDrawCreateEx = 0;
    DIRECTINPUTCREATE    DirectInputCreate  = 0;
    OSVERSIONINFO        osVer;
//DeadCode JON 20Oct00     LPDIRECTDRAWSURFACE  pSurf  = 0;
//DeadCode JON 20Oct00     LPDIRECTDRAWSURFACE3 pSurf3 = 0;
//DeadCode JON 20Oct00     LPDIRECTDRAWSURFACE4 pSurf4 = 0;

    // First get the windows platform
    osVer.dwOSVersionInfoSize = sizeof(osVer);
    if( !GetVersionEx( &osVer ) )
    {
        (*pdwDXPlatform) = 0;
        (*pdwDXVersion)  = 0;
        return;
    }

	*pdwDXVersion = 0;

    if( osVer.dwPlatformId == VER_PLATFORM_WIN32_NT )
    {
        (*pdwDXPlatform) = VER_PLATFORM_WIN32_NT;

        // NT is easy... NT 4.0 is DX2, 4.0 SP3 is DX3, 5.0 is DX5
        // and no DX on earlier versions.
        if( osVer.dwMajorVersion < 4 )
        {
            (*pdwDXVersion) = 0; // No DX on NT3.51 or earlier
            return;
        }

        if( osVer.dwMajorVersion == 4 )
        {
            // NT4 up to SP2 is DX2, and SP3 onwards is DX3, so we are at least DX2
            (*pdwDXVersion) = 0x200;

            // We're not supposed to be able to tell which SP we're on, so check for dinput
            DIHinst = LoadLibrary( "DINPUT.DLL" );
            if( DIHinst == 0 )
            {
                // No DInput... must be DX2 on NT 4 pre-SP3
                OutputDebugString( "Couldn't LoadLibrary DInput\r\n" );
                return;
            }

            DirectInputCreate = (DIRECTINPUTCREATE)GetProcAddress( DIHinst,
                                                                 "DirectInputCreateA" );
            FreeLibrary( DIHinst );

            if( DirectInputCreate == 0 )
            {
                // No DInput... must be pre-SP3 DX2
                OutputDebugString( "Couldn't GetProcAddress DInputCreate\r\n" );
                return;
            }

            // It must be NT4, DX2
            (*pdwDXVersion) = 0x300;  // DX3 on NT4 SP3 or higher
            return;
        }
        // Else it's NT5 or higher, and it's DX5a or higher: Drop through to
        // Win9x tests for a test of DDraw (DX6 or higher)
    }
    else
    {
        // Not NT... must be Win9x
        (*pdwDXPlatform) = VER_PLATFORM_WIN32_WINDOWS;
    }

    // Now we know we are in Windows 9x (or maybe 3.1), so anything's possible.
    // First see if DDRAW.DLL even exists.
    DDHinst = LoadLibrary( "DDRAW.DLL" );
    if( DDHinst == 0 )
    {
        (*pdwDXVersion)  = 0;
        (*pdwDXPlatform) = 0;
        FreeLibrary( DDHinst );
        return;
    }

//DEADCODE RDH 26/04/00 
//DEADCODE RDH 26/04/00     // See if we can create the DirectDraw object.
//DEADCODE RDH 26/04/00     DirectDrawCreate = (DIRECTDRAWCREATE)GetProcAddress( DDHinst, "DirectDrawCreate" );
//DEADCODE RDH 26/04/00     if( DirectDrawCreate == 0 )
//DEADCODE RDH 26/04/00     {
//DEADCODE RDH 26/04/00         (*pdwDXVersion)  = 0;
//DEADCODE RDH 26/04/00         (*pdwDXPlatform) = 0;
//DEADCODE RDH 26/04/00         FreeLibrary( DDHinst );
//DEADCODE RDH 26/04/00         OutputDebugString( "Couldn't LoadLibrary DDraw\r\n" );
//DEADCODE RDH 26/04/00         return;
//DEADCODE RDH 26/04/00     }
//DEADCODE RDH 26/04/00 
//DEADCODE RDH 26/04/00     hr = DirectDrawCreate( NULL, &pDDraw, NULL );
//DEADCODE RDH 26/04/00     if( FAILED(hr) )
//DEADCODE RDH 26/04/00     {
//DEADCODE RDH 26/04/00         (*pdwDXVersion)  = 0;
//DEADCODE RDH 26/04/00         (*pdwDXPlatform) = 0;
//DEADCODE RDH 26/04/00         FreeLibrary( DDHinst );
//DEADCODE RDH 26/04/00         OutputDebugString( "Couldn't create DDraw\r\n" );
//DEADCODE RDH 26/04/00         return;
//DEADCODE RDH 26/04/00     }
//DEADCODE RDH 26/04/00 
//DEADCODE RDH 26/04/00     // So DirectDraw exists.  We are at least DX1.
//DEADCODE RDH 26/04/00     (*pdwDXVersion) = 0x100;
//DEADCODE RDH 26/04/00 
//DEADCODE RDH 26/04/00     // Let's see if IID_IDirectDraw2 exists.
//DEADCODE RDH 26/04/00     hr = pDDraw->QueryInterface( IID_IDirectDraw2, (VOID**)&pDDraw2 );
//DEADCODE RDH 26/04/00     if( FAILED(hr) )
//DEADCODE RDH 26/04/00     {
//DEADCODE RDH 26/04/00         // No IDirectDraw2 exists... must be DX1
//DEADCODE RDH 26/04/00         pDDraw->Release();
//DEADCODE RDH 26/04/00         FreeLibrary( DDHinst );
//DEADCODE RDH 26/04/00         OutputDebugString( "Couldn't QI DDraw2\r\n" );
//DEADCODE RDH 26/04/00         return;
//DEADCODE RDH 26/04/00     }
//DEADCODE RDH 26/04/00 
//DEADCODE RDH 26/04/00     // IDirectDraw2 exists. We must be at least DX2
//DEADCODE RDH 26/04/00     pDDraw2->Release();
//DEADCODE RDH 26/04/00     (*pdwDXVersion) = 0x200;
//DEADCODE RDH 26/04/00 
//DEADCODE RDH 26/04/00 
//DEADCODE RDH 26/04/00     ///////////////////////////////////////////////////////////////////////////
//DEADCODE RDH 26/04/00     // DirectX 3.0 Checks
//DEADCODE RDH 26/04/00     ///////////////////////////////////////////////////////////////////////////
//DEADCODE RDH 26/04/00 
//DEADCODE RDH 26/04/00     // DirectInput was added for DX3
//DEADCODE RDH 26/04/00     DIHinst = LoadLibrary( "DINPUT.DLL" );
//DEADCODE RDH 26/04/00     if( DIHinst == 0 )
//DEADCODE RDH 26/04/00     {
//DEADCODE RDH 26/04/00         // No DInput... must not be DX3
//DEADCODE RDH 26/04/00         OutputDebugString( "Couldn't LoadLibrary DInput\r\n" );
//DEADCODE RDH 26/04/00         pDDraw->Release();
//DEADCODE RDH 26/04/00         FreeLibrary( DDHinst );
//DEADCODE RDH 26/04/00         return;
//DEADCODE RDH 26/04/00     }
//DEADCODE RDH 26/04/00 
//DEADCODE RDH 26/04/00     DirectInputCreate = (DIRECTINPUTCREATE)GetProcAddress( DIHinst,
//DEADCODE RDH 26/04/00                                                         "DirectInputCreateA" );
//DEADCODE RDH 26/04/00     if( DirectInputCreate == 0 )
//DEADCODE RDH 26/04/00     {
//DEADCODE RDH 26/04/00         // No DInput... must be DX2
//DEADCODE RDH 26/04/00         FreeLibrary( DIHinst );
//DEADCODE RDH 26/04/00         FreeLibrary( DDHinst );
//DEADCODE RDH 26/04/00         pDDraw->Release();
//DEADCODE RDH 26/04/00         OutputDebugString( "Couldn't GetProcAddress DInputCreate\r\n" );
//DEADCODE RDH 26/04/00         return;
//DEADCODE RDH 26/04/00     }
//DEADCODE RDH 26/04/00 
//DEADCODE RDH 26/04/00     // DirectInputCreate exists. We are at least DX3
//DEADCODE RDH 26/04/00     (*pdwDXVersion) = 0x300;
//DEADCODE RDH 26/04/00     FreeLibrary( DIHinst );
//DEADCODE RDH 26/04/00 
//DEADCODE RDH 26/04/00     // Can do checks for 3a vs 3b here
//DEADCODE RDH 26/04/00 
//DEADCODE RDH 26/04/00 
//DEADCODE RDH 26/04/00     ///////////////////////////////////////////////////////////////////////////
//DEADCODE RDH 26/04/00     // DirectX 5.0 Checks
//DEADCODE RDH 26/04/00     ///////////////////////////////////////////////////////////////////////////
//DEADCODE RDH 26/04/00 
//DEADCODE RDH 26/04/00     // We can tell if DX5 is present by checking for the existence of
//DEADCODE RDH 26/04/00     // IDirectDrawSurface3. First, we need a surface to QI off of.
//DEADCODE RDH 26/04/00     DDSURFACEDESC ddsd;
//DEADCODE RDH 26/04/00     ZeroMemory( &ddsd, sizeof(ddsd) );
//DEADCODE RDH 26/04/00     ddsd.dwSize         = sizeof(ddsd);
//DEADCODE RDH 26/04/00     ddsd.dwFlags        = DDSD_CAPS;
//DEADCODE RDH 26/04/00     ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
//DEADCODE RDH 26/04/00 
//DEADCODE RDH 26/04/00     hr = pDDraw->SetCooperativeLevel( NULL, DDSCL_NORMAL );
//DEADCODE RDH 26/04/00     if( FAILED(hr) )
//DEADCODE RDH 26/04/00     {
//DEADCODE RDH 26/04/00         // Failure. This means DDraw isn't properly installed.
//DEADCODE RDH 26/04/00         pDDraw->Release();
//DEADCODE RDH 26/04/00         FreeLibrary( DDHinst );
//DEADCODE RDH 26/04/00         (*pdwDXVersion) = 0;
//DEADCODE RDH 26/04/00         OutputDebugString( "Couldn't Set coop level\r\n" );
//DEADCODE RDH 26/04/00         return;
//DEADCODE RDH 26/04/00     }
//DEADCODE RDH 26/04/00 
//DEADCODE RDH 26/04/00     hr = pDDraw->CreateSurface( &ddsd, &pSurf, NULL );
//DEADCODE RDH 26/04/00     if( FAILED(hr) )
//DEADCODE RDH 26/04/00     {
//DEADCODE RDH 26/04/00         // Failure. This means DDraw isn't properly installed.
//DEADCODE RDH 26/04/00         pDDraw->Release();
//DEADCODE RDH 26/04/00         FreeLibrary( DDHinst );
//DEADCODE RDH 26/04/00         *pdwDXVersion = 0;
//DEADCODE RDH 26/04/00         OutputDebugString( "Couldn't CreateSurface\r\n" );
//DEADCODE RDH 26/04/00         return;
//DEADCODE RDH 26/04/00     }
//DEADCODE RDH 26/04/00 
//DEADCODE RDH 26/04/00     // Query for the IDirectDrawSurface3 interface
//DEADCODE RDH 26/04/00     if( FAILED( pSurf->QueryInterface( IID_IDirectDrawSurface3,
//DEADCODE RDH 26/04/00                                        (VOID**)&pSurf3 ) ) )
//DEADCODE RDH 26/04/00     {
//DEADCODE RDH 26/04/00         pDDraw->Release();
//DEADCODE RDH 26/04/00         FreeLibrary( DDHinst );
//DEADCODE RDH 26/04/00         return;
//DEADCODE RDH 26/04/00     }
//DEADCODE RDH 26/04/00 
//DEADCODE RDH 26/04/00     // QI for IDirectDrawSurface3 succeeded. We must be at least DX5
//DEADCODE RDH 26/04/00     (*pdwDXVersion) = 0x500;
//DEADCODE RDH 26/04/00 
//DEADCODE RDH 26/04/00 
//DEADCODE RDH 26/04/00     ///////////////////////////////////////////////////////////////////////////
//DEADCODE RDH 26/04/00     // DirectX 6.0 Checks
//DEADCODE RDH 26/04/00     ///////////////////////////////////////////////////////////////////////////
//DEADCODE RDH 26/04/00 
//DEADCODE RDH 26/04/00     // The IDirectDrawSurface4 interface was introduced with DX 6.0
//DEADCODE RDH 26/04/00     if( FAILED( pSurf->QueryInterface( IID_IDirectDrawSurface4,
//DEADCODE RDH 26/04/00                                        (VOID**)&pSurf4 ) ) )
//DEADCODE RDH 26/04/00     {
//DEADCODE RDH 26/04/00         pDDraw->Release();
//DEADCODE RDH 26/04/00         FreeLibrary( DDHinst );
//DEADCODE RDH 26/04/00         return;
//DEADCODE RDH 26/04/00     }
//DEADCODE RDH 26/04/00 
//DEADCODE RDH 26/04/00     // IDirectDrawSurface4 was create successfully. We must be at least DX6
//DEADCODE RDH 26/04/00     (*pdwDXVersion) = 0x600;
//DEADCODE RDH 26/04/00     pSurf->Release();
//DEADCODE RDH 26/04/00     pDDraw->Release();
//DEADCODE RDH 26/04/00 
//DEADCODE RDH 26/04/00 
//DEADCODE RDH 26/04/00     ///////////////////////////////////////////////////////////////////////////
//DEADCODE RDH 26/04/00     // DirectX 6.1 Checks
    ///////////////////////////////////////////////////////////////////////////

    // Check for DMusic, which was introduced with DX6.1
 //   LPDIRECTMUSIC pDMusic = NULL;
 //   CoInitialize( NULL );
 //  hr = CoCreateInstance( CLSID_DirectMusic, NULL, CLSCTX_INPROC_SERVER,
 //                          IID_IDirectMusic, (VOID**)&pDMusic );
 //   if( FAILED(hr) )
 //  {
 //       OutputDebugString( "Couldn't create CLSID_DirectMusic\r\n" );
 //       FreeLibrary( DDHinst );
 //       return;
 //   }

    // DirectMusic was created successfully. We must be at least DX6.1
 //   (*pdwDXVersion) = 0x601;
 //  pDMusic->Release();
 //   CoUninitialize();
    

    ///////////////////////////////////////////////////////////////////////////
    // DirectX 7.0 Checks
    ///////////////////////////////////////////////////////////////////////////

    // Check for DirectX 7 by creating a DDraw7 object
//DEADCODE RDH 26/04/00     LPDIRECTDRAW7 pDD7;
    DirectDrawCreateEx = (DIRECTDRAWCREATEEX)GetProcAddress( DDHinst,
                                                       "DirectDrawCreateEx" );
    if( NULL == DirectDrawCreateEx )
    {
        FreeLibrary( DDHinst );
        return;
    }

//DEADCODE RDH 26/04/00     if( FAILED( DirectDrawCreateEx( NULL, (VOID**)&pDD7, IID_IDirectDraw7,
//DEADCODE RDH 26/04/00                                     NULL ) ) )
//DEADCODE RDH 26/04/00     {
//DEADCODE RDH 26/04/00         FreeLibrary( DDHinst );
//DEADCODE RDH 26/04/00         return;
//DEADCODE RDH 26/04/00     }

    // DDraw7 was created successfully. We must be at least DX7.0
    (*pdwDXVersion) = 0x700;
//DEADCODE RDH 26/04/00     pDD7->Release();

    
    ///////////////////////////////////////////////////////////////////////////
    // End of checks
    ///////////////////////////////////////////////////////////////////////////

    // Close open libraries and return
    FreeLibrary( DDHinst );
    
    return;
}



