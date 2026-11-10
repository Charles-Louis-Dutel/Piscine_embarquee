# Piscine Embarquée — École 42

Projet réalisé en **C** dans le cadre d'une piscine intensive de trois semaines consacrée à la programmation de systèmes embarqués à l'école 42.

L'objectif est de découvrir le développement sur microcontrôleur **ATmega328P (architecture AVR 8 bits)**, en manipulant directement les registres matériels, sans utiliser les abstractions de l'environnement Arduino.

Cette piscine comporte dix modules progressifs abordant la programmation bas niveau, la gestion des périphériques et les protocoles de communication.

## Modules

### Module 00 — Premiers programmes et GPIO
- Découverte de l'ATmega328P et de son environnement de développement.
- Compilation croisée avec `avr-gcc` et programmation du microcontrôleur.
- Configuration des entrées/sorties numériques avec les registres `DDRx`, `PORTx` et `PINx`.
- Pilotage de LED, lecture de boutons et réalisation d'un compteur binaire.

### Module 01 — Timers
- Gestion du temps et des délais.
- Configuration des timers matériels et des prescalers.
- Génération de signaux périodiques.
- Manipulation des rapports cycliques (*duty cycle*).

### Module 02 — Communication UART
- Configuration d'une communication série asynchrone à 115 200 bauds.
- Transmission et réception de caractères et de chaînes.
- Manipulation des registres de l'interface USART.
- Traitement des données reçues et interaction avec un terminal série.

### Module 03 — RGB et timers avancés
- Pilotage d'une LED RGB.
- Utilisation de la modulation de largeur d'impulsion (PWM).
- Gestion des couleurs sur différentes résolutions, jusqu'à 24 bits.
- Contrôle des couleurs à partir de commandes reçues par UART.

### Module 04 — Interruptions
- Configuration des interruptions externes.
- Gestion des événements sans interrogation permanente (*polling*).
- Utilisation des interruptions liées aux timers.
- Pilotage de sorties et réalisation d'un compteur binaire avec interruptions.

### Module 05 — Conversion analogique-numérique (ADC)
- Configuration du convertisseur ADC 10 bits.
- Acquisition et traitement de signaux analogiques.
- Lecture et interprétation de mesures de température.
- Utilisation de valeurs analogiques pour contrôler une LED RGB.

### Module 06 — Communication I²C (TWI)
- Configuration du microcontrôleur en maître I²C.
- Gestion des conditions START, STOP et des acquittements ACK/NACK.
- Communication avec un capteur de température et d'humidité **AHT20**.
- Lecture et interprétation des données transmises par le capteur.

### Module 07 — Mémoire EEPROM
- Lecture et écriture de données en mémoire non volatile.
- Manipulation des registres de l'EEPROM.
- Gestion des adresses et des opérations d'écriture.
- Introduction au contrôle d'intégrité des données avec CRC.

### Module 08 — Communication SPI
- Configuration du protocole SPI en mode maître.
- Transmission synchrone de données vers des périphériques externes.
- Pilotage de LED adressables **SK9822**.
- Gestion des couleurs et réalisation de séquences lumineuses.

### Module 09 — Expandeurs d'entrées/sorties et afficheurs 7 segments
- Communication avec l'expandeur d'entrées/sorties **PCA9555** via I²C.
- Extension du nombre de GPIO disponibles.
- Pilotage d'un afficheur 7 segments.
- Affichage de chiffres et gestion de plusieurs afficheurs.
- Exploitation des périphériques externes pour réaliser des affichages dynamiques.

## Environnement technique

- **Langage :** C
- **Microcontrôleur :** ATmega328P
- **Architecture :** AVR 8 bits
- **Outils :** avr-gcc, avr-objcopy, avrdude, Makefile
- **Protocoles :** UART, I²C, SPI
- **Périphériques :** GPIO, timers, ADC, PWM, interruptions, EEPROM
- **Composants :** AHT20, SK9822, PCA9555

## Compétences mises en œuvre

- Programmation embarquée en C
- Manipulation directe des registres matériels
- Opérations binaires et masques de bits
- Configuration des périphériques d'un microcontrôleur
- Gestion des interruptions et des contraintes temporelles
- Communication avec des capteurs et composants électroniques
- Lecture de datasheets et de schémas électroniques
- Débogage et validation sur matériel

## Auteur

Charles-Louis Dutel — [GitHub](https://github.com/Charles-Louis-Dutel)
