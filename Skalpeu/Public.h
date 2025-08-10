/*++

Module Name:

    public.h

Abstract:

    This module contains the common declarations shared by driver
    and user applications.

Environment:

    user and kernel

--*/

//
// Define an Interface Guid so that app can find the device and talk to it.
//

DEFINE_GUID (GUID_DEVINTERFACE_Skalpeu,
    0x73051051,0x4532,0x4f09,0x9b,0x73,0x46,0x50,0xc7,0x89,0x0a,0xee);
// {73051051-4532-4f09-9b73-4650c7890aee}
