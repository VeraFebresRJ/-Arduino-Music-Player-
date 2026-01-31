#include <WiFi.h>
#include "_A_notes.h"
#include "_C_tree.h"

// --------- CONFIGURACIÓN RED ----------
const char* ssid     = "Academos_EXT";
const char* password = "Monagas2024.";

// --------- CONFIGURACIÓN PWM (v3.0) ----------
#define LED_FREQ 5000     // Frecuencia
#define LED_RES  8        // Resolución de 8 bits (0-255)
#define LED_PIN  4        // Pin del LED indicador     # Cable: Amarillo
#define BUZZER_PIN 18     // Pin del Buzzer (zumbador) # Cable: Naranja


WiFiServer server(80);

// Nombres de las canciones para la UI.
const char* songNames[] = {
  "1️⃣ Jingle Bells 🔔", "2️⃣ Santa Claus is Coming to Town 🎅", "3️⃣ Silent Night 🌙",  "4️⃣ We Wish You a Merry Christmas 🎄", "5️⃣ Cartoon Ending 🐰", "6️⃣ First Noel ❄️", 
  "7️⃣ We Three Kings 👑", "8️⃣ Good King Wenceslass 🤴"
};

volatile bool stopSong = false;
int currentProgress = 0; // 0 a 100.

// Función para el efecto respiración del LED.
void actualizarRespiracion() {
  if (currentProgress == 0) { // Solo si el sistema está "Listo" (en espera).
    float period = 3000.0; // 3 segundos por pulsación.
    float lfo = (exp(sin(millis() / period * 2.0 * PI)) - 0.36787944) * 108.0;
    ledcWrite(LED_PIN, (int)lfo); // En v3.0 usamos directamente el pin
  }
}

