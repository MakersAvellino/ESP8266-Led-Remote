# ESP8266-Led-Remote
Controlliamo da remoto il led on board del ESP8266

Questo progetto è davvero molto semplice, se segui questi semplici passi anche tu sarai in grado di accendere o spegnere il led da remoto, clona ed estrai questo progetto e posizionati nella cartella appena estratta.

1: leggi il file "ESP8266 riassunto breve" il file è dentro la cartella LedRemote, nella prima pagina ti sarà spiegato come configurare l'IDE di arduino per poter programmare il tuo ESP8266

2: Apri il file LedRemote.ino presente nella cartella LedRemote, poi vai a sketch-->#include libraries o includi libreria(dipende dalla lingua che si ha impostato all'interno dell'IDE) e cliccare su importa da zip, e quindi importare, una alla volta le due librerie presenti nella cartella generale di questo progetto.

3 Vai in impostazioni cliccando su file e spunta la casella visualizza numeri di linea

4: Modifica lo SSID  e la password presenti tra le virgolette "" alle righe 7 e 8, associate al tuo modem di casa oppure del tuo smartphone se hai attivato il tethering

5: Seleziona la board giusta, infine carica il progetto stando attento ad aver selezionato la porta COM a cui è collegato il tuo ESP

6: Non appena caricato il progetto apri il monitor seriale presente in tools/strumenti e leggi l'indirizzo IP che ti è stato assegnato dal tuo modem

7: Apri il browser da qualsialsi dispositivo, assicurati che sia connesso alla stessa rete del ESP8266 e inserisci l'indirizzo IP che ti è stato assegnato

Ottimo, ora visualizzarai una pagina web nella quale saranno presenti due caselle, una che sfrutta il webServer per controllare il led e una che sfrutta il webSocket, entrambe potranno controllare il led, ma solo quella che sfrutta il webSocket sarà in grado di accendere e spegnere il led all'istante.
