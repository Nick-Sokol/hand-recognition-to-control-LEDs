#include <WiFi.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Replace with your network credentials
const char* ssid = "your ssid";
const char* password = "your password";

// LED pin definitions
const int ledPins[5] = {12, 14, 27, 26, 25}; // Change these GPIO pins as per your connection

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();

  // Initialize the LED pins as OUTPUT
  for (int i = 0; i < 5; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);

    Serial.println("Connecting to WiFi...");
    // Print for oled
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("Connecting to WiFi...");
    display.display();
  }
  Serial.println("Connected to WiFi");
  // Print for oled
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Connected to WiFi");
  display.display();

  // Print the IP address
  Serial.println(WiFi.localIP());
  // Print for oled
  display.println(WiFi.localIP());

  // Start the server
  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    Serial.println("New Client.");
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        // Serial.write(c); // Debugging: Print each received character
        if (c == '\n') {
          // If the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            break;
          } else {
            Serial.println("Received line: " + currentLine);

            // Print for oled
            display.clearDisplay();
            display.setTextSize(1);
            display.setTextColor(SSD1306_WHITE);
            display.setCursor(0, 0);
            display.println("Received data:");
            display.println(currentLine);
            display.display();

            int fingerUp[5];
            if (sscanf(currentLine.c_str(), "%d %d %d %d %d", &fingerUp[0], &fingerUp[1], &fingerUp[2], &fingerUp[3], &fingerUp[4]) == 5) {
              // Update LEDs based on the received finger data
              for (int i = 0; i < 5; i++) {
                digitalWrite(ledPins[i], fingerUp[i]);
                // Serial.printf("LED %d set to %d\n", i, fingerUp[i]); // Debugging: Confirm LED state change
              }
            } else {
              Serial.println("Error parsing data");
            }
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    // Close the connection
    client.stop();
    Serial.println("Client Disconnected.");
    delay(500); // Add a delay to prevent rapid reconnecting
  }
}