// Función para manejar las peticiones web de forma centralizada.
void handleRequests() {
  WiFiClient client = server.available();
  if (!client) return;

  String request = client.readStringUntil('\r');
  client.flush(); // Limpiar el buffer para evitar colas de peticiones.

  // Permitir que la barra de progreso se actualice mediante un servidor SSE/JSON, sin lag.
  // Enviar datos de progreso a la interfaz.
  if (request.indexOf("/events") != -1) {
    client.print("HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nAccess-Control-Allow-Origin: *\r\n\r\n");
    client.printf("{\"prog\":%d}", currentProgress);
  }

  // Comando para detener canción.
  else if (request.indexOf("/stop") != -1) {
    stopSong = true;
    client.print("HTTP/1.1 200 OK\r\n\r\n");
  } 
  // Comando para iniciar canción
  else if (request.indexOf("/play?id=") != -1) {
    // Si ya hay algo sonando, paramos antes de empezar la nueva.
    stopSong = true; 
    client.print("HTTP/1.1 200 OK\r\n\r\n");
    // No llamamos a playTune aquí para evitar recursión infinita.
  }
  else {
    // INTERFAZ WEB con CSS Dark Mode y JS.
    client.print("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
    client.print("<!DOCTYPE html><html><head><meta charset='UTF-8'>");
    client.print("<style>body{background:#0a0a0a; color:#00ff99; font-family:monospace; text-align:center;}");
    client.print(".card{background:#111; border:1px solid #00ff99; border-radius:10px; padding:20px; margin:20px auto; max-width:400px;}");
    client.print(".prog-container{background:#222; border-radius:10px; height:20px; width:100%; margin:15px 0; overflow:hidden;}");
    client.print(".prog-bar{background:#00ff99; height:100%; width:0%; transition:width 0.4s ease; box-shadow: 0 0 10px #00ff99;}");

    // CSS para orientar los botones a la izquierda.
    client.print(".btn-list{text-align: left; max-width: 400px; margin: 0 auto;}");
    client.print(".btn{background:transparent; color:#00ff99; border:1px solid #00ff99; padding:12px; margin:5px 0; width:100%; cursor:pointer; font-weight:bold; text-align: left;}");
    client.print(".btn:hover{background:#00ff99; color:#000;}");
    client.print(".btn-stop{color:#ff4444; border-color:#ff4444; text-align: center; margin-bottom: 20px;}");
    client.print("</style></head><body><h1>🎵 ESP32 MUSIC PLAYER 🎵</h1>");
    client.print("<div class='card'>STATUS: <span id='stat'>READY</span><div class='prog-container'>");

    // Contenedor de botones orientado a la izquierda.
    client.print("<div id='pb' class='prog-bar'></div></div></div><div class='btn-list'>");
    client.print("<button class='btn btn-stop' onclick='exec(\"/stop\")'>⏹️ STOP MUSIC</button>");
    for(int i=0; i<8; i++) {
        client.printf("<button class='btn' onclick='exec(\"/play?id=%d\")'>%s</button>", i, songNames[i]);
    }
    client.print("</div><script>function exec(path){fetch(path);}");
    client.print("setInterval(()=>{fetch('/events').then(r=>r.json()).then(d=>{");
    client.print("document.getElementById('pb').style.width=d.prog+'%';");
    client.print("document.getElementById('stat').innerText=d.prog>0? d.prog+'%':'READY';})");
    client.print(".catch(e=>{});}, 500);</script></body></html>");
  }
  delay(1);
  client.stop();
}

// Función de reproducción mejorada para atender al servidor mientras toca.
void playTune(int tuneIdx) {
  stopSong = false;
  ledcWrite(LED_PIN, 0); // Apagar respiración durante la música.

  // 1. Contar notas totales para el cálculo porcentual.
  int totalNotes = 0;
  while (pgm_read_word(&(tunes[tuneIdx][totalNotes * 2])) != NOTE_END && totalNotes < N_MAX/2) {
    totalNotes++;
  }

  for (int i = 0; i < totalNotes; i++) {
    if (stopSong) break;

    // 2. Extraer datos de la memoria Flash.
    int note = pgm_read_word(&(tunes[tuneIdx][i * 2]));
    int duration = pgm_read_word(&(tunes[tuneIdx][i * 2 + 1]));

    // 3. ACTUALIZACIÓN DE PROGRESO: Calculada antes de la pausa (Nota actual / Total) * 100.
    currentProgress = ((i + 1) * 100) / totalNotes;

    int noteDuration = 1000 / duration;
    if (note != NOTE_REST) tone(BUZZER_PIN, note, noteDuration);

    unsigned long startPause = millis();
    // Pausa entre notas con interrupción suave.
    int pause = noteDuration * 1.30;

    // Durante la pausa de la nota, el ESP32 queda libre para procesar la Web.
    // BUCLE CRÍTICO: Mientras esperamos la nota, escuchamos peticiones web.
    // 4. ESCUCHA ACTIVA: Atender peticiones web mientras la nota suena.
    while(millis() - startPause < pause) {
      handleRequests(); // ESCUCHA ACTIVA DE PROGRESO Y STOP.
      if (stopSong) break;      
      yield();
    }
    // 5. Finalización: resetear progreso y apagar buzzer.
    noTone(BUZZER_PIN);
  }
  currentProgress = 0;
}

void setup() {
  Serial.begin(115200);
  pinMode(BUZZER_PIN, OUTPUT);

  // NUEVA API v3.0: Solo una función para configurar y adjuntar.
  ledcAttach(LED_PIN, LED_FREQ, LED_RES);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);

  server.begin();
  Serial.println("\n********************");
  Serial.println("📶 WiFi conectado.");
  Serial.print("🌐 IP: ");
  Serial.print(WiFi.localIP());
}

void loop() {
  actualizarRespiracion(); // El LED respira constantemente si no hay música.

  WiFiClient client = server.available();
  if (client) {
    String request = client.readStringUntil('\r');

    // Rutas de control
    if (request.indexOf("/play?id=") != -1) {
      int id = request.substring(request.indexOf("id=") + 3).toInt();
      client.print("HTTP/1.1 200 OK\r\n\r\n");
      client.stop();
      playTune(id);
    } else {
      // Si no es "play", manejar normal (HTML, events o stop).
      client.stop(); // Cerramos y usamos la función centralizada en el siguiente ciclo.
      // (Para mayor estabilidad, procesamos en el handleRequests del loop).
    }
  }
  handleRequests();
}