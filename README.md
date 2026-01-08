# Raspberry Pi 5 – 4× LED “chaser” (rechts → links) – headless via SSH, ontwikkelen met VS Code + Docker

Dit project bouwt en runt een C-programma dat **4 GPIO-pinnen** aanstuurt zodat **4 LEDs** in een “looplicht” patroon knipperen (één LED tegelijk).  
Je werkt vanaf een **Windows-pc** met **Visual Studio Code + Docker**, en je gebruikt de **Raspberry Pi 5 volledig headless** (geen scherm/keyboard), alleen via **SSH (command line)**.

---

## Inhoud

- [Wat je krijgt](#wat-je-krijgt)
- [Benodigdheden](#benodigdheden)
- [Hardware aansluiten](#hardware-aansluiten)
- [Stap 0 — microSD/SSD volledig “clearen” (Windows)](#stap-0--microsdssd-volledig-clearen-windows)
- [Stap 1 — Raspberry Pi OS Lite flashen (headless)](#stap-1--raspberry-pi-os-lite-flashen-headless)
- [Stap 2 — SSH verbinden](#stap-2--ssh-verbinden)
- [Stap 3 — Packages installeren op de Pi](#stap-3--packages-installeren-op-de-pi)
- [Stap 4 — Project clonen en bouwen](#stap-4--project-clonen-en-bouwen)
- [Stap 5 — Programma runnen en testen](#stap-5--programma-runnen-en-testen)
- [Stap 6 — Automatisch starten bij boot (systemd)](#stap-6--automatisch-starten-bij-boot-systemd)
- [Stap 7 — Ontwikkelen met VS Code + Docker](#stap-7--ontwikkelen-met-vs-code--docker)
- [Troubleshooting](#troubleshooting)

---

## Wat je krijgt

- `main.c` gebruikt `pigpio` om 4 GPIO’s als output te zetten en ze om de 250ms te schakelen.
- Stoppen met **Ctrl+C** (SIGINT).
- Een stappenplan om:
  1) Pi OS Lite headless te installeren  
  2) via SSH te verbinden  
  3) te bouwen met CMake  
  4) automatisch te starten met systemd  
  5) te ontwikkelen met VS Code + Docker zonder scherm op de Pi

---

## Benodigdheden

**Hardware**
- Raspberry Pi 5
- microSD of USB-SSD met Raspberry Pi OS Lite (aanrader: 64-bit)
- 4× LED
- 4× weerstand (220–330Ω)
- breadboard + jumper wires

**Software (Windows)**
- Raspberry Pi Imager
- Visual Studio Code
- Docker Desktop (voor lokale builds)  
- VS Code extensions:
  - **Remote - SSH**
  - **Dev Containers** (optioneel, als je in containers wil ontwikkelen)
  - **CMake Tools** (handig)

---

## Hardware aansluiten

**GPIO’s (BCM) die in de code staan:**
- GPIO17, GPIO27, GPIO22, GPIO26

**Per LED:**
- GPIO-pin → **weerstand** → LED **anode** (lange poot)
- LED **kathode** (korte poot) → **GND** (bv. fysieke pin 6/9/14/20/25/30/34/39)

### Richting rechts → links (zonder code aan te passen)
In jouw code loopt de array `LED_PINS` van index 0 → 3.  
Wil je dat het “rechts → links” lijkt, dan zijn er 2 makkelijke manieren:

1) **Plaats je LEDs fysiek zo** dat `LED_PINS[0]` de **rechter** LED is en `LED_PINS[3]` de **linker** LED.  
OF  
2) Pas later (indien gewenst) de volgorde van `LED_PINS` aan (maar dit README verandert je code niet).

---

## Stap 0 — microSD/SSD volledig “clearen” (Windows)

Als je constant errors krijgt zoals “dit is niet de eerste pc” / rare partities / Windows wil niet formatteren: doe een harde wipe van de partitietabel.

1. Open **PowerShell als Administrator**
2. Run:

```bat
diskpart
list disk
select disk N   (KIES HEEL GOED JE SD/SSD!)
clean
exit
