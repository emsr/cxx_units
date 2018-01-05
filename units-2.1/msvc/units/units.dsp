# Microsoft Developer Studio Project File - Name="units" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=units - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "units.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "units.mak" CFG="units - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "units - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "units - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "units - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "UNITS_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "../../src" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "UNITS_EXPORTS" /D "UNITS_BUILD_DLL" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=mkdir ..\..\lib	copy Release\units.lib ..\..\lib	copy Release\units.dll ..\..\lib
# End Special Build Tool

!ELSEIF  "$(CFG)" == "units - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "UNITS_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "../../src" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "UNITS_EXPORTS" /D "UNITS_BUILD_DLL" /D "UNITS_INCLUDE_TESTS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=mkdir ..\..\lib	copy Debug\units.lib ..\..\lib	copy Debug\units.dll ..\..\lib
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "units - Win32 Release"
# Name "units - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "scalar Source"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=..\..\src\scalar\Acceleration.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\Angle.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\AngularAcceleration.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\AngularSpeed.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\Area.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\Current.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\Density.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\Force.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\Frequency.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\Inertia.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\Length.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\Mass.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\MassFlowRate.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\Power.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\Pressure.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\SignedAngle.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\Speed.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\Temperature.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\Time.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\Torque.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\UnsignedAngle.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\Voltage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\Volume.cpp
# End Source File
# End Group
# Begin Group "vector2D Source"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=..\..\src\vector2D\Acceleration2D.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\vector2D\Angle2D.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\vector2D\Direction2D.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\vector2D\Force2D.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\vector2D\Length2D.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\vector2D\Rotation2D.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\vector2D\Speed2D.cpp
# End Source File
# End Group
# Begin Group "vector3D Source"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=..\..\src\vector3D\Acceleration3D.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\vector3D\AngularAcceleration3D.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\vector3D\AngularSpeed3D.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\vector3D\Direction3D.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\vector3D\Force3D.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\vector3D\Length3D.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\vector3D\MatrixRotation3D.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\vector3D\QuaternionRotation3D.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\vector3D\Rotation3D.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\vector3D\Speed3D.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\vector3D\Torque3D.cpp
# End Source File
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "scalar Headers"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=..\..\src\scalar\Acceleration.h
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\Angle.h
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\AngularAcceleration.h
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\AngularSpeed.h
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\Area.h
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\Current.h
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\Density.h
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\Force.h
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\Frequency.h
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\Inertia.h
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\Length.h
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\Mass.h
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\MassFlowRate.h
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\Power.h
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\Pressure.h
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\ProductUnitFormat.h
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\RatioUnitFormat.h
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\RepeatedUnit.h
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\SignedAngle.h
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\SpecificUnit.h
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\Speed.h
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\Temperature.h
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\Time.h
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\Torque.h
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\Unit.h
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\UnsignedAngle.h
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\Voltage.h
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\Volume.h
# End Source File
# End Group
# Begin Group "vector2D Headers"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=..\..\src\vector2D\Acceleration2D.h
# End Source File
# Begin Source File

SOURCE=..\..\src\vector2D\Angle2D.h
# End Source File
# Begin Source File

SOURCE=..\..\src\vector2D\Direction2D.h
# End Source File
# Begin Source File

SOURCE=..\..\src\vector2D\Force2D.h
# End Source File
# Begin Source File

SOURCE=..\..\src\vector2D\Length2D.h
# End Source File
# Begin Source File

SOURCE=..\..\src\vector2D\Rotation2D.h
# End Source File
# Begin Source File

SOURCE=..\..\src\vector2D\Speed2D.h
# End Source File
# Begin Source File

SOURCE=..\..\src\vector2D\Unit2D.h
# End Source File
# Begin Source File

SOURCE=..\..\src\vector2D\Vector2D.h
# End Source File
# End Group
# Begin Group "vector3D Headers"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=..\..\src\vector3D\Acceleration3D.h
# End Source File
# Begin Source File

SOURCE=..\..\src\vector3D\AngularAcceleration3D.h
# End Source File
# Begin Source File

SOURCE=..\..\src\vector3D\AngularSpeed3D.h
# End Source File
# Begin Source File

SOURCE=..\..\src\vector3D\Direction3D.h
# End Source File
# Begin Source File

SOURCE=..\..\src\vector3D\Force3D.h
# End Source File
# Begin Source File

SOURCE=..\..\src\vector3D\Length3D.h
# End Source File
# Begin Source File

SOURCE=..\..\src\vector3D\MatrixRotation3D.h
# End Source File
# Begin Source File

SOURCE=..\..\src\vector3D\QuaternionRotation3D.h
# End Source File
# Begin Source File

SOURCE=..\..\src\vector3D\Rotation3D.h
# End Source File
# Begin Source File

