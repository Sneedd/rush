


Rush Utility Library
===============================================================================
Die Rush Utility Library ist eine einfach zu Bediende Klassenbibliotek, ohne
kompizierte Programmierkonstrukte, wie sie in der std vorkommen.

Der Name "Rush" kommt von dem Hund von MegaMan, der ihn bei seinen Abenteuern
unterstützt hat.




Konfiguration
===============================================================================
Die Defines können in der Datei "config.h" eingetragen werden oder aber
über den Compiler. Beispiel MinGW: -D_RUSH_WINDOWS_

#define _RUSH_LINUX_                Linux Unterstützung
#define _RUSH_WINDOWS_              Windows Unterstützung

#define _RUSH_SUPPORTS_STD_         std Klassenbiliothek Unterstützung
#define _RUSH_SUPPORTS_WXWIDGETS_   wxWidgets Klassenbiliothek Unterstützung

#define _RUSH_UNICODE_              Unicode Unterstützung



