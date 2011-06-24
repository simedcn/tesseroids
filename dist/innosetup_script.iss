; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{64816CC6-3C40-48F8-8937-4236AABECD23}
AppName=Tesseroids
AppVerName=Tesseroids 1.0
AppPublisher=Leonardo Uieda
AppPublisherURL=http://code.google.com/p/tesseroids/
AppSupportURL=https://leouieda-tesseroids-docs.googlecode.com/hg/doc/build/html/index.html
AppUpdatesURL=http://code.google.com/p/tesseroids/
DefaultDirName={pf}\Tesseroids_v1_0
DefaultGroupName=Tesseroids_v1_0
SetupIconFile=C:\Users\Leo\tesseroids\doc\images\logo.ico
LicenseFile=C:\Users\Leo\tesseroids\dist\tesseroids-1.0\LICENSE
InfoAfterFile=C:\Users\Leo\tesseroids\dist\postsetup_info.txt
OutputDir=C:\Users\Leo\tesseroids\dist
OutputBaseFilename=tesseroids-1.0-win32
Compression=lzma
SolidCompression=yes
AlwaysRestart=yes

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Files]
Source: "C:\Users\Leo\tesseroids\dist\tesseroids-1.0\bin\*"; DestDir: "{app}\bin"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "C:\Users\Leo\tesseroids\dist\tesseroids-1.0\examples\*"; DestDir: "{app}\examples"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "C:\Users\Leo\tesseroids-docs\doc\build\html\*"; DestDir: "{app}\doc\html"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "C:\Users\Leo\tesseroids-docs\doc\build\user-manual-v1_0.html"; DestDir: "{app}\doc"; Flags: ignoreversion
Source: "C:\Users\Leo\tesseroids\dist\tesseroids-1.0\LICENSE"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\Leo\tesseroids\dist\tesseroids-1.0\README"; DestDir: "{app}"; Flags: ignoreversion
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{group}\{cm:UninstallProgram,Tesseroids}"; Filename: "{uninstallexe}"
Name: "{group}\{cm:ProgramOnTheWeb,User Manual}"; Filename: "https://leouieda-tesseroids-docs.googlecode.com/hg/doc/build/html/index.html"

[Registry]
Root: HKCU ; Subkey: "Environment"; ValueType: string; ValueName: "PATH"; ValueData: "{olddata};{app}\bin"