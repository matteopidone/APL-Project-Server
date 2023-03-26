# Project - Advanced Programming Languages
# Server - C++ - Drogon Framework
Server realizzato con l'utilizzo del Framework `Drogon` in `C++`.<br>
Repository GitHub Framework Drogon: <a href="https://github.com/drogonframework/drogon" target="_blank">clicca qui</a><br>
Tutte le classi utilizzate all'interno del progetto, sono suddivise in due file:
-	File `.h` , per la definizione delle funzioni
-	File `.cc` , per l'implementazione delle funzioni
# Installazione ed Utilizzo
Per utilizzare il server è necessario Docker.<br>
Dopo aver clonato il repository eseguire i seguenti comandi all'interno della directory del progetto:
```bash
mkdir mysql_data
docker compose up
```
In questo modo verranno creati due container.<br>
Nel primo verranno installate le dipendenze del framework, verrà compilato il progetto e poi eseguito.<br>
Nel secondo verrà installato il database `mysql` con un relativo dump. In questo modo saranno già disponibili alcuni dati relativi al progetto.

# Struttura Progetto
L'entry point del progetto è il file `main.cc`.<br>
Qui viene caricato a runtime il file di configurazione `config.json` e viene istanziato il server.

Le directory principali sono:
-	`build` -> file relativi al build del progetto, tra cui l'eseguibile
-	`controllers` -> controller che definiscono gli `endpoint` del server
-	`models` -> model relativi alle strutture dati coinvolte
-	`plugins` -> funzionalità aggiuntive del progetto

## Controllers
Nella directory `controllers`, sono presenti due classi che estendono la classe `HttpController` e `Utility` (vedi plugins).<br>
La classe `HttpController` è una classe del Framework Drogon, che consente di associare delle funzioni a degli endpoint.<br>
Le classi in questione sono:
-	`UserController` , funzionalità relative agli utenti
-	`HolidayController` , funzionalità relative alle ferie

## Models
Nella directory `models`, sono presenti due classi che offrono una serie di funzionalità per la manipolazione dei dati e l'accesso al database.<br>
Le classi sono:
-	`User` , per la gestione degli utenti
-	`Holiday` , per la gestione delle ferie

## Plugins
Nella directory `plugins`, sono presenti due classi per la gestione di funzionalità aggiuntive.<br>
Le classi sono:
-	`jwt` , per la gestione dell'autenticazione attraverso l'utilizzo di `Json Web Token`
-	`utility` , per la gestione di funzionalità e controlli aggiuntivi di uso comune

È presente anche un file `constants.h`, in cui sono definite le costanti utilizzate nella definizione degli endpoint.<br>
