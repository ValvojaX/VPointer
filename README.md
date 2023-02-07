# VPointer

A simple helper class for reading from memory in untraditional ways (eg. ReadProcessMemory)

## Description

Originally I used this for reading undocumented structures from windows kernel with a driver, but for this repository I changed it to use a more common function ReadProcessMemory. VPointer's functionality is simple and there is not a lot of code needed, so it can be easily adjusted if necessary.

## Getting Started

### Example usage

```C
#include "VPointer.h"

// Set handle to process (used by VPointer internally)
mem::m_hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessId);

// Get address of player health
DWORD dwPlayerHealth = ...

// With ReadProcessMemory
DWORD health = 0;
BOOL success = ReadProcessMemory(hProcess, (LPCVOID)dwPlayerHealth, &health, sizeof(health), NULL);
printf("Health: %d at address %p\n", health, dwPlayerHealth);

// With VPointer
mem::VPointer<DWORD> pHealth = mem::VPointer<DWORD>(dwPlayerHealth);
printf("Health: %d at address %p\n", *pHealth, &pHealth);
```

Using VPointer makes reading structures a lot easier, especially if they are chained.
```C
struct Vector3D
{
    float x, y, z;
};

struct LocalPlayer
{
    int m_health;
    int m_ammo;
    mem::VPointer<Vector3D> m_pos;
};

// Get address of local player
DWORD dwLocalPlayer = ...

// Read structures
mem::VPointer<LocalPlayer> pPlayer = mem::VPointer<LocalPlayer>(dwLocalPlayer);
printf("Health: %d Ammo: %d Position: (%f, %f, %f)\n", 
    pPlayer->m_health, pPlayer->m_ammo, pPlayer->m_pos->x, pPlayer->m_pos->y, pPlayer->m_pos->z);
```

## Version History

* 0.1
    * Initial Release