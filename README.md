# Particles-in-a-lattice-Gas-Reticolare
Questo programma in C simula il movimento di particelle in un gas all'interno di un reticolo bidimensionale utilizzando un modello di automa a reticolo

una spiegazione dettagliata del codice:

# Librerie e Definizioni:

# Includono le librerie standard e definiscono costanti per semplificare il codice.
# Funzioni:

inizializzazione_variabili(): Inizializza le variabili utilizzando i valori passati come argomenti da linea di comando.
inizializzazione_generatore(): Inizializza il generatore di numeri casuali con un seme preso dal file /dev/random.
inizializzazione_array(): Alloca la memoria per vari array multidimensionali utilizzati per tenere traccia delle posizioni delle particelle e delle distanze.
inizializzazione_reticolo(): Imposta il reticolo con le particelle distribuite in base alla probabilità fornita.

aggiornamento_reticolo(): Aggiorna le posizioni delle particelle nel reticolo in base a movimenti casuali.
misura(): Calcola la media delle distanze quadrate delle particelle dai loro punti di partenza.
Funzione Main:

Controlla se il numero corretto di argomenti è stato passato al programma.
Inizializza variabili, il generatore di numeri casuali e gli array.
Esegue una simulazione di "num_storie" storie, ciascuna con "num_passi" passaggi.
Misura la distanza media quadrata delle particelle a intervalli specifici.
Calcola il coefficiente di diffusione e lo scrive su un file.
Logica di Simulazione:

Per ogni storia, inizializza il reticolo e poi esegue un numero di passi, aggiornando le posizioni delle particelle e calcolando misurazioni a intervalli regolari.
Errore di Scrittura File:

Se il file coeff_diffusione.dat non può essere aperto, viene stampato un errore.
# Calcolo e Stampa dei Risultati:

Alla fine della simulazione, il programma calcola il coefficiente di diffusione basato sulla media delle distanze quadrate delle particelle e lo scrive nel file di output.
Output Grafico:

Infine, il programma chiama gnuplot per visualizzare graficamente i risultati utilizzando uno script di plot predefinito.
Il codice è strutturato per essere facilmente modificabile per differenti dimensioni del reticolo e probabilità di occupazione delle particelle, permettendo di esplorare come questi fattori influenzano la diffusione in un gas ideale.
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
# This C program simulates the movement of particles in a lattice gas using a two-dimensional lattice automaton model. Here is a detailed explanation of the code:

# Libraries and Definitions:

It includes standard libraries and defines constants to simplify the code.
# Functions:

initialization_variables(): Initializes variables using values passed as command-line arguments.
initialization_generator(): Initializes the random number generator with a seed taken from the /dev/random file.
initialization_array(): Allocates memory for various multidimensional arrays used to track particle positions and distances.
initialization_lattice(): Sets up the lattice with particles distributed according to the provided probability.
update_lattice(): Updates the positions of the particles in the lattice based on random movements.
measure(): Calculates the average of the squared distances of the particles from their starting points.
# Main Function:

Checks if the correct number of arguments has been passed to the program.
Initializes variables, the random number generator, and arrays.
Executes a simulation of "num_stories" stories, each with "num_steps" steps.
Measures the average squared distance of particles at specified intervals.
Computes the diffusion coefficient and writes it to a file.
Simulation Logic:

For each story, the lattice is initialized and then a number of steps are performed, updating the particle positions and calculating measurements at regular intervals.
# File Writing Error:

If the file coeff_diffusione.dat cannot be opened, an error is printed.
Calculation and Output of Results:

At the end of the simulation, the program calculates the diffusion coefficient based on the average squared distances of the particles and writes this to the output file.
Graphical Output:

Finally, the program calls gnuplot to graphically display the results using a predefined plotting script.
The code is structured to be easily modifiable for different lattice sizes and particle occupancy probabilities, allowing exploration of how these factors influence diffusion in an ideal gas.
