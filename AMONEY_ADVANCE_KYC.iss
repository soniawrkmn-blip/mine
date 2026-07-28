; AMONEY ADVANCE KYC - Inno Setup Script
; Save this as: C:\Users\Yasem\Downloads\Telegram Desktop\AI KYC v3.2\AIKYC-main\AIKYC-main\AMONEY_ADVANCE_KYC.iss

[Setup]
AppId={{9AEC76EE-E617-4999-AF7F-A4AEBF71D26E}
AppName=AMONEY ADVANCE KYC
AppVersion=3.2
AppPublisher=AI Onlyfake
DefaultDirName={pf}\AMONEY ADVANCE KYC
DefaultGroupName=AMONEY ADVANCE KYC
OutputDir=.
OutputBaseFilename=Setup-AMONEY-ADVANCE-KYC
SetupIconFile=icons\logo.ico
Compression=lzma
SolidCompression=yes
WizardStyle=modern
PrivilegesRequired=admin

[Files]
Source: "release\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs

[Icons]
Name: "{group}\AMONEY ADVANCE KYC"; Filename: "{app}\AMONEY_ADVANCE_KYC.exe"
Name: "{commondesktop}\AMONEY ADVANCE KYC"; Filename: "{app}\AMONEY_ADVANCE_KYC.exe"

[Run]
Filename: "{app}\AMONEY_ADVANCE_KYC.exe"; Description: "Launch AMONEY ADVANCE KYC"; Flags: nowait postinstall skipifsilent

[UninstallDelete]
Type: filesandordirs; Name: "{app}"