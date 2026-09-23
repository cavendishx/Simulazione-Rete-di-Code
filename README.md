# Queueing Network Simulation

**Queueing network simulation** developed using **OMNeT++**, aimed at studying the performance of a queueing system with **batch arrivals, two user classes, priority, and a single server**.

The model is inspired by a **Wireless Sensor Network (WSN)** scenario, in which data collected by sensors are aggregated and subsequently processed by a central system.

## 🧩 Model

The system consists of:

* **2 user classes**, with class 1 having priority over class 2;
* **batch arrivals**, with exponentially distributed inter-arrival times;
* a **shared queue**;
* a **single server**;
* a **parameterized service policy**;
* **service times** consisting of a deterministic component and a random component;
* a **Single Vacation Rule (SVR)**, according to which the server enters a vacation when neither class can be served;
* a **Set-Up Process**, which determines when the server can resume service after the vacation.

The general structure of the system is:

```text
Source → Queue → Server → Sink
```

### Service Policy

The server gives priority to **class 1**. If the queue contains at least `a₁` class 1 users, a batch of size

```text
r₁ = min(b₁, number of class 1 users in the queue)
```

is served.

If class 1 cannot be served, class 2 is considered according to the same policy.

When neither class satisfies the conditions required for service, the server enters a **vacation**.

After the vacation phase ends, the server goes through a **set-up phase** before resuming normal service.

## 🛠️ Technologies

* **OMNeT++**
* **C++**
* **NED**
* **OMNeT++ Message Definition Language**
* **Python**
* **Jupyter Notebook**

## 📁 Repository Structure

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

## 📊 Performance Analysis

The simulation results are subsequently analyzed using the Python notebook:

```text
analisi_prestazioni_sistema.ipynb
```

The notebook contains the statistical analysis of the system's performance, carried out using the **independent replications method**.

In particular, it calculates:

* **point estimates** of the quantities of interest;
* **confidence intervals** for the estimates;
* analysis of the results obtained from the different simulation replications.

The analysis is performed in **Python** using **Jupyter Notebook**.

## 🚀 Running the Simulation

The `componenti_omnet` folder contains the **model source files**, but not a complete OMNeT++ project.

To run the simulation:

1. Install **OMNeT++**.
2. Create a **new OMNeT++ project**.
3. Copy the contents of the `componenti_omnet` folder into the project, preserving the directory structure.
4. Build the project.
5. Run the simulation using the configuration defined in `omnetpp.ini`.

The `net.ned` file defines the simulated network, while `omnetpp.ini` contains the configuration and parameters used for the simulations.

## 🐍 Python Analysis

To perform the statistical analysis, a Python environment with **Jupyter Notebook** and the libraries used by the notebook is required.

Open:

```text
analisi_prestazioni_sistema.ipynb
```

and run the notebook cells to obtain the point estimates and corresponding confidence intervals.