SOURCE=..\..\src\vector3D\Speed3D.h
# End Source File
# Begin Source File

SOURCE=..\..\src\vector3D\Torque3D.h
# End Source File
# Begin Source File

SOURCE=..\..\src\vector3D\Unit3D.h
# End Source File
# Begin Source File

SOURCE=..\..\src\vector3D\Vector3D.h
# End Source File
# End Group
# Begin Group "system"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\system\config.h
# End Source File
# End Group
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "Inline Files"

# PROP Default_Filter "*.i"
# Begin Group "scalar Inlines"

# PROP Default_Filter "*.i"
# Begin Source File

SOURCE=..\..\src\scalar\Acceleration.i
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\Angle.i
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\AngularAcceleration.i
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\AngularSpeed.i
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\Area.i
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\Current.i
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\Density.i
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\Force.i
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\Frequency.i
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\Inertia.i
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\Length.i
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\Mass.i
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\MassFlowRate.i
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\Power.i
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\Pressure.i
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\ProductUnitFormat.i
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\RatioUnitFormat.i
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\RepeatedUnit.i
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\SignedAngle.i
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\SpecificUnit.i
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\Speed.i
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\Temperature.i
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\Time.i
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\Torque.i
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\Unit.i
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\UnsignedAngle.i
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\Voltage.i
# End Source File
# Begin Source File

SOURCE=..\..\src\scalar\Volume.i
# End Source File
# End Group
# Begin Group "vector2D Inlines"

# PROP Default_Filter "*.i"
# Begin Source File

SOURCE=..\..\src\vector2D\Acceleration2D.i
# End Source File
# Begin Source File

SOURCE=..\..\src\vector2D\Angle2D.i
# End Source File
# Begin Source File

SOURCE=..\..\src\vector2D\Direction2D.i
# End Source File
# Begin Source File

SOURCE=..\..\src\vector2D\Force2D.i
# End Source File
# Begin Source File

SOURCE=..\..\src\vector2D\Length2D.i
# End Source File
# Begin Source File

SOURCE=..\..\src\vector2D\Rotation2D.i
# End Source File
# Begin Source File

SOURCE=..\..\src\vector2D\Speed2D.i
# End Source File
# Begin Source File

SOURCE=..\..\src\vector2D\Unit2D.i
# End Source File
# Begin Source File

SOURCE=..\..\src\vector2D\Vector2D.i
# End Source File
# End Group
# Begin Group "vector3D Inlines"

# PROP Default_Filter "*.i"
# Begin Source File

SOURCE=..\..\src\vector3D\Acceleration3D.i
# End Source File
# Begin Source File

SOURCE=..\..\src\vector3D\AngularAcceleration3D.i
# End Source File
# Begin Source File

SOURCE=..\..\src\vector3D\AngularSpeed3D.i
# End Source File
# Begin Source File

SOURCE=..\..\src\vector3D\Direction3D.i
# End Source File
# Begin Source File

SOURCE=..\..\src\vector3D\Force3D.i
# End Source File
# Begin Source File

SOURCE=..\..\src\vector3D\Length3D.i
# End Source File
# Begin Source File

SOURCE=..\..\src\vector3D\MatrixRotation3D.i
# End Source File
# Begin Source File

SOURCE=..\..\src\vector3D\QuaternionRotation3D.i
# End Source File
# Begin Source File

SOURCE=..\..\src\vector3D\Rotation3D.i
# End Source File
# Begin Source File

SOURCE=..\..\src\vector3D\Speed3D.i
# End Source File
# Begin Source File

SOURCE=..\..\src\vector3D\Torque3D.i
# End Source File
# Begin Source File

SOURCE=..\..\src\vector3D\Unit3D.i
# End Source File
# Begin Source File

SOURCE=..\..\src\vector3D\Vector3D.i
# End Source File
# End Group
# End Group
# Begin Group "Template Files"

# PROP Default_Filter "*.cpp"
# Begin Group "scalar Templates"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\scalar\Unit.cpp

!IF  "$(CFG)" == "units - Win32 Release"

!ELSEIF  "$(CFG)" == "units - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "vector2D Templates"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\vector2D\Unit2D.cpp

!IF  "$(CFG)" == "units - Win32 Release"

!ELSEIF  "$(CFG)" == "units - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\src\vector2D\Vector2D.cpp

!IF  "$(CFG)" == "units - Win32 Release"

!ELSEIF  "$(CFG)" == "units - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "vector3D Templates"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\vector3D\Unit3D.cpp

!IF  "$(CFG)" == "units - Win32 Release"

!ELSEIF  "$(CFG)" == "units - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\src\vector3D\Vector3D.cpp

!IF  "$(CFG)" == "units - Win32 Release"

!ELSEIF  "$(CFG)" == "units - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# End Group
# End Target
# End Project
