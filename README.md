# Simulazione di una rete di code

**Simulazione di una rete di code** sviluppata tramite **OMNeT++**, finalizzata allo studio delle prestazioni di un sistema di code con **arrivi batch, due classi di utenti, priorità e singolo server**.

Il modello è ispirato a uno scenario di **Wireless Sensor Networks (WSN)**, in cui i dati raccolti dai sensori vengono aggregati e successivamente elaborati da un sistema centrale.

## 🧩 Modello

Il sistema è costituito da:

* **2 classi di utenti**, con priorità della classe 1 sulla classe 2;
* **arrivi batch**, con tempi tra gli arrivi distribuiti esponenzialmente;
* una **coda condivisa**;
* un **singolo server**;
* una **politica di servizio** parametrizzata;
* **tempi di servizio** costituiti da una componente deterministica e una componente casuale;
* una **Single Vacation Rule (SVR)**, secondo cui il server entra in vacanza quando nessuna delle due classi può essere servita;
* un **Set-Up Process**, che determina quando il server può riprendere il servizio al termine della vacation.

La struttura generale del sistema è:

```text
Source → Queue → Server → Sink
```

### Politica di servizio

Il server dà priorità alla **classe 1**. Se nella coda sono presenti almeno `a₁` utenti di classe 1, viene servito un batch di dimensione:

```text
r₁ = min(b₁, numero di utenti di classe 1 in coda)
```

Se la classe 1 non può essere servita, viene considerata la **classe 2** secondo la stessa logica.

Quando nessuna delle due classi soddisfa le condizioni necessarie per il servizio, il server entra in **vacation**.

Terminata la fase di vacation, il server effettua una fase di **set-up** prima di riprendere il normale servizio.

## 🛠️ Tecnologie

* **OMNeT++**
* **C++**
* **NED**
* **OMNeT++ Message Definition Language**
* **Python**
* **Jupyter Notebook**

## 📁 Struttura del repository

```text
├── componenti_omnet/
│   ├── components/
│   │   ├── queue/
│   │   │   ├── Queue.cc
│   │   │   ├── Queue.h
│   │   │   └── Queue.ned
│   │   ├── server/
│   │   │   ├── Server.cc
│   │   │   ├── Server.h
│   │   │   └── Server.ned
│   │   ├── sink/
│   │   │   ├── Sink.cc
│   │   │   ├── Sink.h
│   │   │   └── Sink.ned
│   │   └── source/
│   │       ├── Source.cc
│   │       ├── Source.h
│   │       └── Source.ned
│   ├── Job.msg
│   ├── net.ned
│   └── omnetpp.ini
│
└── analisi_prestazioni_sistema.ipynb
```

## 📊 Analisi delle prestazioni

I risultati delle simulazioni vengono successivamente analizzati tramite il notebook Python:

```text
analisi_prestazioni_sistema.ipynb
```

Il notebook contiene l'analisi statistica delle prestazioni del sistema, effettuata mediante il **metodo delle repliche indipendenti**.

In particolare, vengono calcolate:

* **stime puntuali** delle grandezze di interesse;
* **intervalli di confidenza** delle stime;
* analisi dei risultati ottenuti dalle diverse repliche della simulazione.

L'analisi viene effettuata in **Python** utilizzando **Jupyter Notebook**.

## 🚀 Avvio della simulazione

La cartella `componenti_omnet` contiene i **file sorgente del modello**, ma non un progetto OMNeT++ completo.

Per eseguire la simulazione:

1. Installare **OMNeT++**.
2. Creare un **nuovo progetto OMNeT++**.
3. Copiare all'interno del progetto il contenuto della cartella `componenti_omnet`, mantenendo la struttura delle directory.
4. Compilare il progetto.
5. Avviare la simulazione utilizzando la configurazione definita in `omnetpp.ini`.

Il file `net.ned` definisce la rete simulata, mentre `omnetpp.ini` contiene la configurazione e i parametri utilizzati per le simulazioni.

## 🐍 Analisi con Python

Per eseguire l'analisi statistica è necessario disporre di un ambiente Python con **Jupyter Notebook** e le librerie utilizzate dal notebook.

Aprire:

```text
analisi_prestazioni_sistema.ipynb
```

ed eseguire le celle del notebook per ottenere le stime puntuali e i relativi intervalli di confidenza.

---

