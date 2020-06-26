
# rush - Utility library
A collection of some C++ datastructures and algorithms. The main goal where putting together classes and functions which I developed over the years and can be reused into one library. There is a lot still missing and a lot is not fully tested. The code was last 2014 really maintained, but may be useful to someone.


## Usage and maintain
Code::Blocks and the MinGW compiler was used. 


## Configuration

```cpp
#define _RUSH_LINUX_                Linux Unterstützung
#define _RUSH_WINDOWS_              Windows Unterstützung

#define _RUSH_SUPPORTS_STD_         std Klassenbiliothek Unterstützung
#define _RUSH_SUPPORTS_WXWIDGETS_   wxWidgets Klassenbiliothek Unterstützung

#define _RUSH_UNICODE_              Unicode Unterstützung
```


## TODO
* Hinzufügen des TODO Verzeichnisses
* XML auf Basis von wxWidgets oder tinyxml2?
 * XML muss Unicode kompatibel sein
* ObjectArray
 * CopyTo() implementieren
 * Reverse() implementieren
 * ReadOnly Flag implementieren
* String
 * Falls _RUSH_SUPPORTS_WXWIDGETS_ aktiv dann in String wxString verwenden
 * Bzw testen ob direkt typedef String wxString; verwendet werden könnte
 * Unicode
* Sortierungen
 * Quicksort
 * Introsort
 * Smoothsort (?)
 * Stabiles Sortierungsverfahren
* Anstatt Dictionary
 * StaticHashTable (Optimiert auf kleiner Speicherbedarf, langsam beim Hinzufügen)
 * DynamicHashTable (Optimiert auf schelles Hinzufügen, großer Speicherbedarf)
 * Hashing von int, string, wxString und Klassen mit IHashable
* Version
 * Read and Write
 * Assigment Operator
 * Copy Constructor
* NTL Library einbauen (als rush::math)
 * Und vervollständigen
* pthreads verwenden (als rush::threads)
 * WorkDistributor (input work und verteilen auf viele threads)
 * WorkCollector (input work und in einem thread abarbeiten)
 * ThreadPool
 * ObjectQueueSafe
 * ObjectStackSafe


## Additional TODOs
* Ini Parser
* CircularBuffer
* CSV Parser
* Like-Comparer
* Hierachial Text File (see Particle Engine Text Format)
* Binary Tree
* Tree Klasse adoptieren (siehe TODO bzw C# ???)
* BinaryTree Klasse implementieren (siehe C# Beispiel???)




